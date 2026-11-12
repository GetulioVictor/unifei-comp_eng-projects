# Balanceamento de carga com nginx + WAF (ModSecurity + OWASP CRS)

Projeto de Sistemas Distribuídos: aplicação replicada em três instâncias, com balanceador de carga,
estado compartilhado em Redis e um Web Application Firewall na entrada.

## Arquitetura

```
                  Navegador / curl
                        |
               http://localhost:2222
                        v
   +------------------------------------------+
   |  WAF  nginx + ModSecurity v3 + OWASP CRS |   rede "frontend"
   +------------------------------------------+
                        |
                        v
   +------------------------------------------+
   |  LB   nginx: balanceamento, failover,    |   (sem porta exposta)
   |       rate limit, headers de segurança   |
   +------------------------------------------+
            |            |            |            rede "backend" (interna,
            v            v            v             sem acesso à internet)
          app1         app2         app3     Flask + Gunicorn
            \            |            /
             +-----> Redis <---------+       sessões e contadores compartilhados
```

## Estrutura

```
docker-compose.yml                     orquestração dos 6 containers
.env                                   liga/desliga o WAF e outras opções
nginx/nginx.conf                       balanceador de carga
nginx/snippets/security-headers.conf   cabeçalhos de segurança
nginx/snippets/proxy-params.conf       proxy, failover e flags de cookie
waf/REQUEST-900-...-BEFORE-CRS.conf    regras customizadas do WAF
waf/RESPONSE-999-...-AFTER-CRS.conf    ajustes de falsos positivos
app/                                   aplicação com página de login
waf.sh                                 ativar e desativar o WAF
test.sh                                bateria de testes automatizados
```

## Passo a passo para rodar (Linux)

### 1. Instalar o Docker

Instale o Docker Engine e o plugin Docker Compose pela documentação oficial da sua distribuição.
Para usar o Docker sem `sudo`, adicione seu usuário ao grupo `docker` e abra uma nova sessão:

```
sudo usermod -aG docker $USER
```

Confira:

```
docker --version
docker compose version
```

### 2. Dar permissão de execução aos scripts

Na pasta do projeto:

```
chmod +x waf.sh test.sh
```

### 3. Verificar a porta

O projeto usa apenas a porta 2222. Para ver se ela está livre:

```
ss -tlnp | grep 2222
```

Se aparecer algo, a porta está ocupada. Altere o número da esquerda em `ports:` no
`docker-compose.yml` (ex.: `"3333:2222"`) e use essa porta na URL e no `test.sh`.

### 4. Subir o ambiente

```
docker compose up -d --build
```

Na primeira vez demora alguns minutos para baixar as imagens. Acompanhe com:

```
docker compose ps
```

Espere todos ficarem `running` ou `healthy`.

### 5. Acessar

Existe uma única URL: http://localhost:2222

Toda requisição passa pelo container do WAF. Quando o WAF está desligado, ele apenas repassa o
tráfego ao balanceador, sem inspecionar nada.

Login válido: usuário `root`, senha `root`.

### 6. Testar a página de login

1. Clique em "Credenciais válidas" e em "Entrar": você é redirecionado para `/painel`, que mostra
   "Login efetuado com sucesso", o usuário e a réplica que atendeu.
2. Volte, clique em "SQL Injection" ou "XSS" e entre: aparece "Requisição bloqueada pelo WAF".
3. Desligue o WAF (`./waf.sh off`) e repita:
   - SQL Injection: entra no painel sem saber a senha.
   - XSS: o navegador executa o script e abre um alerta.
4. Ligue de novo com `./waf.sh on`.

A mensagem de bloqueio só aparece quando o WAF bloqueia (status 403, 405 ou 415). A aplicação
nunca devolve esses códigos, então não há falso aviso.

Os campos de usuário e senha são visíveis (não mascarados) para facilitar a demonstração.

#### Payloads de SQL Injection que funcionam com o WAF desligado

| Usuário                          | Senha             | Resultado                      |
|----------------------------------|-------------------|--------------------------------|
| `' OR 1=1 --`                    | qualquer          | entra como o primeiro usuário  |
| `' OR '1'='1' --`                | qualquer          | entra como o primeiro usuário  |
| `root' --`                       | qualquer          | entra como root                |
| `admin' --`                      | qualquer          | entra como admin (senha aleatória) |
| `admin'/*`                       | qualquer          | entra como admin               |
| `root`                           | `' OR '1'='1`     | entra como root                |
| `' OR '1'='1`                    | `' OR '1'='1`     | entra como root                |
| `' UNION SELECT 'hacker' --`     | qualquer          | entra como um usuário que nem existe |
| `'`                              | qualquer          | erro do banco vazado na tela   |

