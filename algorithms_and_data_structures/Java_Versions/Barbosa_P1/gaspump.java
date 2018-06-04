
public class gaspump extends main
{
    //Public methods.
    public gaspump(String gas_type, double capacity, double price)
    {
        this.gas_type        = gas_type;
        this.capacity        = capacity;
        this.price           = price;
        this.amount          = capacity;
        this.revenue         = 0.0;
        this.total_dispensed = 0.0;
        this.turn_em_away    = false;
    }

    public String Fuel_Type()
    {
        return gas_type;
    }

    public double Fuel_Dispensed()
    {
        return total_dispensed;
    }

    public double Revenue()
    {
        return revenue;
    }

    public void dispenseFuel(double gals)
    {
        if(!turn_em_away)
        {
            String output = null;
            if(gals < amount)
            {
                amount          -= gals;
                amount_dispensed = gals;
            }
            else
            {
                amount_dispensed = gals - amount;
                amount           = 0;
                turn_em_away     = true;
            }

            output           = String.format("Amount of fuel requested: %.2f\nAmount of fuel dispensed: %.2f\nTotal price: $%.2f",
                               gals, amount_dispensed, amount_dispensed*price);
            revenue         += amount_dispensed*price;
            total_dispensed += amount_dispensed;
            System.out.println(output);
        }
        else
        {
            System.out.println("No more fuel. Go away.");
            Replenish();
        }
    }

    //Private methods.
    private void Replenish()
    {
        amount = capacity;
        System.out.println("Fuel pump replensished.");
        turn_em_away = false;
    }

    //Member data.
    private String  gas_type;
    private double  amount;
    private double  capacity;
    private double  price;
    private double  amount_dispensed;
    private double  total_dispensed;
    private double  revenue;
    private boolean turn_em_away;
}
