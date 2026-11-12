
import java.net.*; // for Socket, ServerSocket, and InetAddress
import java.io.*; // for IOException and Input/OutputStream

public class TCPEchoServerThread {

    public static void main(String[] args) throws IOException {
        
        int echoServPort = 7500; // Server port
// Create a server socket to accept client connection requests
        ServerSocket servSock = new ServerSocket(echoServPort);
        
        for (;;) {
            try {
                Socket clntSock = servSock.accept();
                EchoProtocol protocol = new EchoProtocol(clntSock);
                Thread thread = new Thread(protocol);
                thread.start();
                System.out.println("Created and started Thread = " + thread.getName());
            } catch (IOException e) {
                System.out.println(e.getMessage());
            }
        }
        /* NOT REACHED */
    }
}
