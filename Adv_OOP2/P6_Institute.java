import java.util.*;
import java.util.regex.Pattern;

class Address {
    private String premises; //premises number
    String getPremisesNumber() {return premises;}
    private String street; //street name
    String getStreetName() {return street;}
    private String city; //city name
    String getCityName() {return city;}
    private int pin; //PIN number
    int getPIN() {return pin;}
    private String state; //state name
    String getStateName() {return state;}

    Address() {
        System.out.print("Enter premises number: "); premises = P6.in.next();
        System.out.print("Enter street name: "); P6.in.skip(P6.ws); street = P6.in.nextLine();
        System.out.print("Enter city name: "); P6.in.skip(P6.ws); city = P6.in.nextLine();
        System.out.print("Enter PIN: "); pin = P6.in.nextInt();
        System.out.print("Enter state name: "); P6.in.skip(P6.ws); state = P6.in.nextLine();
    }
    void update() {
        System.out.print("Premises number: "+premises+"\nDo you want to change this value? [Y/N] ");
        if(P6.in.next().toLowerCase().charAt(0) == 'y') {System.out.print("Enter premises number: "); premises = P6.in.next();}
        System.out.print("Street name: "+street+"\nDo you want to change this value? [Y/N] ");
        if(P6.in.next().toLowerCase().charAt(0) == 'y') {System.out.print("Enter street name: "); P6.in.skip(P6.ws); street = P6.in.nextLine();}
        System.out.print("City name: "+city+"\nDo you want to change this value? [Y/N] ");
        if(P6.in.next().toLowerCase().charAt(0) == 'y') {System.out.print("Enter city name: "); P6.in.skip(P6.ws); city = P6.in.nextLine();}
        System.out.print("PIN: "+pin+"\nDo you want to change this value? [Y/N] ");
        if(P6.in.next().toLowerCase().charAt(0) == 'y') {System.out.print("Enter PIN: "); pin = P6.in.nextInt();}
        System.out.print("State name: "+state+"\nDo you want to change this value? [Y/N] ");
        if(P6.in.next().toLowerCase().charAt(0) == 'y') {System.out.print("Enter state name: "); P6.in.skip(P6.ws); state = P6.in.nextLine();}    
    }
    @Override public String toString() {return premises+" "+street+", "+city+" "+pin+", "+state;}
}

abstract class Member {
    private String name;
    String getName() {return name;}
    private Address address;
    Address getAddress() {return address;}
    private String phone; //phone number
    String getPhoneNumber() {return phone;}
    private String email; 
    String getEmail() {return email;}

    Member() {
        System.out.print("Enter name: "); P6.in.skip(P6.ws); name = P6.in.nextLine();
        System.out.println("For address:"); address = new Address();
        System.out.print("Enter phone number: "); phone = P6.in.next();
        System.out.print("Enter e-mail address: "); email = P6.in.next();
    }
    void update() {
        System.out.print("Name: "+name+"\nDo you want to change this value? [Y/N] ");
        if(P6.in.next().toLowerCase().charAt(0) == 'y') {System.out.print("Enter name: "); P6.in.skip(P6.ws); name = P6.in.nextLine();}
        System.out.print("Address: "+address+"\nDo you want to change this value? [Y/N] ");
        if(P6.in.next().toLowerCase().charAt(0) == 'y') address.update();
        System.out.print("\nPhone Number: "+phone+"\nDo you want to change this value? [Y/N] ");
        if(P6.in.next().toLowerCase().charAt(0) == 'y') {System.out.print("Enter phone number: "); phone = P6.in.next();}
        System.out.print("E-mail address: "+email+"\nDo you want to change this value? [Y/N] ");
        if(P6.in.next().toLowerCase().charAt(0) == 'y') {System.out.print("Enter e-mail address: "); email = P6.in.next();}
    }
    @Override public String toString() {
	StringBuilder s = new StringBuilder();
        s.append("Name: "+name);
        s.append("\nAddress: "+address);
        s.append("\nPhone number: "+phone);
        s.append("\nE-mail address: "+email);
	return s.toString();
    }
}

class Student extends Member {
    private final String roll; //roll number
    String getRoll() {return roll;}
    private String course; //course of study
    String getCourse() {return course;}

    Student(String roll) throws Exception {
        roll = roll.trim(); if(roll.length() == 0) throw new IllegalArgumentException(); this.roll = roll;
        System.out.print("Enter course of study: "); P6.in.skip(P6.ws); course = P6.in.nextLine();
    }
    @Override void update() {
        System.out.println("For student roll number "+roll);
        super.update();
        System.out.print("Course of study: "+course+"\nDo you want to change this value? [Y/N] ");
        if(P6.in.next().toLowerCase().charAt(0) == 'y') {System.out.print("Enter course of study: "); P6.in.skip(P6.ws); course = P6.in.nextLine();}
    }
    @Override public String toString() {
	StringBuilder s = new StringBuilder();
        s.append("Student roll number: "+roll+"\n");
        s.append(super.toString());
        s.append("\nCourse of study: "+course);
	return s.toString();
    }
}

