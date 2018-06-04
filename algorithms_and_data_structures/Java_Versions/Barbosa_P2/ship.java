public class ship
{
    public ship(String name, double fuel)
    {
        this.name = name;
        this.fuel = fuel;
    }

    public void Fuel()
    {
        String output = String.format("%s fuel: %.2f tons", name, fuel);
        System.out.println(output);
    }

    public void sail()
    {
        System.out.println("Ship sailing.");
    }

    public void load(int cargo)
    {}

    protected String name;
    protected double fuel;
}
