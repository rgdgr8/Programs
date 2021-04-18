import java.io.*;
import java.util.Scanner;
import java.math.*;

class Metric{
	public static final BigDecimal CONV = new BigDecimal("1.5");
        static BigDecimal KmToMile(BigDecimal km,int scale){return km.divide(CONV,scale,RoundingMode.HALF_UP);}
        static BigDecimal MileToKm(BigDecimal mile){return mile.multiply(CONV);}
	public static void main(String[] args) throws Exception{
		System.out.print("Km to Mile(1) or Mile to Km(2)? ");
		Scanner s = new Scanner(System.in);
                int opt = s.next().charAt(0);
                System.out.print("Enter value to be converted: ");
		BigDecimal v = new BigDecimal(s.next());
                if(opt=='1'){
                   int sc = v.scale();
		   System.out.println(v+" km is "+KmToMile(v,sc)+" mi");
		}
                else
		   System.out.println(v+" mi is "+MileToKm(v)+" km");
	}
}


