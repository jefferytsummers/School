import java.util.Random;

public class main
{
    public static void main(String[] args)
    {
        Random  num    = new Random();
        gaspump pump1  = new gaspump("Unleaded", 200, 2.59);
        gaspump pump2  = new gaspump("Midgrade", 125, 2.87);
        gaspump pump3  = new gaspump("Premium+", 100, 3.13);
        String  output = null;
        double  gals   = 0.0;
        for(int i = 1; i < 201; ++i)
        {
            int fuel = num.nextInt(100)%7;
            gals     = 3.0 + 22*(double)fuel/7;
            switch(fuel)
            {
                case 0: case 1: case 2: case 3:
                    output = String.format("Vechicle %d %s", i, pump1.Fuel_Type());
                    System.out.println(output);
                    pump1.dispenseFuel(gals);
                    break;
                case 4: case 5:
                    output = String.format("Vechicle %d %s", i, pump2.Fuel_Type());
                    System.out.println(output);
                    pump2.dispenseFuel(gals);
                    break;
                case 6:
                    output = String.format("Vechicle %d %s", i, pump3.Fuel_Type());
                    System.out.println(output);
                    pump3.dispenseFuel(gals);
                    break;
            }
            System.out.println("*******************************");
        }

        output = String.format("Pump Unleaded dispensed %.2f gallons and collected $%.2f", pump1.Fuel_Dispensed(), pump1.Revenue());
        System.out.println(output);
        output = String.format("Pump Midgrade dispensed %.2f gallons and collected $%.2f", pump2.Fuel_Dispensed(), pump2.Revenue());
        System.out.println(output);
        output = String.format("Pump Premium+ dispensed %.2f gallons and collected $%.2f", pump3.Fuel_Dispensed(), pump3.Revenue());
        System.out.println(output);
    }
}
