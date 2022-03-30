import java.io.*;
import java.net.*;

public class Client {
    public static void main(String[] args) {
        try {
            Socket client = new Socket("127.0.0.1", 7943);
            InputStream in = client.getInputStream();
            BufferedReader bin = new BufferedReader(new InputStreamReader(in));

            String line;
            while((line = bin.readLine()) != null)
                System.out.println(line + " test");

            client.close();
        } catch (IOException e) {
            System.err.println(e);
        }

    }
}
