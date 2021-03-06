import java.io.*;

public class main
{
    public static void main(String [] args)
    {
        String file   = "point.dat";
        String line   = null;
        Roster roster = new Roster();
        String header = null;

        try
        {
            FileReader     fr   = new FileReader(file);
            BufferedReader br   = new BufferedReader(fr);

            try
            {
                while((line = br.readLine()) != null)
                {
                    if(header != null)
                    {
                        String[] l = line.split("\\s+");
                        roster.Insert(new Student(l[0],
                                      Integer.parseInt(l[1]),
                                      Integer.parseInt(l[2]),
                                      Integer.parseInt(l[3]),
                                      Integer.parseInt(l[4]),
                                      Integer.parseInt(l[5]),
                                      Integer.parseInt(l[6])));
                    }
                    else
                    {
                        header = line;
                    }
                }

                br.close();

                roster.SubmitStudentQuery();
                roster.Print();
            }
            catch(IOException io)
            {
                System.out.println(io);
            }
        }
        catch(FileNotFoundException ex)
        {
            System.out.println(ex);
        }
    }
}
