import java.net.*; // for DatagramSocket, DatagramPacket, InetAddress...
import java.io.*;  // for IOException
import java.util.Enumeration;

/*
 Servidor de Descoberta de Servico (Service Discovery) via UDP Broadcast.
 
 Fica escutando em um socket UDP por mensagens de descoberta enviadas em
 broadcast pelos clientes da rede. Quando recebe a mensagem esperada,
 responde (em unicast, direto para quem perguntou) informando o IP e a
 porta em que o servico HTTP (Server/PoolDispatcher.java + EchoProtocol.java) esta disponivel.
 */
public class UDPDiscoveryServer {

    // Porta onde o servidor de descoberta escuta as requisicoes UDP
    private static final int DISCOVERY_PORT = 6000;

    private static final int MAX_LENGTH = 255;

    // Mensagem que o cliente deve enviar para "perguntar" pelo servico
    private static final String REQUEST_MSG = "DESCOBRIR_SERVICO_HTTP";

    // Porta em que o servico HTTP real (PoolDispatcher) esta escutando
    private static final int HTTP_SERVICE_PORT = 7500;

    public static void main(String[] args) throws Exception {

        DatagramSocket sock = new DatagramSocket(DISCOVERY_PORT);
        sock.setBroadcast(true); // habilita envio/recebimento de pacotes broadcast

        String myIp = getLocalIPAddress();

        System.out.println("Servidor de descoberta ativo na porta " + DISCOVERY_PORT);
        System.out.println("Anunciando servico HTTP em " + myIp + ":" + HTTP_SERVICE_PORT);
        System.out.println("Aguardando mensagens de descoberta...");

        for (;;) {
            try {
                // Bloqueia esperando por uma mensagem de descoberta
                DatagramPacket request = new DatagramPacket(new byte[MAX_LENGTH], MAX_LENGTH);
                sock.receive(request);

                String msg = new String(request.getData(), 0, request.getLength());
                System.out.println("Mensagem recebida de "
                        + request.getAddress().getHostAddress() + ":" + request.getPort()
                        + " -> " + msg);

                // So responde se for de fato um pedido de descoberta do servico
                if (msg.trim().equals(REQUEST_MSG)) {
                    String resposta = "SERVICO_HTTP;" + myIp + ";" + HTTP_SERVICE_PORT;
                    byte[] respBytes = resposta.getBytes();

                    // Responde diretamente (unicast) para quem enviou o broadcast
                    DatagramPacket response = new DatagramPacket(
                            respBytes, respBytes.length,
                            request.getAddress(), request.getPort());
                    sock.send(response);

                    System.out.println("Respondido para " + request.getAddress().getHostAddress()
                            + ":" + request.getPort() + " -> " + resposta);
                }
            } catch (IOException e) {
                System.out.println(e.getMessage());
            }
        }
    }

    // Procura um endereco IPv4 valido (nao loopback) desta maquina, para
    // que a resposta indique um IP que outras maquinas da rede consigam
    // efetivamente alcancar (getLocalHost() as vezes retorna 127.0.0.1).
    private static String getLocalIPAddress() throws SocketException {
        Enumeration<NetworkInterface> ifaces = NetworkInterface.getNetworkInterfaces();
        while (ifaces.hasMoreElements()) {
            NetworkInterface iface = ifaces.nextElement();
            if (!iface.isUp() || iface.isLoopback()) continue;
            Enumeration<InetAddress> addrs = iface.getInetAddresses();
            while (addrs.hasMoreElements()) {
                InetAddress addr = addrs.nextElement();
                if (addr instanceof Inet4Address && !addr.isLoopbackAddress()) {
                    return addr.getHostAddress();
                }
            }
        }
        return "127.0.0.1"; // fallback, caso nenhuma interface valida seja encontrada
    }
}