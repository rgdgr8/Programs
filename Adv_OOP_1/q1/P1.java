import java.util.*;
import java.util.regex.Pattern;

class STUDENT {
    protected String roll = null; //structured as defined in the description; for this version it has only year (first 2 digits) and count.
    private String name = null;
    private String course = null;
    private Date admission = null; //Admission date
    static final int NUM_SUBJECTS = 5;
    private float marks[] = null; //Marks

    static final int STUDENT_ARRAY_SIZE = 1024;
    private static STUDENT students[] = new STUDENT[STUDENT_ARRAY_SIZE];
    static STUDENT[] getStudents(){STUDENT x[] = students.clone(); return x;}
    private static int studentsAdmitted = 0;
    static int numStudentsAdmitted() {return studentsAdmitted;}
    static STUDENT search(String r) {
        for(int i = 0; i < studentsAdmitted; i++) if(students[i].roll.equals(r)) return students[i];
        return null; //if not found
    }
    static boolean remove(String r) {//Remove student with given roll
        int i;
        for(i = 0; i < studentsAdmitted; i++) if(students[i].roll.equals(r)) break;
        if(i >= studentsAdmitted) return false;
        for(; i < studentsAdmitted-1; i++) students[i] = students[i+1];
        students[i] = null; //Allow garbage collection
        studentsAdmitted--; return true;
    }

    void input() {//True when valid object has been entered
        System.out.print("Enter name: "); P1.in.skip(Pattern.compile("\\s*")); name = P1.in.nextLine();
        System.out.print("Enter course: "); course = P1.in.nextLine();
    }

    String getRoll() {return roll;} //may be null if not admitted yet
    String getName() {return name;}
    String getCourse() {return course;}
    Date getAdmissionDate() {return admission;}
    boolean isAdmitted() {return roll != null && admission != null;} //Check if admitted?
    boolean isEvaluated() {return isAdmitted() && marks != null;} //Check if evaluated (marks given)
    //Get marks of subject subNum(1..5). return -1 if not evaluated.
    float getMarksOfSubject(int subNum) {return isEvaluated() ? -1 : marks[subNum-1];}
    float getTotalMarks() {
        if(marks == null) return -1;
        float sum = 0; for(float m : marks) sum += m; return sum;
    }

    void admit() {//Admit student in
        admission = new Date();
        roll = String.format("%ty_%04d", admission, studentsAdmitted + 1);
        students[studentsAdmitted] = this; studentsAdmitted++;
    }
    void evaluate() {//Give marks
        System.out.print("Enter marks of "+NUM_SUBJECTS+" subjects: ");
        marks = new float[NUM_SUBJECTS];
        for(int i = 0; i < NUM_SUBJECTS; i++) marks[i] = P1.in.nextFloat();
    }

    boolean printMarkSheet() {
        System.out.println("Student roll: "+roll);
        System.out.println("Name: "+name);
        System.out.println("Course: "+course);
        if(!isAdmitted()) {System.err.println("Student not admitted!"); return false;}
        System.out.printf("Admission date: %td %tB %tY\n", admission, admission, admission);
        if(!isEvaluated()) {System.err.println("Student not evaluated yet."); return false;}
        System.out.print("Marks of "+NUM_SUBJECTS+" subjects: ");
        for(int i = 0; i < NUM_SUBJECTS; i++) System.out.printf("%5.2f ", marks[i]);
        System.out.println(); return true;
    }

    static void showAllStudents(){
       for(STUDENT s : students)
          if(s!=null){
            s.printMarkSheet();
            System.out.println("------------------------------");
          }
    }

    public String toString() {return "("+roll+")"+name;}
}

