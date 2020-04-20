#include "Ink.hpp"

using namespace std;

Ink::Ink(char newType)
{
    if(newType == 'C' || newType == 'M' || newType == 'Y' || newType == 'K')
        ink_type = newType;
    else if(newType >= '0' && newType <= '9') // for testing
        ink_type = newType;
    else
        ink_type = 'C';
}

int Ink::GetNumbValue() const
{
    switch (ink_type)
    {
        case 'C':
            return 0;
            break;
        case 'M':
            return 1;
            break;
        case 'Y':
            return 2;
            break;
        case 'K':
            return 3;
            break;
        default:
            return ink_type; // for testing
            break;
    }
}

Ink & Ink::operator= (char & c)
{
    ink_type = c;
    return (*this);
}

ostream & operator<< (ostream &out, const Ink &ink)
{
    return out << ink.ink_type;
}

bool Ink::operator== (const char & c)
{
    return (ink_type == c);
}

bool Ink::operator== (const Ink & i)
{
    return (ink_type == i.ink_type);
}

bool Ink::operator!= (const Ink & i)
{
    return (ink_type != i.ink_type);
}

bool Ink::operator< (const Ink &i)
{
    int ink_type1, ink_type2;
    ink_type1 = GetNumbValue();
    ink_type2 = i.GetNumbValue();

    if(ink_type1 > ink_type2)
        return true;
    else
        return false;
}

bool Ink::operator> ( Ink const &i)
{
    int ink_type1, ink_type2;
    ink_type1 = GetNumbValue();
    ink_type2 = i.GetNumbValue();

    if(ink_type1 < ink_type2)
        return true;
    else
        return false;
}

bool Ink::operator<= (const Ink & i)
{
    int ink_type1, ink_type2;
    ink_type1 = GetNumbValue();
    ink_type2 = i.GetNumbValue();

    if(ink_type1 >= ink_type2)
        return true;
    else
        return false;
}

bool Ink::operator>= (const Ink & i)
{
    int ink_type1, ink_type2;
    ink_type1 = GetNumbValue();
    ink_type2 = i.GetNumbValue();

    if(ink_type1 <= ink_type2)
        return true;
    else
        return false;
}
