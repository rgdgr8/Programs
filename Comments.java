package classes;
import java.io.*;
import java.util.*;
import java.util.regex.*;

public class Comments{
	public static final Pattern pat = Pattern.compile("(?://(.+))|(?:/\\*((?:.|\\n)*?)\\*/)");

	public static void main(String[] args) throws Exception {
		Scanner s = new Scanner(System.in);
		String fn = null;
		File f = null;
		BufferedReader br = null;
		
		boolean readable;
	        do{
		 readable = true;
		 try{
		  System.out.print("Enter filename which is to be parsed: ");
		  fn = s.next().trim();
		  f = new File(fn);
		  br = new BufferedReader(new FileReader(f));
		 }catch(Exception e){System.out.println(e.getMessage());readable = false;}
		}while(!readable);

		System.out.print("Enter filename where the result will be stored: ");
		fn = s.next().trim();
		f = new File(fn);
		f.createNewFile();//creates new file if file does not exist
		
		System.out.print("Enter 1 to overwrite, any other key to append: ");
		boolean append = true;
		char app = s.next().trim().charAt(0);
		if(app=='1')
		   append = false;
		final PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(f,append)));

		StringBuilder sb = new StringBuilder("");
		String x = br.readLine();
		while(x!=null){//extract and store the entire text file in a String 
			sb.append(x);
			sb.append("\n");
		        x = br.readLine();
		}
		
		//System.out.println("Final string:\n"+sb.toString());
		Matcher mat = pat.matcher(sb.toString());
		boolean found = false;
		while(mat.find()){
                  try{
		     for(int i=1;;i++){
			String mg = mat.group(i);
			if(mg!=null){
				found = true;
				System.out.println(mg);
				pw.println(mg);
			}
		     }
		  }catch(Exception e){/*e.printStackTrace();*/}
		}

		if(!found) System.out.println("No match");
		pw.close();
	}
}