O banco é SQLite. Payloads com `#` como comentário são do MySQL e geram erro de sintaxe aqui;
use `--` ou `/*`.

#### Payloads de XSS que funcionam com o WAF desligado

| Usuário                                         | Senha    |
|-------------------------------------------------|----------|
| `<script>alert(1)</script>`                     | qualquer |
| `<img src=x onerror="alert(1)">`                | qualquer |
| `<svg onload="alert(document.domain)">`         | qualquer |
| ``<img src=x onerror="alert(`XSS executado`)">`` | qualquer |

O XSS funciona porque a mensagem de erro insere o usuário digitado como HTML. Se o payload tiver
aspas simples (`'`), ele também quebra a consulta SQL e cai na mensagem de erro do banco; o XSS
executa do mesmo jeito, porque essa mensagem também exibe o usuário como HTML.

Repare que `alert(document.cookie)` vem vazio: o cookie de sessão tem a flag HttpOnly, aplicada
pelo nginx.

A CSP do nginx foi liberada com `'unsafe-inline'` para o XSS poder executar. Com a CSP estrita
(`script-src 'self'`), o navegador bloquearia o script mesmo com o WAF desligado. Isso pode ser
mostrado na apresentação como outra camada de defesa.

### 7. Rodar os testes automatizados

```
./test.sh
```

O script testa balanceamento, ataques, regras customizadas, cabeçalhos, força bruta e failover,
e mostra ao lado o resultado esperado com o WAF ligado. Para comparar, rode uma vez com
`./waf.sh on` e outra com `./waf.sh off`.

Depois do teste de força bruta o login fica bloqueado por até 1 minuto (rate limit). É esperado.

## Ativar e desativar o WAF

O modo do WAF fica na variável `WAF_MODE` do arquivo `.env`:

| Modo            | Comportamento                                               |
|-----------------|-------------------------------------------------------------|
| `On`            | Detecta e bloqueia (padrão)                                 |
| `DetectionOnly` | Detecta e registra no log, mas deixa passar                 |
| `Off`           | ModSecurity desligado, o nginx do WAF vira só um proxy      |

### Pelo script

```
./waf.sh on          # liga
./waf.sh off         # desliga
./waf.sh detect      # só detecta
./waf.sh status      # mostra o modo atual
./waf.sh paranoia 2  # muda o nível de paranoia (1 a 4)
```

### Manualmente

1. Edite o `.env` e troque `WAF_MODE=On` por `Off` ou `DetectionOnly`.
2. Rode `docker compose up -d waf` para recriar só o container do WAF.

## Proteções implementadas

### WAF (ModSecurity + OWASP CRS)

| Proteção                               | Onde                     |
|----------------------------------------|--------------------------|
| SQL Injection, XSS, RCE, LFI, RFI, Log4Shell, session fixation e outros ataques do OWASP Top 10 | OWASP CRS |
| Pontuação de anomalia e nível de paranoia ajustáveis | `.env` |
| Apenas métodos GET, HEAD e POST        | `ALLOWED_METHODS`        |
| Apenas HTTP/1.1 e HTTP/2               | `ALLOWED_HTTP_VERSIONS`  |
| Apenas Content-Types de formulário e JSON | `ALLOWED_REQUEST_CONTENT_TYPE` |
| Limite de quantidade e tamanho de argumentos | `MAX_NUM_ARGS`, `ARG_LENGTH`, `TOTAL_ARG_LENGTH` |
| Limite de tamanho de corpo e arquivos  | `MODSEC_REQ_BODY_LIMIT`, `MAX_FILE_SIZE` |
| Validação de codificação UTF-8         | `VALIDATE_UTF8_ENCODING` |
| Inspeção de respostas (vazamento de erros SQL, código-fonte) | `MODSEC_RESP_BODY_*` |
| Log de auditoria em JSON               | `MODSEC_AUDIT_*`         |
| Cabeçalho `Server` removido            | `SERVER_HEADER`          |
| Bloqueio de scanners (sqlmap, nikto, nmap, nuclei...) | regra 10001 |
| Bloqueio de requisições sem User-Agent | regra 10002              |
| Bloqueio de caminhos administrativos e endpoints internos | regra 10003 |
| Bloqueio de arquivos ocultos (.env, .git) | regra 10004           |
| Lista de IPs bloqueados                | regra 10005              |
| Login só aceita POST                   | regra 10006              |
| Login só aceita Content-Type de formulário | regra 10007          |
| Tamanho máximo de usuário e senha      | regra 10008              |
| HTTP Parameter Pollution no login      | regra 10009              |
| Virtual patching do parâmetro `debug`  | regra 10010              |

