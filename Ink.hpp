#ifndef INK_HPP
#define INK_HPP

#include <iostream>

/*
    Class representing ink bottles. There are 4 type of ink (C,M,Y and K).
    Ink type in forms of numbers are allowed for testing purposes.
*/
class Ink
{
    private:
        char ink_type; // type of ink - {'C','M','Y','K'}
    public:
        Ink(char itnk_type); // constructor with given type of ink
        char GetInkType() const {return ink_type;}
        int GetNumbValue() const ; // get type of ink in numerical form - 'C' = 0, ... , 'K' = 3
        friend std::ostream & operator<< (std::ostream &out, const Ink &ink);
        Ink & operator= (char &);
        bool operator== (const char &);
        bool operator== (const Ink &);
        bool operator!= (const Ink &);
        bool operator< (const Ink &); //'C' > 'M' > 'Y' > 'K'
        bool operator> (const Ink &); //'C' > 'M' > 'Y' > 'K'
        bool operator<= (const Ink &); //'C' > 'M' > 'Y' > 'K'
        bool operator>= (const Ink &); //'C' > 'M' > 'Y' > 'K'
};

#endif // INK_H
