import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;

class ServerClient implements Runnable {
    private Socket s;
    private HashMap<Integer, HashMap<String, String>> mm;

    ServerClient(Socket s, HashMap<Integer, HashMap<String, String>> m) {
        this.s = s;
        this.mm = m;
    }

    public void run() {
        try {
            try (DataInputStream din = new DataInputStream(s.getInputStream());
                    DataOutputStream dout = new DataOutputStream(s.getOutputStream())) {
                String[] client = din.readUTF().split("/");// if manager asks for someone else's KV-store, this will be
                                                           // of the form managerId/other-clientId
                boolean isManager = false;
                if (client.length > 1) {
                    for (String s : Constants.MANAGERS) {
                        if (s.equals(client[0])) {
                            isManager = true;
                            break;
                        }
                    }
                }
                int clientId;// servers gets the client's id
                String comm = "from";
                if (isManager) {
                    clientId = Integer.parseInt(client[1]);
                    comm = "about";
                } else {
                    if (client.length > 1) {
                        dout.writeUTF(Constants.ERROR);
                        return;
                    }

                    clientId = Integer.parseInt(client[0]);
                }
                dout.writeUTF("");//to signal that access is authorised
                
                HashMap<String, String> m = mm.get(clientId);// then gets that particular client's key-value store
                if (m == null) {
                    m = new HashMap<String, String>();
                    mm.put(clientId, m);
                }

                String wreq = din.readUTF();
                System.out.println("Request " + comm + " client" + clientId + ": " + wreq);
                String[] request = wreq.split(" ");// gets one request
                List<String> responses = new ArrayList<>();
                while (!request[0].equals(Constants.EXIT)) {// serves request until EXIT signal is read
                    if (request[0].equals(Constants.PUT)) {
                        m.put(request[1], request[2]);
                    } else if (request[0].equals(Constants.GET)) {
                        String x = m.get(request[1]);
                        if (x == null) {
                            x = "";
                        }
                        responses.add(x);
                    }
                    wreq = din.readUTF();
                    System.out.println("Request " + comm + " client" + clientId + ": " + wreq);
                    request = wreq.split(" ");
                }

                for (String response : responses) {
                    dout.writeUTF(response);
                    dout.flush();
                }
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}

public class Server {
    public static void main(String[] args) throws Exception {
        HashMap<Integer, HashMap<String, String>> kvStores = new HashMap<>();
        try (ServerSocket ssocket = new ServerSocket(Constants.PORT)) {
            while (true) {
                Socket s = ssocket.accept();
                Thread t = new Thread(new ServerClient(s, kvStores));
                t.start();
            }
        }
    }
}
