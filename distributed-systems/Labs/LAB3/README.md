# Serviço Relógio via RMI

Aplicação RMI em que o cliente obtém a data atual (opção 1) e a hora atual
(opção 2) de um objeto remoto chamado `Relogio`, hospedado no servidor.

## Arquivos

- `Relogio.java` — interface remota (estende `Remote`), declara `getData()` e `getHora()`
- `RelogioImpl.java` — implementação (estende `UnicastRemoteObject`)
- `RelogioServer.java` — registra o objeto no RMI Registry com `Naming.rebind()`
- `RelogioClient.java` — menu que consulta o objeto remoto com `Naming.lookup()`

## Como rodar

Compilar:

```bash
javac -d out *.java
cd out
```

São necessários 3 consoles, nesta ordem:

```bash
# Console 1 - RMI Registry
rmiregistry

# Console 2 - servidor
java RelogioServer

# Console 3 - cliente
java RelogioClient
# ou, acessando outra máquina da rede:
java RelogioClient <ip-do-servidor>
```

## Como funciona

`Relogio` define o comportamento remoto (dois métodos, ambos lançando
`RemoteException`). `RelogioImpl` implementa esse comportamento
consultando a data/hora do sistema e formatando com `SimpleDateFormat`.

O servidor instancia `RelogioImpl` (o construtor, ao chamar `super()`,
exporta o objeto para o sistema RMI) e o registra no RMI Registry através
de `Naming.rebind("rmi://localhost:1099/Relogio", r)`.

O cliente obtém o stub do objeto com `Naming.lookup("rmi://<host>/Relogio")`
e chama `getData()` ou `getHora()` conforme a opção escolhida no menu —
cada chamada é uma invocação remota real, executada no servidor, cujo
resultado retorna serializado para o cliente.

## Observação sobre o rmiregistry

O `rmiregistry` precisa ser executado no diretório onde estão as classes
compiladas (`out/`), pois é ele quem localiza as classes de stub/skeleton
necessárias para a comunicação. Se o servidor não conseguir se registrar,
confira se o `rmiregistry` está de fato rodando na porta 1099 e não há
outro processo ocupando essa porta.