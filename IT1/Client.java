import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;

public class Client {
    public static void main(String[] args) throws Exception {
        if (args.length < 5) {
            System.out.println(Constants.INSUFF_ARGS);
            return;
        }
        String host = args[0];//hostname of server
        int port = Integer.parseInt(args[1]);//port number of server
        String clientId = args[2];//client Id to uniquely identify this client
        try (Socket s = new Socket(host, port);
            DataOutputStream dout = new DataOutputStream(s.getOutputStream());
            DataInputStream din = new DataInputStream(s.getInputStream())){
            dout.writeUTF(clientId);//send client id to server
            if(din.readUTF().equals(Constants.ERROR)){//if authorization fails
                System.out.println(Constants.UNAUTH);
                return;
            }
            int i = 3;
            int gets = 0;
            String x;
            while(i<args.length){
                args[i] = args[i].toUpperCase();
                if(args[i].equals(Constants.PUT)){
                    if(i+2<args.length){
                        x = args[i]+" "+args[i+1]+" "+args[i+2];
                        dout.writeUTF(x);
                        dout.flush();
                        //System.out.println("Request: "+ x);
                        i += 3;
                    }else{
                        System.out.println(Constants.INSUFF_ARGS);
                        return;
                    }
                }else if(args[i].equals(Constants.GET)){
                    if(i+1<args.length){
                        x = args[i]+" "+args[i+1];
                        dout.writeUTF(x);
                        dout.flush();
                        //System.out.println("Request: "+ x);
                        gets++;
                        i += 2;
                    }else{
                        System.out.println(Constants.INSUFF_ARGS);
                        return;
                    }
                }
            }
            dout.writeUTF(Constants.EXIT);//signal the end to the server
            
            while(gets-->0){//getting responses
                System.out.println(din.readUTF());
            }
        }
    }
}
