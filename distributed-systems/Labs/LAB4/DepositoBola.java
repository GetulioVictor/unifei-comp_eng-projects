import java.rmi.*;

public interface DepositoBola extends Remote {
    public Bola encontraBola(Jogador j) throws RemoteException;
}
