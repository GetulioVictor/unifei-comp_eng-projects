import java.rmi.Naming;

public class RelogioServer {

    public RelogioServer() {
        try {
            Relogio r = new RelogioImpl();
            Naming.rebind("rmi://localhost:1099/Relogio", r);
            System.out.println("Servico 'Relogio' registrado no RMI Registry.");
            System.out.println("Aguardando chamadas dos clientes...");
        } catch (Exception e) {
            System.out.println("Trouble: " + e);
        }
    }

    public static void main(String args[]) {
        new RelogioServer();
    }
}
