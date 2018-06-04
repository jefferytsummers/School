
public class Card
{
    //default constructor - required
	public Card()
    {
        cardSuit   = null;
        cardFace   = 0;
        pointValue = 0;
    }

    //constructor that takes a card's face (represented an integer) and suit
	// card face example: Ace=0, 2=1, 3=2, ... Q=11, K=12 or some other ordering
	public Card (int face, String st)
    {
        cardSuit   = st;
        cardFace   = face;
        pointValue = face + 1;
    }

    // compare and return true if *this has a lesser point value than cd, false otherwise
	public boolean lessThan(Card cd)
    {
        return pointValue < cd.pointValue;
    }

    // compare and return true if *this has a larger point value than cd, false otherwise
	public boolean greaterThan(Card cd)
    {
        return pointValue > cd.pointValue;
    }

    // compare and return true if *this has the same point value as cd, false otherwise
	public boolean equals(Card cd)
    {
        return pointValue == cd.pointValue;
    }

    // return the point value of the card: Ace: 15, Faces: 10, Numbers: the number
	public int getPointValue()
    {
        return pointValue;
    }

    public void Print()
    {
        String output = String.format("Suit: %s Face: %d Value: %d", cardSuit, cardFace, pointValue);
        System.out.println(output);
    }

	private String cardSuit;		// card's suit
	private int    cardFace;		// card's face
	private int    pointValue;	// card's point value (derived from face)
}
