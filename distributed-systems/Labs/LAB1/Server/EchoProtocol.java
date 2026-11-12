
import java.net.*; // for Socket
import java.io.*; // for IOException and Input/OutputStream

// Le e imprime a requisicao HTTP no terminal, monta uma resposta HTTP com
// uma pagina HTML, imprime essa resposta no terminal tambem, e so entao
// envia ela de volta para o Browser.
class EchoProtocol implements Runnable {

    private Socket clntSock; // Connection socket

    public EchoProtocol(Socket clntSock) {
        this.clntSock = clntSock;
    }

    public void run() {
        System.out.println("Client address and port = " + clntSock.getInetAddress().getHostAddress() + ":" + clntSock.getPort());
        System.out.println("Thread = " + Thread.currentThread().getName());
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(clntSock.getInputStream()));
            OutputStream out = clntSock.getOutputStream();

            // Le e loga a linha de requisicao (ex.: "GET / HTTP/1.1")
            String requestLine = in.readLine();
            System.out.println("Requisicao HTTP: " + requestLine);

            // Le e loga os demais cabecalhos ate a linha em branco que
            // marca o fim da requisicao HTTP
            String header;
            while ((header = in.readLine()) != null && !header.isEmpty()) {
                System.out.println("Header: " + header);
            }

            // Monta o corpo (HTML) e os cabecalhos da resposta HTTP
            String html =
                "<!DOCTYPE html>\n" +
                "<html>\n" +
                "<head><meta charset=\"UTF-8\"><title>Servidor HTTP Multithread</title></head>\n" +
                "<body>\n" +
                "  <h1>Ola! Servidor HTTP multithread em Java</h1>\n" +
                "  <p>Requisicao recebida: " + requestLine + "</p>\n" +
                "  <p>Atendido pela thread: " + Thread.currentThread().getName() + "</p>\n" +
                "</body>\n" +
                "</html>\n";
            byte[] body = html.getBytes("UTF-8");

            String responseHeaders =
                "HTTP/1.1 200 OK\r\n" +
                "Content-Type: text/html; charset=UTF-8\r\n" +
                "Content-Length: " + body.length + "\r\n" +
                "Connection: close\r\n" +
                "\r\n";

            // Imprime a resposta completa no terminal antes de envia-la
            System.out.println("---- Resposta HTTP enviada ----");
            System.out.print(responseHeaders);
            System.out.println(html);
            System.out.println("--------------------------------");

            out.write(responseHeaders.getBytes("UTF-8"));
            out.write(body);
            out.flush();

            clntSock.close();
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
