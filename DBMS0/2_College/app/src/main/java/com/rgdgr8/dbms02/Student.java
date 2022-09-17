package com.rgdgr8.dbms02;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Student {
    public static List<Student> students = new ArrayList<>();
    private final int scode;
    private int dcode;
    private String name;
    private String address;
    private String phone;

    public Student(int scode, int dcode, String name, String address, String phone) {
        this.scode = scode;
        this.dcode = dcode;
        this.name = name;
        this.address = address;
        this.phone = phone;
    }

    public int getScode() {
        return scode;
    }

    public int getDcode() {
        return dcode;
    }

    public String getName() {
        return name;
    }

    public String getAddress() {
        return address;
    }

    public String getPhone() {
        return phone;
    }

    public void setDcode(int dcode) {
        this.dcode = dcode;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Student)) return false;
        Student student = (Student) o;
        return scode == student.scode;
    }

    @Override
    public int hashCode() {
        return Objects.hash(scode);
    }

    @Override
    public String toString() {
        return ("Student Code: " + scode + "\n" +
                "Department: " + Department.department[dcode - 1] + "\n" +
                "Name: " + name + "\n" +
                "Address: " + address + "\n" +
                "Phone: " + phone);
    }
}
