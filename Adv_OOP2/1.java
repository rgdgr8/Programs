import java.util.*;
import java.io.*;
     
class BankAcct{
	static int accns = 1;
	private int accn;
	private float balance;
	private static float interest = 10.0f;
	BankAcct(float balance){this.balance = balance;accn = accns++;}
	static void setInterestRate(float intrst){interest = intrst;}
	void showInterestRate(){System.out.println("Interest Rate: "+interest);}
	void showBalance(){System.out.println("Balance: "+balance);}
	float calcInterestAmount(){return balance*interest*0.01f;}
        void showAccountNumber(){System.out.println("Account Number: "+accn);}

	public static void main(String[] args) throws Exception{
          Scanner s = new Scanner(System.in);
          System.out.print("Enter balance: ");
          BankAcct b = new BankAcct(s.nextFloat());
          b.showAccountNumber();
          b.showInterestRate();
          b.showBalance();
          System.out.println("Current interest amount is "+b.calcInterestAmount());
          System.out.print("Set new interest rate(y/n)? ");
          if(s.next().charAt(0)=='y'){
            System.out.print("Enter new interest rate: ");
            setInterestRate(s.nextFloat());
            b.showAccountNumber();
            b.showInterestRate();
            b.showBalance();
            System.out.println("Current interest amount is "+b.calcInterestAmount());
          }
	}
}
