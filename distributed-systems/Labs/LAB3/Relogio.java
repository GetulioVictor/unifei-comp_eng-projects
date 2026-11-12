import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Relogio extends Remote {

    // Retorna a data atual do servidor (opção 1 do menu do cliente)
    public String getData() throws RemoteException;

    // Retorna a hora atual do servidor (opção 2 do menu do cliente)
    public String getHora() throws RemoteException;
}