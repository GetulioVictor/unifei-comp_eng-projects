# Calculadora - Web Services REST

Servidor REST com **Express**, cliente Node.js com **Axios** e cliente Java com **HttpClient**.

## Estrutura

```
calculadora/
├── server/app.js
├── client/app.js
├── client-java/Client.java
└── README.md
```

## Rotas

| Rota                           | Exemplo          | Resposta                 |
|--------------------------------|------------------|--------------------------|
| `/somar/:valor1/:valor2`       | `/somar/10/5`    | `Resultado: 15`          |
| `/subtrair/:valor1/:valor2`    | `/subtrair/10/5` | `Resultado: 5`           |
| `/multiplicar/:valor1/:valor2` | `/multiplicar/10/5` | `Resultado: 50`       |
| `/dividir/:valor1/:valor2`     | `/dividir/10/5`  | `Resultado: 2`           |
| `/dividir/:valor1/0`           | `/dividir/10/0`  | `Erro: divisao por zero` |

## Pré-requisitos

- Node.js e npm
- Java 11+

## 1. Servidor

```bash
cd server
npm install express
node app.js
```

No navegador: http://localhost:3000/somar/10/5

## 2. Cliente Node.js

Em outro terminal, com o servidor rodando:

```bash
cd client
npm i axios
node app.js somar 10 10
```

Saída esperada:

```
Resultado: 20
```

## 3. Cliente Java

```bash
cd cliente-java
javac Client.java
java Client multiplicar 7 7
```

Saída esperada:

```
Resultado: 49
```
