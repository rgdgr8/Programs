import java.io.*;
import java.util.*;
import classes.FastScanner;

class Main{
	public static void main(String[] args) throws IOException{
		FastScanner s = new FastScanner();
                System.out.print("Enter file name: ");
                String fn = s.next();
                File f = new File(fn);
                if(!f.exists() || !f.canRead()){
                   System.out.println("Can't work with "+fn);
                   System.exit(0);
                }
               
                BufferedReader br = new BufferedReader(new FileReader(f));
                StringTokenizer st = null;
                String tt = br.readLine();
                int line = 1;
                HashMap<String,LinkedHashSet<Integer>> hm = new HashMap<>();

                while(tt!=null){
                  tt = tt.toLowerCase().replaceAll("\\p{Punct}","");
                  st = new StringTokenizer(tt);
                  while(st.hasMoreTokens()){
                      String x = st.nextToken();
                      LinkedHashSet<Integer> lhs = null;
                      if(hm.get(x)==null)
                        lhs = new LinkedHashSet<>();
                      else
                        lhs = hm.get(x);
                      lhs.add(line);
                      hm.put(x,lhs);
                  }
                  tt = br.readLine();
                  line++;
                }

                for(Map.Entry<String,LinkedHashSet<Integer>> me : hm.entrySet()){
                   System.out.print(me.getKey()+": ");
                   for(Integer i : me.getValue())
                      System.out.print(i+" ");
                   System.out.println("");
                }
	}
}
