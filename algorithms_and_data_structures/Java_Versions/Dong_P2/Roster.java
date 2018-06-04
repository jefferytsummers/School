import java.util.Scanner;

public class Roster extends main
{
    public void Insert(Student stu)
    {
        this.roster[this.numOfStudents++] = stu;
    }

    public void SubmitStudentQuery()
    {
        System.out.print("Please enter a valid c#: ");
        Scanner sc    = new Scanner(System.in);
        String  c_num = sc.next();
        int i = 0;
        for(i = 0; i < this.numOfStudents; ++i)
        {
            if(roster[i].GetId().equals(c_num))
            {
                System.out.print("Here is the information for student with");
                System.out.println(" c-number " + c_num + ":");
                roster[i].Print();
                System.out.println();
                return;
            }
        }
        System.out.println("Student not found\n");

    }

    public void Print()
    {
        System.out.println("Displaying results for all students:");
        for(int i = 0; i < this.numOfStudents; ++i)
            this.roster[i].Print();
    }

    private static final int max           = 50;
    private int              numOfStudents = 0;
    private Student[]        roster        = new Student[this.max];

}
