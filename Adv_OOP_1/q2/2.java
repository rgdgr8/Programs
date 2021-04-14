import java.io.*;
import java.util.*;
import classes.FastScanner;

class Item{
  private String code;
  private String name;
  private float rate;
  private int qty;
  private String genCode(int qty){
    String x = String.valueOf(qty);
    if(qty<10)
      x = "00"+qty;
    else if(qty<100)
      x = "0"+qty;

    return x;
  }
  public Item(String name,float rate,int qty){
    this.code = (name.toUpperCase() + genCode(qty));
    this.name = name;
    this.rate = rate;
    this.qty = qty;
  }
  public void changeRate(float newRate){rate = newRate;}
  public void changeQty(int newQty){qty = newQty;}
  public int getQty(){return qty;}
  public float getPrice(){return rate;}
  public String getCode(){return code;}
  public String getName(){return name;}
  public String toString(){return (name+" "+qty+" "+rate+" "+code);}
  public boolean equals(Object o){
   if(o==this) return true;
   if(!(o instanceof Item)) return false;
   Item x = (Item)o;
   return x.getCode().equals(code);
  }
  public int hashCode(){return -1;}
}

class ItemList{
  private static FastScanner s = new FastScanner();
  private ArrayList<Item> il;
  private int desig = 1;//default designation for SEO
  private Item check(String code){//5
    for(Item i : il)
       if(i.getCode().equals(code))
         return i;
       
     return null;
  }

  private ArrayList<Item> checkName(String name){
    ArrayList<Item> it = new ArrayList<Item>();
    for(Item i : il)
       if(i.getName().equals(name))
         it.add(i);
       
     return it;
  }

  private ItemList(int items){
    il = new ArrayList<Item>();
    for(int i=0;i<items;i++){
       String name="";float rate=-1;int qty=-1;
      while(qty==-1){
       try{
        name = s.next();rate = s.nextFloat();qty = s.nextInt();
       }catch(Exception e){System.out.println("Invalid Input(s), Try Again.");qty=-1;}
      }
       il.add(new Item(name,rate,qty));
    }
    System.out.println("Signed in as SEO");
  }
  private ItemList(Item[] i){il = new ArrayList<Item>();Collections.addAll(il,i);System.out.println("Signed in as SEO");}

  public static ItemList getInstance(int desig,int items){
   if(desig!=1){System.out.println("Unauthorised! Have to be SEO to access this method");return null;}
   ItemList i = new ItemList(items);return i;
  }
  public static ItemList getInstance(int desig,Item[] items){
   if(desig!=1){System.out.println("Unauthorised! Have to be SEO to access this method");return null;}
   ItemList i = new ItemList(items);return i;
  }

  public void changeDesig(){
   if(desig!=1){desig = 1;System.out.println("Signed in as SEO");}
   else{desig = 2;System.out.println("Signed in as ShopKeeper");}
  }

  public static int input(String st){
    int x=-1;
    while(x==-1){
     System.out.print(st);
     try{
      x = s.nextInt();
     }catch(Exception e){System.out.println("Invalid Input, Try Again.");x=-1;}
    }
    return x;
  }

  public void addNewItem(){//2
   if(desig!=1){System.out.println("Unauthorised! Have to be SEO to access this method");return;}
   int x = 1;
   while(x!=0){
    System.out.print("Enter Item Name,Rate,Quantity: ");
    Item it = null;
    try{
     it = new Item(s.next(),s.nextFloat(),s.nextInt());
    }catch(Exception e){System.out.println("Invalid Input(s)");return;}
    if(il.contains(it))System.out.println("Item Already exists");
    else {il.add(it);System.out.println("Item Added");}
    x = input("Add more items (yes=1,no=0): ");
   }
  }

 public void updateStock(String code){//4
   Item i = check(code);
   if(i!=null){
      int x = input("Issued or received? (issued=1,received=2): ");
      if(x==1){
        x = input("How many issued: ");
        if(x>i.getQty())System.out.println("Insufficient stock");
        else i.changeQty((i.getQty()-x));
      }
      else{
        x = input("How many received: ");
        i.changeQty((i.getQty()+x));
      }
   }else
      System.out.println("No item found with itemcode "+code);
 }

 public void changeRate(String code){//3
   if(desig!=1){System.out.println("Unauthorised! Have to be SEO to access this method");return;}
   Item i = check(code);
   if(i!=null){
     float x=0;
     while(x==0){
      System.out.print("Enter New Rate: ");
      try{
       x = s.nextFloat();
      }catch(Exception e){System.out.println("Invalid Input, Try Again.");x=0;}
     }
      i.changeRate(x);
   }else
      System.out.println("No item found with itemcode "+code);
 }

 public void getDetailsByName(String name){//6
    ArrayList<Item> i = checkName(name);
    if(i.size()<=0) System.out.println("No item exists with name "+name);
    else for(Item it : i) System.out.println(it.toString());
 }
 public void getDetails(String code){//6
    Item i = check(code);
    if(i==null) System.out.println("No item exists with code "+code);
    else System.out.println(i.toString());
 }
 
 public void itemsMoreThan(float amount){//7
   boolean e = false;
   for(Item i : il)
      if(i.getPrice()>amount){
        System.out.println(i.toString());
        e = true;
      }
 
   if(e==false)
     System.out.println("No item with price less than " + amount);
 }

 public String toString(){
  StringBuilder x = new StringBuilder("");
  for(Item i : il){
     x.append(i.toString()).append("\n-----------------------------\n");
  } 
  return x.toString();
 }
}

class Main{
	public static void main(String[] args) throws IOException{
		FastScanner s = new FastScanner();
                Item[] y = new Item[5];
                for(int i=1;i<6;i++)
                    y[i-1] = new Item("Item"+i,(float)(i*5.5),i*3);
                ItemList il = null;int x;
               while(il==null){
                x = ItemList.input("SEO or ShopKeeper (SEO=Any key other than 2,Shopkeeper=2): ");
                if(x!=2)x=1;
                il = ItemList.getInstance(x,y);
               }
                System.out.println(il);
                while(true){
                  x = ItemList.input("Choose an option (1=change user,2=add new item,3=change rate,4=update stock,5=get details,6=items more a given amount,7=display, Escape=8): ");
                  if(x==8) break;
                  switch(x){
                    case 1: 
                    x = ItemList.input("SEO or ShopKeeper (SEO=Any key other than 2,Shopkeeper=2): ");
                    if(x!=2)x=1;
                    il.changeDesig();break;
                    case 2:
                    il.addNewItem();break;
                    case 3:
                    try{System.out.print("Enter code: "); String code = s.next(); il.changeRate(code);}
                    catch(Exception e){System.out.println("Invalid Input code");}
                    break;
                    case 4:
                    try{System.out.print("Enter code: "); String code = s.next(); il.updateStock(code);}
                    catch(Exception e){System.out.println("Invalid Input code");}
                    break;
                    case 5:
                    x = ItemList.input("Get details by name or code (name=1,code=2): ");
                    if(x==2){
                     try{System.out.print("Enter code: "); String code = s.next(); il.getDetails(code);}
                     catch(Exception e){System.out.println("Invalid Input code");}
                    }else{
                     try{System.out.print("Enter name: "); String name = s.next(); il.getDetailsByName(name);}
                     catch(Exception e){System.out.println("Invalid Input name");}
                    }
                    break;
                    case 6:
                    x = ItemList.input("Enter amount: ");
                    il.itemsMoreThan(x);
                    break;
                    case 7:
                    System.out.println(il);break;
                    default: System.out.println("Invalid option");
                  }
                }
	}
}
