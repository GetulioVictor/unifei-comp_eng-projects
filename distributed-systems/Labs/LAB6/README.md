# MQTT Temperatura (Node.js + EMQX)

Duas aplicações que se comunicam via MQTT:

- **sensor.js**: simula a temperatura e publica a cada 2 s em `casa/sala/temperatura`.
- **atuador.js**: assina esse tópico e reage à temperatura:
  - `>= 28 °C`: liga o ar-condicionado (`ON` em `casa/sala/ar-condicionado/comando`)
  - `<= 24 °C`: desliga o ar-condicionado (`OFF`)
  - variação `>= 1,2 °C` entre leituras: publica alerta em `casa/sala/alerta`

## Pré-requisitos

- Node.js 18+
- Docker

## Como rodar

### 1. Subir o broker EMQX

```bash
docker run -d --name emqx -p 1883:1883 -p 8083:8083 -p 8084:8084 -p 8883:8883 -p 18083:18083 emqx/emqx
```

### 2. Instalar as dependências

```bash
npm install mqtt --save
```

### 3. Rodar as aplicações (um terminal para cada)

```bash
npm run atuador
npm run sensor
```

Subir o atuador primeiro para ele não perder nenhuma leitura.

## Onde verificar no EMQX

Acesse o dashboard em **http://localhost:18083** (login padrão: `admin` / `public`). Na tela principal, com o período em *Last hour*, os gráficos mostram a atividade do sensor e do atuador:

| Gráfico | O que esperar com as duas aplicações rodando |
|---------|----------------------------------------------|
| Connections | 2 conexões (`sensor_xxxx` e `atuador_xxxx`) |
| Subscriptions | 1 assinatura (atuador em `casa/sala/temperatura`) |
| Topics | 1 tópico retido (a última temperatura, publicada com `retain`) |
| Messages In | sobe a cada publicação (a cada 2 s do sensor, mais comandos e alertas do atuador) |
| Messages Out | mensagens entregues ao atuador |
| Dropped Messages | mensagens sem nenhum assinante |

Quando você para as aplicações, Connections e Subscriptions voltam a 0.


Observação: No Dropped Messages é normal observar os valores aqui. O atuador publica em `casa/sala/ar-condicionado/comando` e `casa/sala/alerta`, e ninguém assina esses tópicos, então o broker os descarta. O mesmo acontece se o sensor publicar antes de o atuador estar rodando.

## Portas

- `1883`: broker MQTT (usado pelo código)
- `18083`: dashboard web
