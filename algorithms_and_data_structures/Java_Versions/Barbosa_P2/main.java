public class main
{
    public static void main(String[] args)
    {
        cruiseship cs = new cruiseship("Carnival", 400, 0.1, 0.2, 0.7);
        cs.Fuel();
        cs.load(5000);
        cs.sail();

        cargoship Cs = new cargoship("Iron Maiden", 750, 300);
        Cs.Fuel(55);
        Cs.load(800);
        Cs.sail();
    }
}
