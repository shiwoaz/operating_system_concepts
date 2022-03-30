import java.net.*;
import java.io.*;

public class Server {
    public static void main(String[] args) {
        try {
            try (ServerSocket sock = new ServerSocket(7943)) {
                while (true) {
                    Socket client = sock.accept();
                    PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
                    pout.println(new java.util.Date().toString() + " " + client.getInetAddress() + " " + client.getPort());
                    client.close();
                }
            }
        } catch (IOException e) {
            System.err.println(e);
        }
    }
}
