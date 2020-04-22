#include "Shelf.hpp"

using namespace std;

Shelf::Shelf(int inksNumb)
{
    BuildShelf(inksNumb);
}

Shelf::Shelf(string newShelf)
{
    BuildShelf(newShelf);
}

void Shelf::AddInk(char newInkType)
{
    Ink ink(newInkType);
    inks.push_back(ink);
}

void Shelf::BuildShelf(int inksNumb)
{
    clear(); // clear the shelf from the ink bottles

    srand(time(NULL));

    int randInkTypeInt; // random type of new ink bottle in numerical form
    char randInkType; // random type of new ink bottle

    for(int i = 0; i < inksNumb; i++) // generating given number of ink bottles
    {
        randInkTypeInt = rand()%4; // generate random numerical value of type of the new ink
        switch(randInkTypeInt)
        {
            case 0:
                randInkType = 'C';
                break;
            case 1:
                randInkType = 'M';
                break;
            case 2:
                randInkType = 'Y';
                break;
            case 3:
                randInkType = 'K';
                break;
        }
        AddInk(randInkType); // add generated ink to the shelf
    }
}

void Shelf::BuildShelf(string newShelf)
{
    clear();
    for(int i = 0; i < newShelf.size(); i++)
        AddInk(newShelf[i]);
}

bool Shelf::Check()
{
    if(inks.size() <= 1)
        return true;

    list<Ink>::iterator scd = begin(); // iterator for next ink bottle on the shelf behind the currently checked bottle
    scd++; // set iterator j on second Ink on the shelf

    for(list<Ink>::iterator fst = begin(); scd != end(); fst++) //checking each pair of bottles lying next to each other on the shelf
    {
        if((*fst) < (*scd)) // if second bottle has "bigger" ink type then first bottle
            return false;
        scd++;
    }
    return true;
}

bool Shelf::IsMoveable(int first)
{
    return !(first >= inks.size()-4); // if first given bottle is one of the last four bottles on the shelf
}

bool Shelf::Move4InksBottles(int first)
{
    if(first >= inks.size()-4) // if first given bottle is one of the last four bottles on the shelf
        return false;
    int inkNumb = 0;
    list<Ink>::iterator inkIterator = begin(); // iterator for bottle with given first number
    while(inkNumb<first && inkIterator != end()) // while inkIterator does not point to given first ink bottle
    {
        inkNumb++;
        inkIterator++;
    }

    list<Ink>::iterator behind = inkIterator; // iterator for first bottle behind bottle to be moved
    for(inkNumb = 0; inkNumb < 4; inkNumb++)
        behind++;

    inks.splice(end(),inks,inkIterator,behind); // move bottles
    return true;
}

int Shelf::length()
{
    if(inks.empty() == true)
        return 0;
    return inks.size();
}

void Shelf::Print()
{
    for(list<Ink>::iterator i = inks.begin(); i != inks.end(); i++)
        cout << (*i);
    cout << endl;
}

string Shelf::Sort()
{
    /* Bubble Sort */

    char tmp;
    string s = ToString();
    int s1, s2;
    for(int i = s.length() - 1; i >= 0; i--)
    {
        for(int j = 0; j < i; j++)
        {
            switch(s[j])
            {
                case 'C':
                    s1 = 0;
                    break;
                case 'M':
                    s1 = 1;
                    break;
                case 'Y':
                    s1 = 2;
                    break;
                case 'K':
                    s1 = 3;
                    break;
                default:
                    s1 = -1;
            }
            switch(s[j+1])
            {
                case 'C':
                    s2 = 0;
                    break;
                case 'M':
                    s2 = 1;
                    break;
                case 'Y':
                    s2 = 2;
                    break;
                case 'K':
                    s2 = 3;
                    break;
                default:
                    s2 = -1;
            }
            if(s1 > s2)
            {
                tmp = s[j];
                s[j] = s[j+1];
                s[j+1] = tmp;
            }
        }
    }
    return s;
}

string Shelf::ToString()
{
    string s = "";
    for(list<Ink>::iterator i = inks.begin(); i != inks.end(); i++)
        s += (*i).GetInkType();
    return s;
}

Shelf & Shelf::operator= (string s)
{
    inks.clear();
    for(int j = 0; j < s.size(); j++)
        AddInk(s[j]);
    return (*this);
}

bool Shelf::operator== (string s)
{
    if(length() != s.size())
        return false;

    int i = 0;

    for(list<Ink>::iterator j = begin(); j != end(); j++)
    {
        if(s[i] != '#' && (*j) != s[i])
            return false;
        i++;
    }
    return true;
}


bool Shelf::operator== (Shelf & s)
{
    if(length() != s.length())
        return false;

    list<Ink>::iterator i = s.begin();

    for(list<Ink>::iterator j = begin(); j != end(); j++)
    {
        if((*i) != (*j))
            return false;
        i++;
    }
    return true;
}

bool Shelf::operator> (Shelf &s)
{
    list<Ink>::iterator j = s.begin();
    for(list<Ink>::iterator i = begin(); i != inks.end(); i++)
    {
        if((*i) > (*j))
            return true;
        else if((*i) < (*j))
            return false;
        j++;
    }

    return false;
}

bool Shelf::operator< (Shelf &s)
{
    list<Ink>::iterator j = s.begin();
    for(list<Ink>::iterator i = begin(); i != inks.end(); i++)
    {
        if((*i) < (*j))
            return true;
        else if((*i) > (*j))
            return false;
        j++;
    }
    return false;
}

bool Shelf::operator>= (Shelf &s)
{
    list<Ink>::iterator j = s.begin();
    for(list<Ink>::iterator i = begin(); i != inks.end(); i++)
    {
        if((*i) > (*j))
            return true;
        else if((*i) < (*j))
            return false;
        j++;
    }
    return true;
}

bool Shelf::operator<= (Shelf &s)
{
    list<Ink>::iterator j = s.begin();
    for(list<Ink>::iterator i = begin(); i != inks.end(); i++)
    {
        if((*i) < (*j))
            return true;
        else if((*i) > (*j))
            return false;
        j++;
    }
    return true;
}

ostream & operator<< ( ostream &out, Shelf &shelf)
{
    if(!shelf.empty())
    {
        for(list<Ink>::iterator i = shelf.begin(); i != shelf.end(); i++)
            out << (*i);
        out << endl;
    }
    return out;
}


