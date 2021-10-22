// Online Java Compiler
// Use this editor to write, compile and run your Java code online
import java.io.*;
import java.util.*;
import java.math.*;
import java.text.*;
import java.util.regex.*;

abstract class Employee
{
    public abstract void setSalary(int salary);
    public abstract int getSalary();
    public abstract void setGrade(String grade);
    public abstract String getGrade();
    public void label()
    {
        System.out.println("Employee's Data: \n");
    }
}

class HelloWorld {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String sub = sc.nextLine();
        int n = Integer.parseInt(sub);
        for(int i=0; i<n; i++)
        {
            String[] input = sc.nextLine().split(" ");
            if(input[0].equals("ENGINEER"))
            {
                Engineer e = new Engineer();
                e.setSalary(Integer.parseInt(input[2]));
                e.setGrade(input[1]);
                e.label();
                System.out.println("GRADE : "+ e.getGrade());
                System.out.println("SALARY : " + e.getSalary());
            }
        }
    }
}


class Engineer extends Employee
{
    private int salary;
    private String grade;
    
    public int getSalary()
    {
        return this.salary;
    }
    public void setSalary(int salary)
    {
        salary = this.salary;
    }
    public void setGrade(String grade)
    {
        this.grade = grade;
    }
    public String getGrade(String grade)
    {
        return this.grade;
    }
    
    
}


class Manager extends Employee
{
    private int salary;
    private String grade;
    
    public int getSalary()
    {
        return this.salary;
    }
    public void setSalary(int salary)
    {
        salary = this.salary;
    }
    public void setGrade(String grade)
    {
        this.grade = grade;
    }
    public String getGrade(String grade)
    {
        return this.grade;
    }
    
}

