
import java.net.*; // for MulticastSocket, DatagramPacket and
// InetAddress
import java.io.*; // for IOException

public class RecvUDPBroadcast {

    private static final int MAX_LENGTH = 255;

    public static void main(String[] args) throws Exception {
        int port = 5000;

        DatagramSocket sock = new DatagramSocket(port);
        
        //Create and receive a datagram
        DatagramPacket packet = new DatagramPacket(new byte[MAX_LENGTH], MAX_LENGTH);
        sock.receive(packet);

        System.out.println("Handling client at "
                + packet.getAddress().getHostAddress() + " on port "
                + packet.getPort());
        System.out.println("Received: " + new String(packet.getData(),0,packet.getLength()));
        

    }
}
