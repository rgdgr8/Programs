import java.io.*;
import java.util.*;
import java.lang.reflect.*;
	
@SuppressWarnings("serial")
class MyException extends Exception{
	MyException(String s){super(s);}
}
@SuppressWarnings("serial")
class MyWrapper{
	private Number data;
	MyWrapper(Number data){this.data = data;}
	Number value(){Number x = data;return x;}
	void setVal(Number d){data = d;}
	static Number valueOf(String s) throws Exception {
		return (Number)Double.valueOf(s);
	}
	public String toString(){return String.valueOf(data);}	    

private static final Scanner s = new Scanner(System.in);	
	public static void main(String[] args) throws Exception {

	Class<?> cl;//this is used during input to get any particular data type without having to know which class's valueOf(String) or parse method to call during compile time

	      try{
		System.out.print("Enter numeric class name: ");
		String cn = s.next();
		cn = cn.substring(0,1).toUpperCase() + cn.substring(1);
		cl = Class.forName("java.lang."+cn);
		System.out.print("Enter a "+cn+" value: ");
                Method m = cl.getDeclaredMethod("valueOf",String.class);
                MyWrapper mw = new MyWrapper((Number)m.invoke(null,s.next()));
	        System.out.println(mw.value());
		System.out.print("Enter a new "+cn+" value to set: ");
		mw.setVal((Number)m.invoke(null,s.next()));
	        System.out.println(mw.value());

		System.out.print("Enter a string for a "+cn+" value: ");
		Number a = MyWrapper.valueOf(s.next());
		System.out.println(a);
	     }catch(InvocationTargetException e){
		throw new MyException("Incompatible type");
	     } 
	}
}


