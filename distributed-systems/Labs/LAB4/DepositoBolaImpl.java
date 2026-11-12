import java.rmi.*;
import java.util.*;
import java.rmi.server.*;

public class DepositoBolaImpl extends UnicastRemoteObject implements DepositoBola {
    private Vector<BolaImpl> balls;

    public DepositoBolaImpl() throws RemoteException {
        balls = new Vector<BolaImpl>();
    }

    public synchronized void add(BolaImpl b) {
        balls.add(b);
    }

    public synchronized Bola encontraBola(Jogador j) throws RemoteException {
        System.out.println("Received on server -> " + j);
        Bola found = null;
        for (int i = 0; i < balls.size(); i++) {
            BolaImpl b = balls.get(i);
            if (b.match(j)) {
                found = b;
                break;
            }
        }
        j.reset();
        System.out.println("After reset() on server -> " + j);
        return found;
    }
}
