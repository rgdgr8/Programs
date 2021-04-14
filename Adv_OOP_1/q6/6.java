import java.io.*;
import java.util.*;
import classes.FastScanner;

class Hospital{
  private class Patient{
     private String id;
     Patient(String ssn){id = ssn;}
     public String getPatientId(){return id;}
     public String toString(){return id;}
     public boolean equals(Object o){
        if(o==this)
          return true;
        
        if(o==null)
          return false;
     
        if(o instanceof Patient){
           Patient x = (Patient)o;
           return (x.getPatientId().equals(id));
        }
        
        return false;
     }
     public int hashCode(){return -1;}
  }

  private static int dids = 1;
  private class Doctor{
     private String name;
     private ArrayList<Patient> pa;
     Doctor(){pa = new ArrayList<>();name = "Doctor"+dids;dids++;}
     public void addPatient(Patient p){pa.add(p);}
     public void showAllReports(){
       for(Patient p : pa){
          System.out.println("Report for:");
          System.out.println(p);
       }
     }
     public boolean hasPatient(Patient p){
       int x = pa.indexOf(p);
       return (x==-1 ? false : true);
     }
     public void removePatient(Patient p){pa.remove(p);}
     public void showPatientReport(Patient p){
       System.out.println("Report for:\n"+p);
     }
     public int getNumOfPatients(){return pa.size();}
     public String toString(){return name;}
  }

  private ArrayList<Doctor> da;
  public Hospital(int doctors){da = new ArrayList<>(doctors);for(int i=0;i<doctors;i++) da.add(new Doctor());}
  private void assignDoctor(Patient p){
    int min = Integer.MAX_VALUE; int mini = -1;
    for(int i=0;i<da.size();i++){
        if(da.get(i).getNumOfPatients()<min){
           min = da.get(i).getNumOfPatients();
           mini = i;
        }
    }
    da.get(mini).addPatient(p);
  }
  public void registerPatient(String ssn){Patient p = new Patient(ssn);assignDoctor(p);}
  public void showAllRecords(){
    for(Doctor d : da){
       System.out.println("Under doctor "+d+": ");
       d.showAllReports();
    }
    System.out.println("-----------------------------------");
  }
  public void checkOut(String ssn){
     Patient p = new Patient(ssn);
     for(Doctor d : da){
        if(d.hasPatient(p)){
           d.removePatient(p);
           return;
        }
     }
     System.out.println("No such Patient Admitted");
  }
  public void showPatientReport(String ssn){
     Patient p = new Patient(ssn);
     for(Doctor d : da)
         if(d.hasPatient(p)){
           d.showPatientReport(p);
           return;
         }
     System.out.println("Patient not registered!");
  }
}

class Main{
	public static void main(String[] args) throws IOException{
               Hospital h = new Hospital(5);
               for(int i=0;i<5;i++)
                  h.registerPatient("p"+i);

               h.showAllRecords();
               h.checkOut("p1");
               h.checkOut("p12");
               h.showPatientReport("p11");
               h.showAllRecords();
	}
}
