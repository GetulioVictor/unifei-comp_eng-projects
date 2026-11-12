
import java.net.*; // for Socket
import java.io.*; // for IOException and Input/OutputStream

public class TCPEchoClient {

    public static void main(String[] args) throws IOException {
        String server = "localhost";
// Convert input String to bytes using the default character
// encoding
        byte[] byteBuffer = "Mensagem a ser ecoada!".getBytes();
        int servPort = 7500;
// Create socket that is connected to server on specified port
        Socket socket = new Socket(server, servPort);
        System.out.println("Connected to server... sending echo string");
        InputStream in = socket.getInputStream();
        OutputStream out = socket.getOutputStream();
        out.write(byteBuffer); // Send the encoded string to the server
        in.read(byteBuffer);
        System.out.println("Received: " + new String(byteBuffer));
        socket.close();
    }
}
