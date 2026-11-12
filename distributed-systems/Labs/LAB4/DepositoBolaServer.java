import java.rmi.*;
import java.rmi.server.*;

public class DepositoBolaServer {
    public static void main(String[] args) {
        try {
            System.out.println("Constructing server implementations...");

            DepositoBolaImpl deposito = new DepositoBolaImpl();
            fillDeposito(deposito);

            System.out.println("Binding server implementation to registry...");
            Naming.rebind("rmi://localhost:1099/DepositoBolaService", deposito);

            System.out.println("Waiting for invocations from clients...");
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }

    public static void fillDeposito(DepositoBolaImpl d) throws RemoteException {
        d.add(new BolaImpl("Penalty S11", "Futebol", Bola.BOTH, 14, 200, 430));
        d.add(new BolaImpl("Molten GG7", "Basquete", Bola.MALE, 15, 200, 600));
        d.add(new BolaImpl("Mikasa V200W", "Volei", Bola.FEMALE, 12, 200, 270));
        d.add(new BolaImpl("Wilson US Open", "Tenis", Bola.BOTH, 10, 200, 58));
        d.add(new BolaImpl("Nike Infantil", "Futebol", Bola.BOTH, 4, 13, 290));
    }
}
