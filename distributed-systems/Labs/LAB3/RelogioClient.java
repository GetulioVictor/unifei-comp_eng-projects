import java.rmi.Naming;
import java.rmi.RemoteException;
import java.net.MalformedURLException;
import java.rmi.NotBoundException;
import java.util.Scanner;


public class RelogioClient {

    public static void main(String[] args) {

        // Host do servidor: usa o primeiro argumento da linha de comando,
        // ou "localhost" se nenhum for informado
        String host = (args.length > 0) ? args[0] : "localhost";

        try {
            Relogio relogio = (Relogio)
                    Naming.lookup("rmi://" + host + "/Relogio");

            Scanner scanner = new Scanner(System.in);
            int opcao;

            do {
                System.out.println("\n===== Cliente Relogio (RMI) =====");
                System.out.println("1 - Obter data atual");
                System.out.println("2 - Obter hora atual");
                System.out.println("0 - Sair");
                System.out.print("Escolha uma opcao: ");

                opcao = Integer.parseInt(scanner.nextLine().trim());

                switch (opcao) {
                    case 1:
                        System.out.println("Data atual no servidor: " + relogio.getData());
                        break;
                    case 2:
                        System.out.println("Hora atual no servidor: " + relogio.getHora());
                        break;
                    case 0:
                        System.out.println("Encerrando cliente.");
                        break;
                    default:
                        System.out.println("Opcao invalida.");
                }
            } while (opcao != 0);

            scanner.close();
        }
        catch (MalformedURLException murle) {
            System.out.println();
            System.out.println("MalformedURLException");
            System.out.println(murle);
        }
        catch (RemoteException re) {
            System.out.println();
            System.out.println("RemoteException");
            System.out.println(re);
        }
        catch (NotBoundException nbe) {
            System.out.println();
            System.out.println("NotBoundException");
            System.out.println(nbe);
        }
    }
}
