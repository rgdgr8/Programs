import java.io.*;
import java.util.*;

class P3{
	static String[] showTokens(String s){
		String[] words = s.split("\\s+|@|\\.\\s*");
		return words;
	}

	static void a(String s){
		int n = s.length();
		int ac = 0;
		for(int i = 0; i < n; i++)
		    if(s.charAt(i)=='a')ac++;
		System.out.println("Number of 'a' is "+ac+"\n");
	}

	static void and(String s){
		String[] words = showTokens(s);
                final String and = "and";
		int andc = 0;
		for(String x : words)
		    if(x.equals(and))andc++;
		System.out.println("Number of \"and\" is "+andc+"\n");
	}

	static void The(String s){
		boolean res = false;
		String t = s.trim();
		if(t.length()>3 && t.charAt(0)=='T' && t.charAt(1)=='h' && t.charAt(2)=='e')
		   res = true;
		System.out.println("The line starts with a \"The\": "+res+"\n");
	}

	static void showCharArray(String s){
		char[] x = s.toCharArray();
		for(char y : x)
		    System.out.print(y+" ");
		System.out.println("\n");
	}

	public static void main(String[] args) throws Exception {
		Scanner s = new Scanner(System.in);
		System.out.print("Enter line: ");
                String line  = s.nextLine();
		a(line);
		and(line);
		The(line);
		String[] words = showTokens(line);
                for(String x : words)
		    System.out.println(x);
		System.out.println("");
		showCharArray(line);	
	}
}


