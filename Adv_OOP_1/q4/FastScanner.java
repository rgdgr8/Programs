import java.io.*;
import java.util.*;

public class FastScanner{

	private BufferedReader in;
	private StringTokenizer token;

	public FastScanner(FileInputStream f){
		in = new BufferedReader(new InputStreamReader(f));
		token = new StringTokenizer("");
	}

	public String next()throws IOException{
		while(!token.hasMoreElements()){
		 token = new StringTokenizer(in.readLine());
		}
		return token.nextToken();
	} 

	public int nextInt()throws IOException{
		return Integer.parseInt(next());
	}

	public long nextLong()throws IOException{
		return Long.parseLong(next());
	}
        
	public float nextFloat()throws IOException{
		return Float.parseFloat(next());
	}
       
        public String nextLine() throws IOException {
            return in.readLine();
        }
}
