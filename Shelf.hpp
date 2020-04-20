#ifndef SHELF_HPP
#define SHELF_HPP

#include <list>
#include "ink.hpp"
#include <cstdlib>
#include <ctime>

/*
    Class representing ink shelf with ink bottles.
    Ink bottles are stored in the list. The length of the list is unlimited.
*/
class Shelf
{
    private:
        std::list<Ink> inks; //list of Ink objects representing bottles of ink on the shelf
    public:
        Shelf(){} // construct empty shelf
        Shelf(int inksNumb); // constructor with given number of bottles with random inks on the shelf
        Shelf(std::string newShelf); // constructor with bottles on the shelf like in given string (for ex. "CCMYKCM" is shelf with 7 inks - fist ink type C, second ink type C, ... and last ink type M)
        void AddInk(char new_inkType); // add new ink with given type at the end of the shelf
        void BuildShelf(int inksNumb); // add given number of bottles with random inks on the shelf
        void BuildShelf(std::string new_shelf); // add bottles on the shelf like in given string (for ex. "CCMYKCM" is shelf with 7 inks - fist ink type C, second ink type C, ... and last ink type M)
        bool Check(); // check if the bottles on the shelf meet the task requirements
        void clear(){inks.clear();} // clear the shelf from the bottles
        bool empty(){return inks.empty();} // check is shelf is empty
        bool IsMoveable(int first); // check if given ink bottles can by transfered
        bool Move4InksBottles(int first); // take 4 ink bottles in the row (starting with first given from the left, counting from the left side of the shelf from zero) and put it on the right side of the dhelf
        int length(); // return length of the shelf
        void Print(); // print the shelf
        std::string Sort(); // return state of the shelf with bottles sorted in accordance with the requirements of the tasks
        std::string ToString(); // return string representing ink bottles setting on the shelf
        std::list<Ink>::iterator begin(){return inks.begin();} // return begin of the list of inks
        std::list<Ink>::iterator end(){return inks.end();} // return end of the list of inks
        Shelf & operator =( std::string s);
        bool operator== (std::string);
        bool operator== (Shelf &); // check if the shelfs are the same
        bool operator> (Shelf &); // compare which shelf is more ordered from the left
        bool operator< (Shelf &); // compare which shelf is more ordered from the left
        bool operator>= (Shelf &); // compare which shelf is more ordered from the left
        bool operator<= (Shelf &); // compare which shelf is more ordered from the left
        friend std::ostream & operator<< (std::ostream &out, Shelf &shelf);
        friend std::istream & operator>> (std::istream &in, Shelf &shelf);

    protected:

};

#endif // SHELF_HPP
