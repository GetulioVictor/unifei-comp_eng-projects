# Lab 04 - Java RMI 2
Servidor RMI com o objeto remoto DepositoBola. O método encontraBola recebe um Jogador (perfil) e retorna uma Bola adequada.

- Jogador: passado por cópia (classe `Serializable`, não remota).
- Bola: retornada por referência (objeto remoto → cliente recebe stub).

O servidor chama `j.reset()` no Jogador, mas o cliente vê o Jogador intacto (cópia). Cada `getDescription()` na Bola é uma chamada remota (referência).

## Arquivos

| Arquivo | Descrição |
|---|---|
| `Bola.java` | Interface remota (`extends Remote`). |
| `BolaImpl.java` | Implementação; o método `match()` é local. |
| `Jogador.java` | Classe `Serializable` (passada por cópia). |
| `DepositoBola.java` | Interface remota: `encontraBola(Jogador): Bola`. |
| `DepositoBolaImpl.java` | Procura e retorna a Bola; chama `reset()` . |
| `DepositoBolaServer.java` | Cria/cadastra as bolas e registra no `rmiregistry`. |
| `DepositoBolaClient.java` | Faz `lookup` e testa vários jogadores. |


## Como executar 

1. `javac *.java`
2. `rmiregistry` — Terminal 1
3. `java DepositoBolaServer` — Terminal 2
4. `java DepositoBolaClient` — Terminal 3