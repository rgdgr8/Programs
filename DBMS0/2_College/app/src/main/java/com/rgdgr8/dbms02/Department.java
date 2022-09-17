package com.rgdgr8.dbms02;

public class Department {
    public static final Department[] department = {new Department(1, "CSE"), new Department(2, "IT")};
    //if you change dcode for any department, also change the toString method of Student

    private final int dcode;
    private final String name;

    public Department(int dcode, String name) {
        this.dcode = dcode;
        this.name = name;
    }

    public int getDcode() {
        return dcode;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return name + "(" + dcode + ")";
    }
}
