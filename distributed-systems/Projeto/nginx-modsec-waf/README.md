# Balanceamento de carga com nginx + WAF (ModSecurity + OWASP CRS)

Projeto de Sistemas Distribuídos: aplicação replicada em três instâncias, com balanceador de carga,
sessões compartilhadas em Redis e um Web Application Firewall na entrada.

## Arquitetura

```
             http://localhost:2222
                      |
                      v
   WAF   nginx + ModSecurity + OWASP CRS   (única porta exposta)
                      |
                      v
   LB    nginx: balanceamento, failover, rate limit, cabeçalhos de segurança
          |           |           |
          v           v           v
        app1        app2        app3       Flask (réplicas idênticas)
          \           |           /
           +-------> Redis <-----+         sessões compartilhadas
```

## Estrutura

```
docker-compose.yml                     orquestração dos containers
.env                                   modo do WAF e outras opções
nginx/nginx.conf                       balanceador de carga
nginx/snippets/                        cabeçalhos de segurança e parâmetros de proxy
waf/                                   regras customizadas e ajustes do WAF
app/                                   aplicação com página de login
waf.sh                                 liga e desliga o WAF
test.sh                                testes automatizados
```

## Setup

1. Instale o Docker Engine e o plugin Docker Compose. Para usar sem `sudo`:
   ```
   sudo usermod -aG docker $USER
   ```
   Depois, abra uma nova sessão.

2. Na pasta do projeto, dê permissão aos scripts:
   ```
   chmod +x waf.sh test.sh
   ```

3. Suba o ambiente:
   ```
   docker compose up -d --build
   ```

4. Aguarde todos os containers ficarem `healthy`:
   ```
   docker compose ps
   ```

5. Acesse http://localhost:2222 e faça login com `root` / `root`.

O projeto usa só a porta 2222. Se ela estiver ocupada, troque o número da esquerda em `ports:` no
`docker-compose.yml`.

Para desligar tudo:

```
docker compose down
```

## Ativar e desativar o WAF

```
./waf.sh on          # detecta e bloqueia
./waf.sh off         # desligado, só repassa o tráfego
./waf.sh detect      # detecta e registra, sem bloquear
./waf.sh status      # mostra o modo atual
./waf.sh paranoia 2  # nível de rigor do OWASP CRS (1 a 4)
```

O script altera `WAF_MODE` no `.env` e recria o container do WAF.

## Demonstração

1. Login com `root` / `root`: redireciona para o painel, que mostra o usuário e a réplica que atendeu.
2. Com o WAF ligado, SQL Injection e XSS mostram "Requisição bloqueada pelo WAF".
3. Com o WAF desligado:
   - **SQL Injection**: entra no painel sem senha.
   - **XSS**: o navegador executa o script e abre um alerta.

Payloads de exemplo:

| Tipo | Usuário                          | Senha         |
|------|----------------------------------|---------------|
| SQLi | `' OR 1=1 --`                    | qualquer      |
| SQLi | `admin' --`                      | qualquer      |
| SQLi | `root`                           | `' OR '1'='1` |
| SQLi | `' UNION SELECT 'hacker' --`     | qualquer      |
| XSS  | `<script>alert(1)</script>`      | qualquer      |
| XSS  | `<img src=x onerror="alert(1)">` | qualquer      |

O banco é SQLite: use `--` ou `/*` como comentário, não `#`.

A CSP foi liberada com `'unsafe-inline'` só para o XSS executar na demonstração. Com
`script-src 'self'`, o navegador bloquearia o XSS mesmo sem WAF.

Testes automatizados (balanceamento, ataques, regras, cabeçalhos, força bruta e failover):

```
./test.sh
```

Depois do teste de força bruta, o login fica bloqueado por até 1 minuto.

## Proteções

**WAF:**
- OWASP CRS contra SQLi, XSS, RCE, LFI, Log4Shell e outros ataques do OWASP Top 10.
- Restrição de métodos, versões HTTP e Content-Type.
- Limites de tamanho de argumentos e de corpo.
- Inspeção de respostas e log de auditoria em JSON.
- Regras próprias: bloqueio de scanners, de requisições sem User-Agent, de `/admin` e de arquivos
  ocultos; lista de IPs; regras do login (só POST, tamanho máximo, parâmetro duplicado); virtual
  patch do parâmetro `debug`.

**nginx:**
- Balanceamento round robin, com health check passivo e failover.
- Rate limit geral e contra força bruta no login (10 por minuto).
- Limite de conexões e timeouts contra slowloris.
- Cabeçalhos de segurança: CSP, X-Frame-Options, nosniff, Referrer-Policy, Permissions-Policy
  e COOP/CORP.
- Cookie de sessão com HttpOnly e SameSite=Strict.
- `server_tokens off` e bloqueio de arquivos ocultos.

**Containers:**
- Aplicação sem root, com sistema de arquivos somente leitura e sem capabilities.
- Rede do backend isolada da internet.
- Redis com senha.
- Só o WAF expõe porta.

## Logs

```
docker logs -f waf    # ataques detectados
docker logs -f lb     # réplica que atendeu cada requisição
```

## Aviso

A aplicação é vulnerável a SQL Injection e XSS de propósito, para demonstrar o WAF. Use apenas
localmente. Com `APP_SQL_SEGURO=true` no `.env`, o SQL Injection é corrigido no código.
