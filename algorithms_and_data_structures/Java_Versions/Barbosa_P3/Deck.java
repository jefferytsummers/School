import java.util.*;
import java.util.concurrent.ThreadLocalRandom;

public class Deck
{
    // default constructor
	public Deck()
    {
        numCards = 52;
        theDeck  = new Card[numCards];
        for(int i = 0; i < 13; ++i)
            theDeck[i] = new Card((i + 1)%13, "clubs");
        for(int i = 13; i < 26; ++i)
            theDeck[i] = new Card((i + 1)%13, "spades");
        for(int i = 26; i < 39; ++i)
            theDeck[i] = new Card((i + 1)%13, "hearts");
        for(int i = 39; i < numCards; ++i)
            theDeck[i] = new Card((i + 1)%13, "diamonds");
        topCard  = 52;
    }

    // Remove the top card from the deck and return it.
	public Card dealCard()
    {
        return theDeck[topCard--];
    }

    // Shuffle the cards in the deck
	public void Shuffle()
    {
        Random rnd = ThreadLocalRandom.current();
        for(int i = numCards - 1; i > 0; --i)
        {
            int index      = rnd.nextInt(i + 1);
            Card c         = theDeck[index];
            theDeck[index] = theDeck[i];
            theDeck[i]     = c;

        }
    }

    // return true if there are no more cards in the deck, false otherwise
	public boolean isEmpty()
    {
        return topCard < 0;
    }

    //overload << operator to display the deck
    public void Print()
    {
        for(Card c : theDeck)
            c.Print();
    }

    public static void main(String[] args)
    {
        Deck d = new Deck();
        d.Print();
        d.Shuffle();
        d.Print();
    }

    private int    numCards;
	private Card[] theDeck;
	private int    topCard;					// the index of the deck's top card
};
