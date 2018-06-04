import java.io.*;

public class Student extends Roster
{
    public Student(String i, int c, int o, int q, int h, int e, int b)
    {
        id       = i;
        cla      = c;
        ola      = o;
        quiz     = q;
        homework = h;
        exam     = e;
        bonus    = b;

        total    = c + o + q + h + e + b;

        if(total < 60)
            grade = 'F';
        else if(total < 70)
            grade = 'D';
        else if(total < 80)
            grade = 'C';
        else if(total < 90)
            grade = 'B';
        else
            grade = 'A';
    }

    public String GetId()
    {
        return id;
    }

    public void Print()
    {
        System.out.println(id + " " + String.valueOf(cla) + " " +
                           String.valueOf(ola) + " " + String.valueOf(quiz) +
                           " " + String.valueOf(homework) + " " +
                           String.valueOf(exam) + " " + String.valueOf(bonus)
                           + " " + String.valueOf(total) + " " + grade);
    }

    private String id;
    private int    cla;
    private int    ola;
    private int    quiz;
    private int    homework;
    private int    exam;
    private int    bonus;
    private int    total;
    private char   grade;
}

