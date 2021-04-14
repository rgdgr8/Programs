import java.io.*;
import java.util.*;
import java.time.*;

class Quotes{
  private ArrayList<String> quotes;
  private static final Random rand = new Random();
  private LocalDateTime ldt;
  private int[] last = null; //last few shown quotes, so that same quotes are not repeatedly implemented as an circular queue.
  private int lastIndex = -1;
  private int rotateListIndex(int i,int size,int frontIndex){if(i>=(size-1))return frontIndex;return ++i;}
  private void pushLast(int i){ lastIndex = rotateListIndex(lastIndex,last.length,0); last[lastIndex] = i;}
  
  public Quotes(int lastSize) throws Exception{
   quotes = new ArrayList<>();
   quotes.add("Independence Day");
   quotes.add("Teachers' Day");
   quotes.add("God helps them that help themselves. -- Benjamin Franklin");
   quotes.add("Happiness is not a reward - it is consequence. Suffering is not a punishment - it is a result. -- Robert Green Ingersoll");
   quotes.add("Future. That period of time in which our affairs prosper, our friends are true and our happiness is assured. -- Ambrose Bierce");
   quotes.add("Honesty is the first chapter of the book of wisdom. --Thomas Jefferson");
   quotes.add("book of wis--Thomas Jefferson");
   quotes.add("--Thomas Jefferson");
   quotes.add("--Tho");
   quotes.add("--");
   
   last = new int[lastSize];
   
   FileInputStream f = null;
   try{
      f = new FileInputStream(new File("lasts.txt"));
   }catch(Exception e){System.out.println("Error in opening file");}
   FastScanner s = new FastScanner(f);

   int i;
   for(i=0;i<lastSize;i++) last[i] = quotes.size();
   for(i=0;i<lastSize;i++){
       try{
        last[i] = s.nextInt();
       }catch(Exception e){/*System.out.println("Error while reading");e.printStackTrace();*/}
   }
 
   try{
      lastIndex = s.nextInt();
      f.close();
   }catch(Exception e){/*System.out.println("Error while reading lastIndex");e.printStackTrace();*/}

 }
  
  public int[] getLasts(){
     int[] x = new int[last.length];
     for(int i=0;i<x.length;i++)
        x[i] = last[i];
     return x;
  }

  public int getLastIndex(){return lastIndex;}
  
  //public void addQuote(String s){quotes.add(s);}
  public void show(){
    ldt =LocalDateTime.now();
    int month = ldt.getMonthValue();
    int day = ldt.getDayOfMonth();
    //System.out.println("dd/mm = " + day + "/" + month);
    if(month==8 && day==15)
      System.out.println(quotes.get(0));
    else if(month==9 && day==5)
      System.out.println(quotes.get(1));
    else{
      int i = rand.nextInt((quotes.size()-2))+2;
      int[] temp = new int[last.length];
      for(int k=0;k<last.length;k++) temp[k] = last[k];
      Arrays.sort(temp);
      /*for(int l : temp){System.out.print(l+" ");}
      System.out.println("  i="+i);*/
      
      for(int j=0;j<temp.length;j++){
         if(i==temp[j]){
            i = rotateListIndex(i,quotes.size(),2);
            if(j==(temp.length-1))
               j=-1;
         }
         else if(i<temp[j]) break;
      }
      pushLast(i);
      /*for(int l : last){System.out.print(l+" ");}
      System.out.println("  i="+i);*/
      System.out.println(quotes.get(i));
    }
  }
}

class QuoteOfTheDay{
	public static void main(String[] args) throws Exception{
               try {
                   File myObj = new File("lasts.txt");
                   if (myObj.createNewFile()) {
                   System.out.println("File created: " + myObj.getName());
                   } //else {
                   //System.out.println("File already exists.");
                   //}
               } catch (IOException e) {
                   System.out.println("An error occurred while creating file");
                   e.printStackTrace();
                   return;
               }

               Quotes q = new Quotes(2);int x[] = null; int y = -1;
               //while(s.nextInt()!=0)
                q.show();
                try {
                     FileWriter myWriter = new FileWriter("lasts.txt");
                     x = q.getLasts();
                     y = q.getLastIndex();
                     for(int i = 0;i<x.length;i++)
                         myWriter.write(x[i]+" ");
                     myWriter.write("\n"+y);
                     myWriter.close();
                     //System.out.println("Successfully wrote to the file.");
                } catch (IOException e) {
                     System.out.println("An error occurred while writing into file");
                     e.printStackTrace();
                }

                //for(int i=0;i<x.length;i++) System.out.print(x[i] + " ");
                //System.out.println("\n"+y);
	}
}
