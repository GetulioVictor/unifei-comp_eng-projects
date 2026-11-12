import java.io.IOException;
import java.net.http.*;
import java.net.*;
import java.net.http.HttpResponse.BodyHandlers;

public class Client {
    public static void main(String args[]) throws IOException, InterruptedException {
        String operacao = args.length > 0 ? args[0] : "somar";
        String valor1 = args.length > 1 ? args[1] : "10";
        String valor2 = args.length > 2 ? args[2] : "5";
        HttpClient client = HttpClient.newHttpClient();
        HttpRequest request = HttpRequest.newBuilder().uri(URI.create("http://localhost:3000/" + operacao + "/" + valor1 + "/" + valor2)).build();
        HttpResponse<String> response = client.send(request, BodyHandlers.ofString());
        System.out.println(response.body());
    }
}
