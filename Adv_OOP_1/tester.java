import java.io.*;
import java.util.*;
import classes.FastScanner;

class Main{
	public static void main(String[] args) throws IOException{
           FastScanner s = new FastScanner();
           StringTokenizer st = new StringTokenizer(s.nextLine());
           while(st.hasMoreTokens())
                System.out.println(st.nextToken()); 
        }
}
