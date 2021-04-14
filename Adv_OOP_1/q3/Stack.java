import java.io.*;
import java.util.*;

public class Stack<T>{
  private class Node{
     T value;
     Node next;
     Node prev = null;
     Node(T v){value = v; next = null;}
  }

  private Node top = null;
  
  public void push(T v){
    Node newNode = new Node(v);
    if(top!=null){top.next = newNode; newNode.prev = top;}
    top = newNode;
  }

  public T pop(){
    if(top==null) return null;
    T x = top.value;
    top = top.prev;
    return x;
  }

  public T peek(){
    return top.value;
  }

  public boolean empty(){return top==null;}
}
