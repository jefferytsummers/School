#ifndef dateClass_H
#define dateClass_H

class dateClass
{
    public:

        //Constructors.
        dateClass(); //default constructor
        dateClass(int m, int d, int y); //value constructor

        //set date to month(m), day(d), year(y).
        void SetDate(int m, int d, int y);

        //Set month(m).
        void SetMonth(int m);

        //Set day(d).
        void SetDay(int d);

        //Set year(y).
        void SetYear(int y);

        //Get month value.
        int  GetMonth();

        //Get day value.
        int  GetDay();

        //Get year value.
        int  GetYear();

        //Display object data.
        void Display() const;

    private:
        //Declare private variables.
        int month,
            day,
            year;














};

#endif