class Faculty extends Member {
    private final String id; //employee ID
    String getEmployeeID() {return id;}
    private String dept; //department
    String getDepartment() {return dept;}
    private String special; //specialization
    String getSpecialization() {return special;}

    Faculty(String id) throws Exception {
        id = id.trim(); if(id.length() == 0) throw new IllegalArgumentException(); this.id = id;
        System.out.print("Enter department: "); P6.in.skip(P6.ws); dept = P6.in.nextLine();
        System.out.print("Enter specialization: "); P6.in.skip(P6.ws); special = P6.in.nextLine();
    }
    @Override void update() {
        System.out.println("For faculty employee ID: "+id);
        super.update();
        System.out.print("Department: "+dept+"\nDo you want to change this value? [Y/N] ");
        if(P6.in.next().toLowerCase().charAt(0) == 'y') {System.out.print("Enter department: "); P6.in.skip(P6.ws); dept = P6.in.nextLine();}
        System.out.print("Specialization: "+special+"\nDo you want to change this value? [Y/N] ");
        if(P6.in.next().toLowerCase().charAt(0) == 'y') {System.out.print("Enter specialization: "); P6.in.skip(P6.ws); special = P6.in.nextLine();}
    }
    @Override public String toString() {
	StringBuilder s = new StringBuilder();
        s.append("Faculty employee ID: "+id+"\n");
        s.append(super.toString());
        s.append("\nDepartment: "+dept);
        s.append("\nSpecialization: "+special);
	return s.toString();
    }
}

class P6 {
    static final Scanner in = new Scanner(System.in);
    static final Pattern ws = Pattern.compile("\\s*");
    static final HashMap<String, Student> students = new HashMap<String, Student>();
    static final HashMap<String, Faculty> employees = new HashMap<String, Faculty>();
    static void students() throws Exception {
        System.out.println("Student List Menu:");
        System.out.println("1. Add a student");
        System.out.println("2. Show details of a student");
        System.out.println("3. Update details of a student");
        System.out.println("0. Exit to main menu");
        int choice; Student student; String temp;
        do {
            System.out.print("\nEnter choice: ");
            switch(choice = in.nextInt()) {
            case 1:
                System.out.print("Enter new student roll number: "); temp = in.next();
                if(students.containsKey(temp)) {System.err.println("Student already exists: "+students.get(temp)); break;}
                student = new Student(temp); students.put(student.getRoll(), student); break;
            case 2:
                System.out.print("Enter student roll number: "); temp = in.next();
                if(!students.containsKey(temp)) {System.err.println("Student does not exist!"); break;}
                System.out.println(students.get(temp)); break;
            case 3:
                System.out.print("Enter student roll number: "); temp = in.next();
                if(!students.containsKey(temp)) {System.err.println("Student does not exist!"); break;}
                student = students.get(temp); student.update(); students.put(student.getRoll(), student); break;
            case 0: return;
            default: System.err.println("Invalid Option!");
            }
        } while (choice != 0);
        System.out.println();
    }
    static void employees() throws Exception {
        System.out.println("Faculty Employees List Menu");
        System.out.println("1. Add a faculty member");
        System.out.println("2. Show details of a faculty member");
        System.out.println("3. Update details of a faculty member");
        System.out.println("0. Exit to main menu");
        int choice; Faculty emp; String temp;
        do {
            System.out.print("\nEnter choice: ");
            switch(choice = in.nextInt()) {
            case 1:
                System.out.print("Enter new faculty employee ID: "); temp = in.next();
                if(employees.containsKey(temp)) {System.err.println("Faculty member already exists: "+employees.get(temp)); break;}
                emp = new Faculty(temp); employees.put(emp.getEmployeeID(), emp); break;
            case 2:
                System.out.print("Enter faculty employee ID: "); temp = in.next();
                if(!employees.containsKey(temp)) {System.err.println("Faculty member does not exist!"); break;}
                System.out.println(employees.get(temp)); break;
            case 3:
                System.out.print("Enter faculty employee ID: "); temp = in.next();
                if(!employees.containsKey(temp)) {System.err.println("Faculty member does not exist!"); break;}
                emp = employees.get(temp); emp.update(); employees.put(emp.getEmployeeID(), emp); break;
            case 0: return;
            default: System.err.println("Invalid Option!");
            }
        } while (choice != 0);
        System.out.println();
    } 
    public static void main(String args[]) throws Exception {
        char choice;
        do {
            System.out.println("Main Menu:");
            System.out.println("S: Enter Student Menu");
            System.out.println("F: Enter Faculty Menu");
            System.out.println("0: Exit");
            System.out.print("Enter choice: ");
            switch(choice = in.next().charAt(0)) {
            case 's': case 'S': students(); break;
            case 'f': case 'F': employees(); break;
            case '0': return;
            default: System.err.println("Invalid Option!");
            }
        } while (choice != '0');
    }
}
