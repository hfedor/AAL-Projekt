#include "SolutionInkProblem.hpp"

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <windows.h>

using namespace std;

const int UP=72, DOWN=80, LEFT=75, RIGHT=77, ENTER=13;

SolutionInkProblem::SolutionInkProblem(int inks_numb)
{
    shelf = Shelf(inks_numb);
    distance = 0;
    numberOfShifts = 0;
    start = shelf.length() - 4; // the arm of the machine start above last four bottles from the left
    pointer = start; // pointer starts on the forth on the end of the shelf from the left
}

SolutionInkProblem::SolutionInkProblem(string new_shelf)
{
    shelf = Shelf(new_shelf);
    distance = 0;
    numberOfShifts = 0;
    start = shelf.length() - 4; // the arm of the machine start above last four bottles from the left
    pointer = start; // pointer starts on the forth on the end of the shelf from the left
}

bool SolutionInkProblem::Check()
{
    return shelf.Check();
}

list<Ink>::iterator SolutionInkProblem::FindByNumber(int numb)
{
    list<Ink>::iterator i = shelf.begin();

    for(int j = 0; j < numb; j++)
        i++;

    return i;
}

int SolutionInkProblem::FindInkFrom(int actPos, char toFind)
{
    string s = ToString();

    /*
        try to find bottle with given ink type which stands in a position
        distant from the current position with a multiple of 4.
        Bottles in those positions are the easiest to transport to current
        position by the machine.
    */
    for(int i = actPos; i < length(); i += 4)
        if(s[i] == toFind)
            return i;

    /*
        try to find bottle with given ink type which does not stands in a position
        distant from the current position with a multiple of 4.
    */
    for(int i = length(); i > actPos; i -= 4)
        for(int j = 0; j < 3 && i-j >= actPos; j++)
            if(s[i-j] == toFind)
                return i-j;

    return actPos; // if there is no bottle with given ink type return actual position
}

string SolutionInkProblem::GetTransfersByString()
{
    string s;
    for(list<int>::iterator i = transfers.begin(); i != transfers.end(); i++)
    {
        s += to_string(*i);
    }
    return s;
}

string SolutionInkProblem::LoadMovesFromFile(string fileName, string sShelf)
{
    fstream file;
    string moves;
    string situation;

    file.open( fileName, std::ios::in);

    while(getline(file,situation))
    {
        getline(file,moves);

        if(situation == sShelf)
        {
            file.close();
            return moves;
        }
    }

    file.close();
    return "";
}

int SolutionInkProblem::MovePointer(int newPosition, bool animated)
{
    if(newPosition < 0 || newPosition >= shelf.length())
        return -1;

    if(animated)
    {
        string shelf = ToString() + "    ";;
        int armFirst = pointer;
        int newDistance = 0;

            while(armFirst != newPosition)
        {
            system("cls");
            cout << "\n";
            for(int i = 0; i < shelf.length(); i++)
            {
                if(i == armFirst)
                {
                    for(int j = 0; j < 4; j++)
                        cout << "_";
                    i += 4;
                }
                else
                    cout << " ";
            }
            cout << "\n" << shelf << "\n";
            cout << "\ndistance:\t" << distance + newDistance << "\n";
            cout << "transfers:\t" << numberOfShifts << endl;;
            Sleep(300);

            if(armFirst < newPosition)
                armFirst++;
            else
                armFirst--;
            newDistance++;
        }
    }

    distance += (int)abs(pointer - newPosition);

    return pointer = newPosition;
}

void SolutionInkProblem::Move(list<int> transfers, bool animated)
{
    int p;
    for(list<int>::iterator i = transfers.begin(); i != transfers.end(); i++)
    {
        p = (*i);
        Move4InksBottles(p,animated);
    }
}

int SolutionInkProblem::MoveBottleToPos(int actPos, int bottleToBeMoved, bool animated)
{
    int distance;

    if(actPos >= length() - 6 || actPos < 0 || bottleToBeMoved >= length() || bottleToBeMoved < 0)
        return -1;
    if(actPos > bottleToBeMoved)
        return -1;


    while(actPos != bottleToBeMoved)
    {
        distance = bottleToBeMoved - actPos;

        if(distance%4 == 0)
        {
            Move4InksBottles(bottleToBeMoved - 4, animated);
            bottleToBeMoved -= 4;
        }
        else if(bottleToBeMoved >= length() - 4)
        {
            while(distance%4 != 0)
            {
                Move4InksBottles(length() - 5, animated);
                if(bottleToBeMoved < length() - 1)
                    bottleToBeMoved++;
                else
                    bottleToBeMoved = length() - 5;
                distance = bottleToBeMoved - actPos;
            }
        }
        else
        {
            int i;
            for(i = 0; i < 4; i++)
                if((length() - 1 - i - actPos)%4 == 0)
                    break;

            for(int j = 0; j < 3; j++)
                if(bottleToBeMoved - 3 + i < actPos)
                    i++;

            Move4InksBottles(bottleToBeMoved - 3 + i, animated);
            bottleToBeMoved = length() - 1 - i;
        }
    }

    return bottleToBeMoved;
}

