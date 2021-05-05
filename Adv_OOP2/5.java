import java.io.*;
import java.util.*;

class Bank{
	private static int ids = 1;
	public static final double U_LIMIT = 20000.0;
	public static final double P_LIMIT = 100000.0;
	private HashMap<Integer,Customer> hm = new HashMap<>();
	Customer getCustomer(int id){return hm.get(id);}
	void loan(int id,double amount){
		Customer c = hm.get(id); if(c==null){System.out.println("No such account!");return;}
		if(c.priv && (c.loan+amount)<=P_LIMIT) c.loan += amount;
		else if(!c.priv && (c.loan+amount)<=U_LIMIT) c.loan += amount;
		else System.out.println("Insufficient Credit!");
	}
	public String toString(){
		StringBuilder s = new StringBuilder("");
		for(Integer x : hm.keySet())
		    s.append(hm.get(x));
		return s.toString();
	}

	private class Customer{
		private int id;
		private String name;
		private String number;
		private double loan = 0.0;
		private boolean priv;
		Customer(String name,String number,boolean priv){
			this.name=name;
			this.number=number;
			this.priv=priv;
			id=ids++;
			hm.put(id,this);
		}
		public String toString(){
			String x = ("Acc No: "+id+"  Name: "+name+"  Number: "+number);
			double limit = priv ? P_LIMIT : U_LIMIT;
			x += ("\nCurrent Loan Amount: "+loan+"  Seekable Loan Amount: "+(limit-loan)+"  Loan Limit: "+limit);
			x += "\n";
			return x;
		}
		void changeName(String name){this.name = name;}
		void changeNumber(String number){this.number = number;}
		int getAccNum(){return id;}
	}

	public static void main(String[] args){
		Scanner s = new Scanner(System.in);Random rand = new Random(1);
		Bank b = new Bank();
		for(int i=0;i<5;i++) b.new Customer(String.valueOf(i),""+i+i+i+i+i+i,rand.nextBoolean());
		System.out.println(b);
		do{
			System.out.println("Enter account number: ");
			Customer c = b.getCustomer(s.nextInt());
			if(c==null){System.out.println("No such account!");continue;}
			
			System.out.println("Choose an option:");
			System.out.println("1. Loan");
			System.out.println("2. Show Details");
			System.out.println("3. Change Name");
			System.out.println("4. Change Number");
			System.out.println("0. Exit");
			char x = s.next().charAt(0);
			
			switch(x){
				case '1' : System.out.println("Enter Loan amount: ");
					   b.loan(c.getAccNum(),s.nextDouble());break;

				case '2' : System.out.println(c);break;

				case '3' : System.out.println("Enter new Name: ");
					   s.skip("\\s+");c.changeName(s.nextLine());break;

				case '4' : System.out.println("Enter new Number: ");
					   s.skip("\\s+");c.changeNumber(s.nextLine());break;

				case '0' : continue;

				default : System.out.println("Invalid option!");
			}
		}while(true);
	}	
}


