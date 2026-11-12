import os
import secrets
import socket
import sqlite3

import redis
from flask import Flask, jsonify, request, send_from_directory

app = Flask(__name__, static_folder="static", static_url_path="/static")

INSTANCE = os.getenv("INSTANCE_NAME", socket.gethostname())
SQL_SEGURO = os.getenv("APP_SQL_SEGURO", "false").lower() == "true"
DB_PATH = "/tmp/usuarios.db"
SESSAO_TTL = 600  # segundos

r = redis.Redis(
    host=os.getenv("REDIS_HOST", "redis"),
    port=6379,
    password=os.getenv("REDIS_PASSWORD") or None,
    decode_responses=True,
    socket_timeout=2,
)

def init_db() -> None:
    con = sqlite3.connect(DB_PATH)
    con.execute("DROP TABLE IF EXISTS usuarios")
    con.execute("CREATE TABLE usuarios (username TEXT PRIMARY KEY, senha TEXT NOT NULL)")
    con.executemany(
        "INSERT INTO usuarios VALUES (?, ?)",
        [("root", "root"), ("admin", secrets.token_hex(16))],  # senha do admin e aleatoria
    )
    con.commit()
    con.close()

init_db()

def autenticar(usuario: str, senha: str):
    con = sqlite3.connect(DB_PATH)
    try:
        if SQL_SEGURO:
            # Correto: consulta parametrizada
            row = con.execute(
                "SELECT username FROM usuarios WHERE username = ? AND senha = ?",
                (usuario, senha),
            ).fetchone()
        else:
            # VULNERAVEL DE PROPOSITO: entrada do usuario concatenada na consulta
            query = f"SELECT username FROM usuarios WHERE username = '{usuario}' AND senha = '{senha}'"
            row = con.execute(query).fetchone()
    finally:
        con.close()
    return str(row[0]) if row else None

def usuario_da_sessao():
    token = request.cookies.get("sessao")
    return r.get(f"sessao:{token}") if token else None

@app.get("/")
def index():
    return send_from_directory(app.static_folder, "index.html")

@app.get("/painel")
def painel():
    return send_from_directory(app.static_folder, "painel.html")

@app.post("/api/login")
def login():
    usuario = request.form.get("username", "")
    senha = request.form.get("password", "")

    try:
        nome = autenticar(usuario, senha)
    except sqlite3.Error as erro:
        # Vazamento de erro do banco: mostra o impacto quando o WAF esta desligado
        return jsonify(ok=False, usuario=usuario, detalhe=str(erro), instancia=INSTANCE), 500

    if not nome:
        # Devolve o usuario digitado; a pagina o exibe sem tratamento (XSS refletido)
        return jsonify(ok=False, usuario=usuario, instancia=INSTANCE), 401

    token = secrets.token_urlsafe(32)
    try:
        # Sessao no Redis: qualquer replica consegue validar
        r.setex(f"sessao:{token}", SESSAO_TTL, nome)
    except redis.RedisError:
        return jsonify(ok=False, detalhe="Servico de sessao indisponivel", instancia=INSTANCE), 503

    resposta = jsonify(ok=True, redirecionar="/painel", instancia=INSTANCE)
    resposta.set_cookie("sessao", token, max_age=SESSAO_TTL, path="/")
    return resposta

@app.get("/api/me")
def me():
    try:
        nome = usuario_da_sessao()
    except redis.RedisError:
        return jsonify(ok=False, erro="Servico de sessao indisponivel", instancia=INSTANCE), 503
    if not nome:
        return jsonify(ok=False, erro="Sem sessao ativa", instancia=INSTANCE), 401
    return jsonify(ok=True, usuario=nome, instancia=INSTANCE)

@app.post("/api/logout")
def logout():
    token = request.cookies.get("sessao")
    if token:
        try:
            r.delete(f"sessao:{token}")
        except redis.RedisError:
            pass
    resposta = jsonify(ok=True)
    resposta.delete_cookie("sessao", path="/")
    return resposta

@app.get("/api/status")
def status():
    try:
        total = r.incr("visitas_total")
        r.hincrby("visitas_por_instancia", INSTANCE, 1)
        distribuicao = r.hgetall("visitas_por_instancia")
    except redis.RedisError:
        total, distribuicao = None, {}
    return jsonify(instancia=INSTANCE, visitas_total=total, distribuicao=distribuicao)

@app.get("/api/busca")
def busca():
    return jsonify(instancia=INSTANCE, termo=request.args.get("q", ""))

@app.get("/health")
def health():
    return "ok"