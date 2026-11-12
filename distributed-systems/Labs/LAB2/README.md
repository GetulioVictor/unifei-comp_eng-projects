# Service Discovery via UDP Broadcast

Aplicação que descobre, via broadcast UDP, onde está disponível o servidor HTTP
multithread desenvolvido na aula anterior (`Server/PoolDispatcher.java` +
`Server/EchoProtocol.java`).

## Arquivos

- `Server/UDPDiscoveryServer.java` — anuncia o serviço HTTP 
- `Client/UDPDiscoveryClient.java` — descobre o serviço HTTP 
- `Server/PoolDispatcher.java`, `Server/EchoProtocol.java` — servidor HTTP a ser descoberto (aula anterior)
- `Server/TCPEchoServerThread.java`, `Client/TCPEchoClient.java` — mantidos da aula anterior
- `Client/SendUDPBroadcast.java`, `Client/RecvUDPBroadcast.java` — base original que deu origem ao par acima

## Como rodar

Compilar:

```bash
cd LAB2-ECOS12A
javac -d out Server/*.java Client/*.java
cd out
```

Em três terminais separados, nesta ordem:

```bash
# Terminal 1 - sobe o serviço HTTP a ser descoberto
java PoolDispatcher

# Terminal 2 - sobe o servidor de descoberta
java UDPDiscoveryServer

# Terminal 3 - descobre o serviço
java UDPDiscoveryClient
```

O cliente imprime o endereço e a porta encontrados, e uma URL pronta para
acessar o serviço (ex.: `http://172.18.0.1:7500/`).

## Como funciona

**UDPDiscoveryServer** (porta UDP 6000)
Fica em loop recebendo pacotes UDP. Ao receber a mensagem
`DESCOBRIR_SERVICO_HTTP`, responde em unicast — direto para quem perguntou,
não em broadcast — com a string `SERVICO_HTTP;<ip>;<porta>`, onde `<ip>` é
descoberto automaticamente a partir das interfaces de rede da máquina (evita
retornar `127.0.0.1`) e `<porta>` é a porta fixa 7500 do servidor HTTP.

**UDPDiscoveryClient**
Envia um pacote UDP com a mensagem `DESCOBRIR_SERVICO_HTTP` para o endereço
de broadcast `255.255.255.255:6000`. Em seguida usa `setSoTimeout` para
esperar respostas por 3 segundos, processando todas as que chegarem nesse
intervalo — pode haver mais de um servidor de descoberta respondendo na
mesma rede. Ao estourar o timeout, encerra a busca.

**Serviço descoberto**
O `PoolDispatcher` continua sendo o serviço real: um servidor HTTP na porta
7500 que atende requisições usando um pool de threads (`EchoProtocol` trata
cada conexão). O discovery apenas anuncia onde esse serviço está; a conexão
final é feita normalmente via HTTP (browser, `curl` ou `TCPEchoClient`) usando
o IP e porta retornados pela descoberta.

## Observação de rede

Em máquinas diferentes na mesma LAN, verifique se o firewall permite UDP na
porta 6000 e se a rede aceita tráfego broadcast. Em redes que bloqueiam o
broadcast limitado (`255.255.255.255`), pode ser necessário usar o broadcast
da sub-rede específica (ex.: `192.168.1.255`).