bool SolutionInkProblem::Move4InksBottles(int first, bool animated)
{
    if(first > length() - 4)
        return false;
    if(MovePointer(first,animated) == -1)
        return false;
    if(animated)
        PrintForAnimation(0);

    if(shelf.IsMoveable(pointer))
    {
        int pointerOnBegin = pointer;

        if(animated)
            PrintForAnimation(1);
        shelf.Move4InksBottles(pointer);
        MovePointer(start,false);

        distance += 8;
        numberOfShifts++;
        transfers.push_back(first);

        return true;
    }
        return false;
}

char SolutionInkProblem::NextToSort(char &actual)
{
    switch(actual)
    {
        case 'C':
            return actual = 'M';
            break;
        case 'M':
            return actual = 'Y';
            break;
        case 'Y':
            return actual = 'K';
            break;
        case 'K':
            return actual = '0';
            break;
    }
}

void SolutionInkProblem::Play()
{
    char c;

    do
    {
        system("cls");

        PrintForPlay();

        if(Check())
            break;

        c = getch();
        switch (c)
        {
            case LEFT:
            {
                PointerLeft();
                break;
            }
            case RIGHT:
            {
                PointerRight();
                break;
            }
            case ENTER:
            {
                Move4InksBottles(GetPointer(),false);
                break;
            }
        }
    }
    while(c!=27);
}

int SolutionInkProblem::PointerLeft()
{
        pointer--;
        if(pointer < 0)
            pointer = shelf.length() - 4;
        return pointer;
}

int SolutionInkProblem::PointerRight()
{
        pointer++;
        if(pointer > shelf.length() - 4)
            pointer = 0;
        return pointer;
}

void SolutionInkProblem::Print()
{
    cout << shelf;
    cout << "distance: " << distance + (int)abs(start-pointer) << "\nnumberOfShifts: " << numberOfShifts << endl;
    for(list<int>::iterator i = transfers.begin(); i != transfers.end(); i++)
        cout << length() - (*i);
    cout << endl;
}

void SolutionInkProblem::PrintForAnimation(int step)
{
    string shelf = ToString() + "    ";
    int newDistance = 0;

    if(step <= 0)
    {
        system("cls");
        cout << "\n";
        for(int i = 0; i < shelf.length(); i++)
        {
            if(i == pointer)
            {
                for(int j = 0; j < 4; j++)
                    cout << "_";
                i += 4;
            }
            else
                cout << " ";
        }
        cout << "\n" << shelf << "\n";
        cout << "\ndistance:\t" << distance + newDistance << "\n";
        cout << "transfers:\t" << numberOfShifts << endl;;
        Sleep(300);
    }
    else if(step == 1)
    {
        int armFirst = pointer;
        string inArm = "";
        string newShelf = "";

        for(int i = 0; i < shelf.length(); i++)
        {
            if(i == pointer)
            {
                for(int j = i; j < i + 4; j++)
                {
                    inArm += shelf[j];
                    shelf[j] = ' ';
                }
                break;
            }
        }

        while(armFirst <= shelf.length() - 4)
        {
            system("cls");
            for(int i = 0; i < shelf.length(); i++)
            {
                if(i == armFirst)
                {
                    for(int j = 0; j < 4; j++)
                        cout << "_";
                    i += 4;
                }
                else
                    cout << " ";
            }
            cout << "\n";
            for(int i = 0; i < shelf.length(); i++)
            {
                if(i == armFirst)
                {
                    cout << inArm;
                    i += 4;
                }
                else
                    cout << " ";
            }
            cout << "\n" << shelf << "\n";
            cout << "\ndistance:\t" << distance + newDistance << "\n";
            cout << "transfers:\t" << numberOfShifts << endl;;
            Sleep(300);

            armFirst++;
            if(armFirst <= shelf.length() - 4)
                newDistance++;
        }

        for(int i = 0; i < 4; i++)
            shelf[shelf.length() - 4 + i] = inArm[i];

        system("cls");
        cout << "\n";
        for(int i = 0; i < shelf.length() - 4; i++)
            cout << " ";
        cout << "____\n" << shelf << "\n";
        cout << "\ndistance:\t" << distance  + newDistance << "\n";
        cout << "transfers:\t" << numberOfShifts << endl;;
        Sleep(300);

        while(armFirst > start + 1)
        {
            newDistance++;
            newShelf = "";

            system("cls");

            cout << "\n";
            for(int i = 0; i < shelf.length(); i++)
            {
                if(i == armFirst - 2)
                {
                    for(int j = 0; j < 4; j++)
                        cout << "_";
                    i += 4;
                }
                else
                    cout << " ";
            }

            for(int i = 0; i < shelf.length(); i++)
            {
                if(shelf[i] == ' ')
                {
                    for(int j = i + 1; j < shelf.length(); j++)
                        newShelf += shelf[j];
                    newShelf += ' ';
                    break;
                }
                else
                    newShelf += shelf[i];
            }
            shelf = newShelf;
            cout << "\n" << shelf << "\n";
            cout << "\ndistance:\t" << distance  + newDistance << "\n";
            cout << "transfers:\t" << numberOfShifts << endl;;
            Sleep(300);

            if(armFirst > start + 1)
                armFirst--;
        }
    }
}