### Balanceador (nginx)

| Proteção / recurso                      | Diretiva                          |
|-----------------------------------------|-----------------------------------|
| Balanceamento round robin (ou least_conn, ip_hash) | `upstream`             |
| Health check passivo e failover         | `max_fails`, `proxy_next_upstream`|
| Rate limit geral (20 req/s por IP)      | `limit_req zone=geral`            |
| Proteção contra força bruta no login (10/min) | `limit_req zone=login`      |
| Limite de conexões simultâneas por IP   | `limit_conn`                      |
| Mitigação de slowloris                  | `client_*_timeout`, `send_timeout`|
| Limite de tamanho de corpo e cabeçalhos | `client_max_body_size`, `large_client_header_buffers` |
| Restrição de métodos por rota           | `limit_except`                    |
| Bloqueio de arquivos ocultos            | `location ~ /\.`                  |
| Versão do nginx oculta                  | `server_tokens off`               |
| Remoção de cabeçalhos do backend        | `proxy_hide_header`               |
| Cookie de sessão com HttpOnly e SameSite=Strict | `proxy_cookie_flags`      |
| IP real do cliente atrás do WAF         | `real_ip_header`                  |
| Métricas restritas à rede interna       | `stub_status` + `allow/deny`      |

Cabeçalhos de segurança enviados em todas as respostas: `Content-Security-Policy`,
`X-Frame-Options`, `X-Content-Type-Options`, `Referrer-Policy`, `Permissions-Policy`,
`Cross-Origin-Opener-Policy`, `Cross-Origin-Resource-Policy`, `X-XSS-Protection: 0` e
`Cache-Control: no-store`. O HSTS está no arquivo, comentado, porque em localhost afetaria
todas as portas do navegador.

### Containers

| Proteção                                 | Onde                   |
|------------------------------------------|------------------------|
| Aplicação roda sem root                  | `app/Dockerfile`       |
| Sistema de arquivos somente leitura      | `read_only: true`      |
| Todas as capabilities do Linux removidas | `cap_drop: [ALL]`      |
| Sem escalada de privilégios              | `no-new-privileges`    |
| Rede do backend isolada da internet      | `internal: true`       |
| Redis com senha                          | `--requirepass`        |
| Balanceador e réplicas sem porta exposta | só o WAF publica porta |

## Conceitos de Sistemas Distribuídos demonstrados

- Escalabilidade horizontal: três réplicas idênticas atrás do balanceador.
- Tolerância a falhas: `docker stop app2` e o sistema continua respondendo.
- Estado compartilhado: a sessão criada numa réplica é validada por outra (atualize o painel e
  veja a réplica mudar sem perder o login).
- Health checks: o Compose só inicia o balanceador quando as réplicas estão saudáveis.
- Defesa em camadas: WAF, balanceador e aplicação, cada um com sua responsabilidade.
- Ponto único de falha: `docker stop redis` derruba login e sessão. Bom ponto para discutir
  replicação do Redis (Sentinel) como melhoria futura.

## Experimentos

1. Faça login e atualize o painel várias vezes: a réplica alterna entre app1, app2 e app3.
2. Derrube a réplica que aparece no painel (`docker stop app1`) e atualize: a sessão continua
   válida porque está no Redis, e outra réplica atende.
3. Tente SQL Injection e XSS com o WAF ligado, em `DetectionOnly` e desligado.
4. Mude `APP_SQL_SEGURO=true` no `.env`, rode `docker compose up -d` e repita com o WAF desligado:
   agora o código está corrigido e o ataque falha mesmo sem WAF.
5. Rode `./waf.sh paranoia 4` e veja se requisições legítimas começam a ser bloqueadas
   (falsos positivos).
6. Em `nginx/nginx.conf`, troque para `least_conn` e rode `docker compose restart lb`.

## Logs

```
docker logs -f waf    # auditoria do ModSecurity em JSON (ataques detectados)
docker logs -f lb     # qual réplica recebeu cada requisição e se foi limitada
docker logs -f app1   # acessos de uma réplica
```

Para ver só os IDs e mensagens das regras disparadas:

```
docker logs waf 2>&1 | grep -o '"ruleId":"[0-9]*"\|"message":"[^"]*"'
```

## Desligar

```
docker compose down
```

## Observação

Com `APP_SQL_SEGURO=false` a aplicação é vulnerável a SQL Injection, e a página de login é sempre
vulnerável a XSS, de propósito, para demonstrar o WAF. Use apenas localmente.
