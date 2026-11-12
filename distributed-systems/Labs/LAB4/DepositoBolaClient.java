import java.rmi.*;

public class DepositoBolaClient {
    public static void main(String[] args) {
        try {
            String url = "rmi://localhost/DepositoBolaService";
            DepositoBola deposito = (DepositoBola) Naming.lookup(url);

            Jogador[] jogadores = {
                new Jogador("Ana", 22, Bola.FEMALE, "Volei"),
                new Jogador("Bruno", 30, Bola.MALE, "Basquete"),
                new Jogador("Carla", 16, Bola.FEMALE, "Futebol"),
                new Jogador("Diego", 8, Bola.MALE, "Futebol"),
                new Jogador("Elena", 25, Bola.FEMALE, "Golfe")
            };

            for (int i = 0; i < jogadores.length; i++) {
                Jogador j = jogadores[i];
                System.out.println("--------------------------------------------------");
                System.out.println("Sending -> " + j);

                Bola b = deposito.encontraBola(j);

                System.out.println("Client after the call -> " + j);

                if (b != null)
                    System.out.println("Returned ball -> " + b.getDescription());
                else
                    System.out.println("No suitable ball found.");
            }
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
        System.exit(0);
    }
}
