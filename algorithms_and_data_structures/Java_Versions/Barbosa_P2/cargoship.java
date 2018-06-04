public class cargoship extends ship
{
    public cargoship(String name, double fuel, int capacity)
    {
        super(name, fuel);
        this.capacity      = capacity;
        this.aft_cargo     = 0;
        this.forward_cargo = 0;
    }

    public void Fuel(int flashpoint)
    {
        super.Fuel();
        System.out.println(name + " verified fuel flashpoint > " + String.valueOf(flashpoint)
                            + " degrees");
    }

    public void load(int cargo)
    {
        forward_cargo = (int)(0.47*cargo);
        aft_cargo     = cargo - forward_cargo;
        String output = String.format("%s Loading...Ajusting CG...%.1f tons in FWD Bay %.1f tons in AFT Bay", name, forward_cargo, aft_cargo);
        System.out.println(output);
    }

    private double forward_cargo;
    private double aft_cargo;
    private int    capacity;
}
