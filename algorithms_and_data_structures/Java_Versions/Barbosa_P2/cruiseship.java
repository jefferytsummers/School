public class cruiseship extends ship
{
    public cruiseship(String name, double fuel, double luxury_p,
                      double upper_deck_p, double lower_deck_p)
    {
        super(name, fuel);
        this.luxury_p     = luxury_p;
        this.upper_deck_p = upper_deck_p;
        this.lower_deck_p = lower_deck_p;
    }

    public void sail()
    {
        String output = String.format("%s sailing: %d in Luxury %d in Upper-deck %d in Lower-deck", name, luxury, upper_deck, lower_deck);
        System.out.println(output);
    }

    public void load(int passengers)
    {
        luxury     = (int)(passengers*luxury_p);
        upper_deck = (int)(passengers*upper_deck_p);
        lower_deck = (int)(passengers*lower_deck_p);
    }

    private double luxury_p;
    private double upper_deck_p;
    private double lower_deck_p;
    private int    luxury;
    private int    upper_deck;
    private int    lower_deck;
}
