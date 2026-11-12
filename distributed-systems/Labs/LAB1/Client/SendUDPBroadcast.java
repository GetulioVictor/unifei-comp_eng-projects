
import java.net.*; // for MulticastSocket, DatagramPacket and
// InetAddress
import java.io.*; // for IOException

public class SendUDPBroadcast {

    public static void main(String args[]) throws Exception {
        InetAddress destAddr = InetAddress.getByName("255.255.255.255");
        int destPort = 5000; // Destination port
        DatagramSocket sock = new DatagramSocket();
      //  sock.setTimeToLive(TTL);

        byte[] bytesToSend = "Descobrindo Servico".getBytes();

        // Create and send a datagram
        DatagramPacket message = new DatagramPacket(bytesToSend, bytesToSend.length, destAddr, destPort);
        //DatagramPacket dp= new DatagramPacket()
        sock.send(message);

        sock.close();
    }
}