void SolutionInkProblem::PrintForPlay()
{
    cout << shelf;
    for(int i  = 0; i < shelf.length(); i++)
    {
        if(i >= pointer && i < pointer+4)
            cout << "#";
        else
            cout << " ";
    }
    cout << "\ndistance: " << distance + (int)abs(start-pointer) << "\nnumberOfShifts: " << numberOfShifts << endl;
}

void SolutionInkProblem::Solve(bool animated)
{
    char notSorted = 'C';
    int j = 0;
    int finded;
    list<Ink>::iterator i = shelf.begin();
    char actualInkType;

    while(i != shelf.end())
    {
        i = shelf.begin();
        for(int k = 0; k < j; k++)
            i++;
        actualInkType = (*i).GetInkType();

        pointer = j;

        if(actualInkType != notSorted)
        {
            finded = FindInkFrom(j, notSorted);
            if(finded == j)
            {
                NextToSort(notSorted);
                    if(notSorted == '0')
                        break;
                continue;
            }
            else if(j >= length() - 6)
            {
                if(!Check())
                {
                    string ShelfEnding = "";
                    string sShelf = ToString();
                    for(int i = length() - 6; i < length(); i++)
                        ShelfEnding += sShelf[i];
                    string newTransfersString = LoadMovesFromFile("6result.txt",ShelfEnding);
                    list<int> newTransfers;

                    if(newTransfersString != "")
                    {
                        newTransfers = ScaleTransfersFrom6(newTransfersString);
                        Move(newTransfers, animated);
                    }
                }

                break;
            }
            else
                MoveBottleToPos(j, finded, animated);
        }

        j++;
    }
}

list<int> SolutionInkProblem::ScaleTransfersFrom6(string transfersFor6)
{
    list<int> transfersForLonger;
    int transfer;

    for(int i = 0; i < transfersFor6.length(); i++)
    {
        transfer = (int)transfersFor6[i] - (int)48;
        transfersForLonger.push_back(transfer + length() - 6);
    }

    return transfersForLonger;
}

SolutionInkProblem &SolutionInkProblem::operator= ( SolutionInkProblem & isg)
{
    shelf = isg.shelf;
    pointer = isg.pointer;
    distance = isg.distance;
    numberOfShifts = isg.numberOfShifts;
    start = isg.start;
    transfers = isg.transfers;
    return (*this);
}

bool SolutionInkProblem::operator== ( string & s)
{
    return (shelf == s);
}

bool SolutionInkProblem::operator== ( SolutionInkProblem & isg)
{
    return (shelf == isg.shelf && distance == isg.distance);
}

bool SolutionInkProblem::operator< ( SolutionInkProblem & isg)
{
    return (shelf == isg.shelf && distance < isg.distance);
}

bool SolutionInkProblem::operator> ( SolutionInkProblem & isg)
{
    return (shelf == isg.shelf && distance > isg.distance);
}

bool SolutionInkProblem::operator<= ( SolutionInkProblem & isg)
{
    return (shelf == isg.shelf && distance <= isg.distance);
}

bool SolutionInkProblem::operator>= ( SolutionInkProblem & isg)
{
    return (shelf == isg.shelf && distance >= isg.distance);
}

ostream & operator<< ( ostream &out, SolutionInkProblem &isg)
{
    out << isg.shelf;
    out << isg.distance + (int)abs(isg.start-isg.pointer) << "\n" << isg.numberOfShifts << "\n";
    for(list<int>::iterator i = isg.transfers.begin(); i != isg.transfers.end(); i++)
        out << isg.length() - (*i);
    out << "\n";
    return out;
}