class DepartmentalStudent extends STUDENT {
    //number of students in each department
    private static final HashMap<String, Short> numStudents = new HashMap<String, Short>();
    static short numStudents(String dept_code) 
        {return (numStudents.containsKey(dept_code)) ? numStudents.get(dept_code) : 0;}
    static void printAllDeptNumbers() {//Print number of students admitted in each department
        if(numStudents.isEmpty()) return;
        for(String dept : numStudents.keySet()) System.out.println(dept+": "+numStudents.get(dept)+" students");
    }
    private String dept; //department code
    String getDept() {return dept;}
    @Override void input() {
        super.input();
        System.out.print("Enter department code: ");
        dept = String.format("%4s", P1.in.next()).replace(' ', '0');
    }
    @Override void admit() {
        super.admit();
        short count = numStudents(dept);
        roll = String.format("%4s_%ty_%04d", dept, super.getAdmissionDate(), count+1);
        numStudents.put(dept, (short)(count+1)); //manual boxing is necessary
    }
    /*@Override boolean printMarkSheet() {
        System.out.printf("Student Department Code: %04s\n", dept);
        return super.printMarkSheet();
    }*/
    static final Comparator<DepartmentalStudent> RANKED_ONMARKS = new Comparator<DepartmentalStudent>() {
        public int compare(DepartmentalStudent a, DepartmentalStudent b) 
            {return Float.compare(b.getTotalMarks(), a.getTotalMarks());}
    };
}

public class P1 {
    static final Scanner in = new Scanner(System.in);
    public static void main(String args[]) {
        System.out.println("1. Add Student");
        System.out.println("2. Assign marks to student (evaluate)");
        System.out.println("3. Print Mark Sheet of Student");
        System.out.println("4. How many students have taken admission?");
        System.out.println("5. Get Ranked List by Department (on total/average marks)");
        System.out.println("6. Remove student");
        System.out.println("7. Display all Students");
        System.out.println("0. Exit");
        int choice; STUDENT s; char choice2; String roll, dept;
        Runtime r = Runtime.getRuntime(); long mem;
        ArrayList<DepartmentalStudent> temp;
        do {
            System.out.print("Enter choice: "); choice = in.nextInt();
            switch(choice) {
            case 1:
                System.out.print("Is Departmental Student? [y/n] "); choice2 = Character.toLowerCase(in.next().charAt(0));
                s = (choice2 == 'y') ? new DepartmentalStudent() : new STUDENT();
                s.input();
                s.admit(); System.out.println("Student Admitted: "+s);
                break;
            case 2:
                System.out.print("Enter Roll Number: "); roll = in.next();
                if((s = STUDENT.search(roll)) == null) System.err.println("Student Not Found");
                else {System.out.print(s+": "); s.evaluate();}
                break;
            case 3:
                System.out.print("Enter Roll Number: "); roll = in.next();
                if((s = STUDENT.search(roll)) == null) System.err.println("Student Not Found");
                else s.printMarkSheet();
                break;
            case 4:
                DepartmentalStudent.printAllDeptNumbers();
                System.out.println("In total, "+STUDENT.numStudentsAdmitted()+" students have taken admission."); break;
            case 5:
                System.out.print("Enter Department Code: "); dept = in.next();
                if(DepartmentalStudent.numStudents(dept) == 0) {
                    System.out.println("No student in this department.");
                    break;
                }
                temp = new ArrayList<DepartmentalStudent>(); temp.ensureCapacity(DepartmentalStudent.numStudents(dept));
                STUDENT[] x = STUDENT.getStudents();
                for(int i = 0; i < STUDENT.numStudentsAdmitted(); i++)
                    if(x[i] instanceof DepartmentalStudent) {
                        DepartmentalStudent ds = (DepartmentalStudent) x[i];
                        if(ds.getDept().equals(dept)) temp.add(ds);
                    }
                Collections.sort(temp, DepartmentalStudent.RANKED_ONMARKS);
                System.out.println("Marks\tStudent");
                for(DepartmentalStudent ds : temp) {
                    System.out.printf("%.2f\t%s", ds.getTotalMarks(), ds.toString());
                    if(!ds.isEvaluated()) System.out.println("\t(Not Evaluated)");
                    else System.out.println();
                }
                break;
             case 6:
                System.out.print("Enter Roll Number: "); roll = in.next();
                if((s = STUDENT.search(roll)) == null) {System.err.println("Student Not Found"); break;}
                System.out.print("Deleting "+s+" ... ");
                STUDENT.remove(roll); 
                r.gc(); mem = r.freeMemory(); 
                s = null;
                r.gc(); mem = r.freeMemory() - mem;
                System.out.println("Memory freed: "+mem+" bytes");
                break;
             case 7: STUDENT.showAllStudents();break;
             case 0: return;
             default: System.err.print("Invalid Option! ");
            }
        } while (choice != 0);
    }    
}
