import java.net.*; // for DatagramSocket, DatagramPacket, InetAddress...
import java.io.*;  // for IOException

/**
 * Cliente de Descoberta de Servico via UDP Broadcast.
 *
 * Envia uma mensagem em broadcast perguntando, na rede local, quem
 * oferece o servico HTTP anunciado pelo Server/UDPDiscoveryServer.java, e
 * fica escutando por um curto periodo de tempo as respostas (pode haver
 * mais de um servidor de descoberta respondendo na rede).
 *
 * Baseado no par SendUDPBroadcast.java / RecvUDPBroadcast.java da aula
 * anterior, juntando as duas pontas (enviar pedido + receber resposta)
 * em um unico programa e tratando o caso de varias respostas / timeout.
 */
public class UDPDiscoveryClient {

    private static final int DISCOVERY_PORT = 6000;
    private static final int MAX_LENGTH = 255;
    private static final int TIMEOUT_MS = 3000; // tempo maximo esperando respostas
    private static final String REQUEST_MSG = "DESCOBRIR_SERVICO_HTTP";

    public static void main(String[] args) throws Exception {

        DatagramSocket sock = new DatagramSocket();
        sock.setBroadcast(true);       // necessario para poder enviar em broadcast
        sock.setSoTimeout(TIMEOUT_MS); // evita bloquear para sempre esperando resposta

        InetAddress broadcastAddr = InetAddress.getByName("255.255.255.255");
        byte[] reqBytes = REQUEST_MSG.getBytes();

        DatagramPacket request = new DatagramPacket(
                reqBytes, reqBytes.length, broadcastAddr, DISCOVERY_PORT);
        sock.send(request);
        System.out.println("Broadcast de descoberta enviado: \"" + REQUEST_MSG + "\"");
        System.out.println("Aguardando respostas por " + (TIMEOUT_MS / 1000) + "s...");

        // Continua recebendo ate estourar o timeout, pois pode existir
        // mais de um servidor respondendo ao mesmo broadcast
        try {
            while (true) {
                DatagramPacket response = new DatagramPacket(new byte[MAX_LENGTH], MAX_LENGTH);
                sock.receive(response);

                String msg = new String(response.getData(), 0, response.getLength());
                System.out.println("Servico encontrado em "
                        + response.getAddress().getHostAddress() + ":" + response.getPort()
                        + " -> " + msg);

                // Formato esperado da resposta: SERVICO_HTTP;<ip>;<porta>
                String[] partes = msg.split(";");
                if (partes.length == 3 && partes[0].equals("SERVICO_HTTP")) {
                    String ip = partes[1];
                    int porta = Integer.parseInt(partes[2]);
                    System.out.println("  -> Acesse o servico em: http://" + ip + ":" + porta + "/");
                }
            }
        } catch (SocketTimeoutException e) {
            System.out.println("Tempo esgotado. Fim da busca por servicos na rede.");
        } finally {
            sock.close();
        }
    }
}
