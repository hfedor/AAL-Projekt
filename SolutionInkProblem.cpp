#include "SolutionInkProblem.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>

#ifdef __WIN32__

#include <windows.h>
#include <conio.h>

#else

#include <curses.h>
#include <unistd.h>

#endif

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

void SolutionInkProblem::ClearTerminal()
{
#ifdef __WIN32__
    system("cls");
#else
    system("clear");
#endif
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
    for(int i = length(); i > actPos; i--)
    	if(s[i] == toFind)
      	     return i;

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
    string moves = "";
    string situation = "";

    file.open( fileName, std::ios::in);

    if(!file)
    {
	cout << "there is no file!" << endl;
	return "";
    }

    if(!file.good())
    {
	cout << "there is not good!" << endl;
	return "";
    }

    if(!file.is_open())
    {
	cout << "there is not open!" << endl;
	return "";
    }

    char c;
    bool m = false;
    while(file.get(c))
    {
	if(!m)
	{
	    if(c == '\n')
	    {
		m = true;
		moves = "";
		continue;
	    }
	    situation += c;
	}
	else if(m)
	{
	    if(c == '\n')
	    {
		m = false;
   		if(situation == sShelf)
     		{
		    file.close();
            	    return moves;
		}
	    	situation = "";
		continue;
	    }
	    moves += c;
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
        string shelf = ToString() + "    ";
        int armFirst = pointer;
        int newDistance = 0;

            while(armFirst != newPosition)
        {
            ClearTerminal();
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
            SleepASecond(1);

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
        else
        {
            int nextPos;
            for(int i = length() - 4; i < length(); i++)
                if(((i - actPos)%4) == 0)
                    nextPos = i;

            int disNextToStart;

            while(distance%4 != 0)
            {
                if(bottleToBeMoved >= length() - 4 && nextPos <  bottleToBeMoved)
                {
                    Move4InksBottles(bottleToBeMoved - 4, animated);
                    bottleToBeMoved -= 4;
                    continue;
                }

                disNextToStart = length() - 1 - nextPos + bottleToBeMoved - 3;
                for(int i = 0; i < 4; i++)
                    if(disNextToStart + i >= actPos && disNextToStart + i < length())
                    {
                        if(i != 4)
                        {
                            Move4InksBottles(disNextToStart + i, animated);
                            bottleToBeMoved = nextPos - i;
                            break;
                        }
                        else
                        {

                        }
                    }
                distance = bottleToBeMoved - actPos;
            }
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
    
    return '0';
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
    cout << "transfers:\n";
    for(list<int>::iterator i = transfers.begin(); i != transfers.end(); i++)
        cout << length() - (*i) << " ";
    cout << endl;
}

void SolutionInkProblem::PrintForAnimation(int step)
{
    string shelf = ToString() + "    ";
    int newDistance = 0;

    if(step <= 0)
    {
        ClearTerminal();
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
        SleepASecond(3);
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
            ClearTerminal();
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
            SleepASecond(1);

            armFirst++;
            if(armFirst <= shelf.length() - 4)
                newDistance++;
        }

        for(int i = 0; i < 4; i++)
            shelf[shelf.length() - 4 + i] = inArm[i];

        ClearTerminal();
        cout << "\n";
        for(int i = 0; i < shelf.length() - 4; i++)
            cout << " ";
        cout << "____\n" << shelf << "\n";
        cout << "\ndistance:\t" << distance  + newDistance << "\n";
        cout << "transfers:\t" << numberOfShifts << endl;;
        SleepASecond(3);

        while(armFirst > start + 1)
        {
            newDistance++;
            newShelf = "";

            ClearTerminal();

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
            SleepASecond(1);

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

void SolutionInkProblem::SleepASecond(int t)
{
#ifdef __WIN32__
    Sleep(t*100);
#else
    std::this_thread::sleep_for(std::chrono::nanoseconds(t*100000000));
#endif
}

bool SolutionInkProblem::Solve(bool animated)
{
    char notSorted = 'C';
    int j = 0;
    int finded;
    list<Ink>::iterator i = shelf.begin();
    char actualInkType;

    if(length() < 6)
    {
        cout << "Shelf with less then 6 ink bottles can not by sorted!" << endl;
        return false;
    }

    while(i != shelf.end())
    {
        i = shelf.begin();
        for(int k = 0; k < j; k++)
            i++;
        actualInkType = (*i).GetInkType();

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
#ifdef __WIN32__
                    string newTransfersString = LoadMovesFromFile("6resultWin.txt",ShelfEnding);
#else
                    string newTransfersString = LoadMovesFromFile("6resultLin.txt",ShelfEnding);
#endif
                    list<int> newTransfers;


                    if(newTransfersString != "")
                    {
                        newTransfers = ScaleTransfersFrom6(newTransfersString);
                        Move(newTransfers, animated);
                    }
		    else
			return false;
                }

                break;
            }
            else
                MoveBottleToPos(j, finded, animated);
        }

        j++;
    }

    return true;
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
        out << isg.length() - (*i) << " ";
    out << "\n";
    return out;
}

