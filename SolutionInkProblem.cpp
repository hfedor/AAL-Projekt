#include "SolutionInkProblem.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include <chrono>

#ifdef __WIN32__

#include <windows.h>
#include <conio.h>

#else

#include <curses.h>
#include <unistd.h>

#endif

using namespace std;
using namespace std::chrono;

SolutionInkProblem::SolutionInkProblem(int inks_numb)
{
    shelf = Shelf(inks_numb);
    distance = 0;
    numberOfShifts = 0;
    start = shelf.length() - 4; // the arm of the machine start above last four bottles from the left
    pointer = start; // pointer starts on the forth on the end of the shelf from the left
    shelfOnBegining = shelf.ToString();
#ifdef __WIN32__
        ::QueryPerformanceCounter(&nStartTime);
#endif
}

SolutionInkProblem::SolutionInkProblem(string new_shelf)
{
    shelf = Shelf(new_shelf);
    distance = 0;
    numberOfShifts = 0;
    start = shelf.length() - 4; // the arm of the machine start above last four bottles from the left
    pointer = start; // pointer starts on the forth on the end of the shelf from the left
    shelfOnBegining = shelf.ToString();
}

std::list<int> SolutionInkProblem::BrutalPermutation(string sShelf, char notSorted, int deep)
{
	if(too_slow)
		return list<int>{-2};

	if(sShelf.length() <= 6)
		return list<int>{-1};

    list<int> transforamtions;
    if(deep == 0)
    {
        for(int i = 4; i < sShelf.length(); i += 4)
            if(sShelf[i] == notSorted)
            {
                for(int j = i; j >= 4; j -= 4)
                    transforamtions.push_back(j-4);
                return transforamtions;
            }

        transforamtions.push_back(-1);
        return transforamtions;
    }
    else
    {
#ifdef __WIN32__
        LARGE_INTEGER nStopTime;
        LARGE_INTEGER nElapsed;
        LARGE_INTEGER nFrequency;
        ::QueryPerformanceCounter(&nStopTime);
        nElapsed.QuadPart = (nStopTime.QuadPart - nStartTime.QuadPart) * 1000000;
        nElapsed.QuadPart /= nFrequency.QuadPart;

       if((nElapsed).QuadPart > 5000)
		{
			cout << (nElapsed).QuadPart << endl;
			too_slow = true;
			throw to_string((nElapsed).QuadPart);
		}
#else
        steady_clock::time_point t2 = steady_clock::now();
        duration = t2-start_time;
		if((duration).count() > TIME_LIMIT)
		{
			cout << (duration).count() << endl;
			too_slow = true;
			throw to_string((duration).count());
			return list<int>{-2};
		}
#endif

        for(int i = 0; i <  sShelf.length() - 4; i++)
        {
            Shelf permutedSfelf(sShelf);

            permutedSfelf.Move4InksBottles(i);
            transforamtions = BrutalPermutation(permutedSfelf.ToString(),notSorted,deep - 1);
            if(transforamtions.front() != -1)
            {
				if(transforamtions.front() != -2)
					transforamtions.push_front(i);
				else
					too_slow = true;
                return transforamtions;
            }
        }
    }
    return transforamtions;
}

std::list<int> SolutionInkProblem::BrutalPermutationSparing(char biggestInBegin, string sShelf, char notSorted, int deep)
{
	if(too_slow)
		return list<int>{-2};

	if(sShelf.length() <= 6)
		return list<int>{-1};

    list<int> transforamtions;
    Shelf permutationShelf(sShelf);
    if(deep == 0)
    {
        for(int i = 4; i < sShelf.length(); i += 4)
            if(sShelf[i] == notSorted)
            {
                for(int j = i; j >= 4; j -= 4)
                {
                    bool do_last_6 = (biggestInBegin == '0');
                    Ink ink(biggestInBegin);

                    //cout << permutationShelf.ToString() << endl;
                    if(biggestInBegin != 'C')
                        for(int k = 0; k < j; k++)
                            if((*permutationShelf[k]) > ink)
                            {
                                //cout << permutationShelf.GetInk(k).GetInkType() << endl;
                                biggestInBegin = permutationShelf.GetInk(k).GetInkType();
                                ink = biggestInBegin;
                                if(biggestInBegin == 'C')
                                    break;
                            }

                    string sShelf2 = "";
                    for(int k = j+1; k < permutationShelf.length(); k++)
                        sShelf2 += permutationShelf.ToString()[k];
                    //cout << sShelf2 << endl;

					if(sShelf2.length() > 7)
                    if((do_last_6 && sShelf2.length() - j > 5) || j < ((int)sShelf2.length()) - 6)
                    {
                        SolutionInkProblem sip(sShelf2);
                        sip.Solve(biggestInBegin,4,false);
						if(sip.transfers.front() == -2)
						{
							too_slow = true;
							return sip.transfers;
						}
                        else if(sip.transfers.front() != -1)
                            for(list<int>::iterator k = sip.transfers.begin(); k != sip.transfers.end(); k++)
                            {
                                permutationShelf.Move4InksBottles(j+1+(*k));
                                //cout << permutationShelf.ToString() << endl;
                                transforamtions.push_back(j+1+(*k));
                            }
                    }

                    transforamtions.push_back(j-4);
                    permutationShelf.Move4InksBottles(j-4);
                    /*cout << permutationShelf.ToString() << endl;
                    for(list<int>::iterator k = transforamtions.begin(); k != transforamtions.end(); k++)
                        cout << (*k);
                    cout << endl;*/
                }
                /*for(list<int>::iterator k = transforamtions.begin(); k != transforamtions.end(); k++)
                    cout << (*k);
                cout << endl;*/
                return transforamtions;
            }

        transforamtions.push_back(-1);
        /*for(list<int>::iterator k = transforamtions.begin(); k != transforamtions.end(); k++)
            cout << (*k);
        cout << endl;*/
        return transforamtions;
    }
    else
    {
		#ifdef __WIN32__
        LARGE_INTEGER nStopTime;
        LARGE_INTEGER nElapsed;
        LARGE_INTEGER nFrequency;
        ::QueryPerformanceCounter(&nStopTime);
        nElapsed.QuadPart = (nStopTime.QuadPart - nStartTime.QuadPart) * 1000000;
        nElapsed.QuadPart /= nFrequency.QuadPart;

       if((nElapsed).QuadPart > 5000)
		   return list<int>{-2};
#else
        steady_clock::time_point t2 = steady_clock::now();
        duration = t2-start_time;
		if((duration).count() > TIME_LIMIT)
		{
			cout << (duration).count() << endl;
			too_slow = true;
			throw to_string((duration).count());
			return list<int>{-2};
		}
#endif
        for(int i = 0; i < sShelf.length(); i++)
        {
            Shelf permutedSfelf(sShelf);

            permutedSfelf.Move4InksBottles(i);
            transforamtions = BrutalPermutation(permutedSfelf.ToString(),notSorted,deep - 1);
            if(transforamtions.front() != -1)
            {
				if(transforamtions.front() != -2)
					transforamtions.push_front(i);
				else
					too_slow = true;
                return transforamtions;
            }
        }
    }
    /*for(list<int>::iterator k = transforamtions.begin(); k != transforamtions.end(); k++)
        cout << (*k);
    cout << endl;*/
    return transforamtions;
}

std::list<int> SolutionInkProblem::BrutalPermutationLast6(string sShelf, int deep)
{
	if(too_slow)
		return list<int>{-2};
    list<int> transforamtions;

    if(deep == 0)
    {
        Shelf permutedSfelf(sShelf);
        if(permutedSfelf.Check())
            return transforamtions;

        transforamtions.push_back(-1);
        return transforamtions;
    }
    else
    {
        for(int i = 0; i < length() - 4; i++)
        {
            Shelf permutedSfelf(sShelf);
            permutedSfelf.Move4InksBottles(i);
            transforamtions = BrutalPermutationLast6(permutedSfelf.ToString(),deep - 1);
            if(transforamtions.front() != -1)
            {
                transforamtions.push_front(i);
                return transforamtions;
            }
        }
    }
    return transforamtions;
}

std::list<int> SolutionInkProblem::BrutalPermutationLast6(string sShelf, int deep, int firsts)
{
	if(too_slow)
		return list<int>{-2};
    list<int> transforamtions;

	if(sShelf.length() <= 6)
		return list<int>{-1};

    if(deep == 0)
    {
        Shelf permutedSfelf(sShelf);
        if(permutedSfelf.Check(firsts))
            return transforamtions;

        transforamtions.push_back(-1);
        return transforamtions;
    }
    else
    {
        for(int i = 0; i < length() - 4; i++)
        {
            Shelf permutedSfelf(sShelf);
            permutedSfelf.Move4InksBottles(i);
            transforamtions = BrutalPermutationLast6(permutedSfelf.ToString(),deep - 1);
            if(transforamtions.front() != -1)
            {
                transforamtions.push_front(i);
                return transforamtions;
            }
        }
    }
    return transforamtions;
}

bool SolutionInkProblem::Check()
{
    return shelf.Check();
}

bool SolutionInkProblem::Check(int firsts)
{
    return shelf.Check(firsts);
}

void SolutionInkProblem::ClearTerminal()
{
#ifdef __WIN32__
    system("cls");
#else
    system("clear");
#endif
}

int SolutionInkProblem::CountCostLast6Brutal()
{
	int result = 0;
	for(int i = 1; i <= 14; i++)
	{
		int tmp = pow(2,i);
		tmp *= i;
		result += tmp;
	}
	return result;
}

int SolutionInkProblem::CountCostBeginingBrutal(int l)
{
	if(l < 5)
		return 0;
	int result = 0;
	for(int j = l; j >= 7; j--)
	{
		for(int i = 1; i <= 3; i++)
		{
			int tmp = pow(j-4,i);
			tmp *= j/2;
			tmp += j;
			result += tmp;
		}
	}
	return result;
}

int SolutionInkProblem::CountCostBeginingBrutalSparing(int l)
{
	if(l < 5)
		return 0;
	int result = 0;
	for(int j = l; j >= 7; j--)
	{
		for(int i = 1; i <= 3; i++)
		{
			int tmp = pow(j-4,i);
			tmp *= j/2;
			tmp += j;
			tmp += CountCostBeginingBrutalSparing(l-4);
			result += tmp;
		}
	}
	return result;
}

int SolutionInkProblem::CountCostMod4(int l)
{
	if(l < 7)
		return 0;
	int result = 0;
	for(int j = 1; j <= l; j++)
	{
		result += (9*j/4 )+ 4;
	}
	return result;
}

int SolutionInkProblem::CountCostMod4Recurent(int l)
{
	if(l < 7)
		return 0;
	int result = 0;
	for(int j = 1; j <= l; j++)
	{
		result += 9*j/4 + 4;
		result += CountCostMod4Recurent(l - 4);
	}
	return result;
}

int SolutionInkProblem::CountCost(int mode)
{
	int result = 0;
	if(mode < 5)
		result = CountCostLast6Brutal();
	else
		result = 4012;

	if(length() > 6)
	{
		int tmp;
		switch(mode)
		{
			case 1:
				tmp = CountCostBeginingBrutal(length());
				break;
			case 2:
				tmp = CountCostBeginingBrutalSparing(length());
				break;
			case 3:
				tmp = CountCostMod4(length());
				break;
			case 4:
				tmp = CountCostMod4Recurent(length());
				break;
		}
		if(tmp > result)
			result = tmp;
	}
	teoretical_cost = result;
	return result;
}

list<Ink>::iterator SolutionInkProblem::FindByNumber(int numb)
{
    list<Ink>::iterator i = shelf.begin();

    for(int j = 0; j < numb; j++)
        i++;

    return i;
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
#ifdef __WIN32__
        LARGE_INTEGER nStopTime;
        LARGE_INTEGER nElapsed;
        LARGE_INTEGER nFrequency;
        ::QueryPerformanceCounter(&nStopTime);
        nElapsed.QuadPart = (nStopTime.QuadPart - nStartTime.QuadPart) * 1000000;
        nElapsed.QuadPart /= nFrequency.QuadPart;

       if((nElapsed).QuadPart > 5000)
        {
			cout << (duration).QuadPart << endl;
			too_slow = true;
			throw to_string((duration).QuadPart);
		}
#else
        steady_clock::time_point t2 = steady_clock::now();
        duration = t2-start_time;
		if((duration).count() > TIME_LIMIT)
		{
			cout << (duration).count() << endl;
			too_slow = true;
			throw to_string((duration).count());
		}
#endif

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
    cout << shelfOnBegining << " -> ";
    cout << shelf;
    cout << "distance: " << distance + (int)abs(start-pointer) << "\nnumberOfShifts: " << numberOfShifts << endl;
#ifdef __WIN32__
	cout << "Process duration:" << duration.QuadPart;
#else
    cout << "Process duration:"<< duration_cast<nanoseconds>(duration).count() << " ns" << endl;
#endif
    cout << "\ntransfers:\n";
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

bool SolutionInkProblem::RandomlyComplicate()
{
    Ink ink1(ToString()[length()-1]);
    Ink ink2(ToString()[length()-4]);

    string sShelf = "";
    for(int i = 0; i < 4; i++)
        sShelf += ToString()[length() - 4 + i];

    Shelf shelfTmp(sShelf);

    bool isBackSorted = shelfTmp.Check();

    char notSorted = 'C';
    int i = 0;
    int finded;
    char actualInkType;
    sShelf = ToString();
    while(i < length())
    {
        actualInkType = sShelf[i];

        if(actualInkType != notSorted)
        {
            finded = shelf.FindInkFrom(i, notSorted);
            if(finded == i)
            {
                NextToSort(notSorted);
                    if(notSorted == '0')
                        break;
                continue;
            }
        }
        if(ink2 != i || !isBackSorted)
        {
            shelf.ReversMove4InksBottles(i);
            return true;;
        }
        i++;
    }
    return false;
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

int SolutionInkProblem::Solve(int mode, bool animated)
{
	if(too_slow)
		return -2;
    char notSorted = 'C';
    int i = 0;
    int finded;
    char actualInkType;

    if(length() < 6)
    {
        if(length() == 5)
        {
            if(!shelf.IsLast5Solvable())
                return false;

            for(int i = 0; i < 5; i++)
            {
                Move4InksBottles(0,animated);
                if(Check())
                    return true;
            }
            return false;
        }

        //cout << "Shelf with less then 6 ink bottles can not by sorted!" << endl;
        return false;
    }


    while(shelf[i] != shelf.end())
    {
        actualInkType = (*shelf[i]).GetInkType();

        if(actualInkType != notSorted)
        {
            finded = shelf.FindInkFrom(i, notSorted);
            if(finded == i)
            {
                NextToSort(notSorted);
                    if(notSorted == '0')
                        break;
                continue;
            }
            else if(i >= length() - 6)
            {
                if(!Check())
                    switch(mode)
                    {
                    case 1 :
						if(!SolveLast6Brutal(animated))
							;//return false;
                        break;
                    case 2 :
                        if(!SolveLast6Brutal(animated))
							;//return false;
                        break;
                    case 3 :
                        if(!SolveLast6Brutal(animated))
							;//return false;
                        break;
                    case 4 :
                        if(!SolveLast6Brutal(animated))
							;//return false;
                        break;
                    case 5 :
                        if(!SolveLast6List(animated))
							;//return false;
                        break;
                    case 6 :
                        if(!SolveLast6List(animated))
							;//return false;
                        break;
					case 7:
                        if(!SolveLast6List(animated))
							;//return false;
                        break;
					case 8 :
                        if(!SolveLast6List(animated))
							;//return false;
                        break;
                    }
                break;
            }
            else
                switch(mode)
                    {
                    case 1 :
                        if(!SolveBrtualBegining(i,notSorted,animated))
							;//return false;
                        break;
                    case 2 :
                        if(!SolveBrtualBeginingSparing('0',i, notSorted, animated))
							;//return false;
                        break;
                    case 3 :
                        if(!MoveBottleToPos(i, finded, animated))
							;//return false;
                        break;
                    case 4 :
                        if(!SolveMod4(i, finded, '0', animated))
							;//return false;
                        break;
                    case 5 :
                        if(!SolveBrtualBegining(i,notSorted,animated))
							;//return false;
                        break;
                    case 6 :
                        if(!SolveBrtualBeginingSparing('0',i, notSorted, animated))
							;//return false;
                        break;
					case 7 :
                        if(!MoveBottleToPos(i, finded, animated))
							;//return false;
                        break;
					case 8 :
                        if(!SolveMod4(i, finded, '0', animated))
							;//return false;
                        break;
                    }
        }

        i++;
    }

    return true;
}

int SolutionInkProblem::Solve(char biggestInBegin, int mode, bool animated)
{
	if(too_slow)
		return -2;
    char notSorted = 'C';
    int i = 0;
    int finded;
    char actualInkType;

    if(length() < 6)
    {
        if(length() == 5)
        {
            if(!shelf.IsLast5Solvable())
                return false;

            for(int i = 0; i < 5; i++)
            {
                Move4InksBottles(0,animated);
                if(Check())
                    return true;
            }
            return false;
        }

        cout << "Shelf with less then 5 ink bottles can not by sorted!" << endl;
        return false;
    }

    while(shelf[i] != shelf.end())
    {
        actualInkType = (*shelf[i]).GetInkType();

        if(actualInkType != notSorted)
        {
            finded = shelf.FindInkFrom(i, notSorted);
            if(finded == i)
            {
                NextToSort(notSorted);
                    if(notSorted == '0')
                        break;

                Ink ink1(biggestInBegin), ink2(notSorted);
                if(ink1 > ink2)
                    return false;

                continue;
            }
            else if(i >= length() - 6)
            {
                if(!Check())
                    switch(mode)
                    {
                    case 1 :
                        SolveLast6Brutal(animated);
                        break;
                    case 2 :
                        SolveLast6Brutal(animated);
                        break;
                    case 3 :
                        SolveLast6Brutal(animated);
                        break;
                    case 4 :
                        SolveLast6Brutal(animated);
                        break;
                    case 5 :
                        SolveLast6List(animated);
                        break;
                    case 6 :
                        SolveLast6List(animated);
                        break;
					case 7:
                        SolveLast6List(animated);
                        break;
					case 8 :
                        SolveLast6List(animated);
                        break;
                    }
                break;
            }
            else
                switch(mode)
                    {
                    case 1 :
                        SolveBrtualBegining(i,notSorted,animated);
                        break;
                    case 2 :
                        SolveBrtualBeginingSparing('0',i, notSorted, animated);
                        break;
                    case 3 :
                        MoveBottleToPos(i, finded, animated);
                        break;
                    case 4 :
                        SolveMod4(i, finded, '0', animated);
                        break;
                    case 5 :
                        SolveBrtualBegining(i,notSorted,animated);
                        break;
                    case 6 :
                        SolveBrtualBeginingSparing('0',i, notSorted, animated);
                        break;
					case 7 :
                        MoveBottleToPos(i, finded, animated);
                        break;
					case 8 :
                        SolveMod4(i, finded, '0', animated);
                        break;
                    }
        }

        i++;
    }

    return true;
}

int SolutionInkProblem::SolveBrutal(bool animated)
{
	if(too_slow)
		return -2;
    char notSorted = 'C';
    int j = 0;
    int finded;
    char actualInkType;

    if(length() < 6)
    {
        if(length() == 5)
        {
            if(!shelf.IsLast5Solvable())
                return false;

            for(int i = 0; i < 5; i++)
            {
                Move4InksBottles(0,animated);
                if(Check())
                    return true;
            }
			//if(animated)
				cout << "That shelf cant by sorted." << endl;
            return false;
        }
		//if(animated)
			cout << "Shelf with less then 6 ink bottles can not by sorted!" << endl;
        return false;
    }

    while(shelf[j] != shelf.end())
    {
        actualInkType = (*shelf[j]).GetInkType();

        if(actualInkType != notSorted)
        {
            finded = shelf.FindInkFrom(j, notSorted);
            if(finded == j)
            {
                NextToSort(notSorted);
                if(notSorted == '0')
                    break;
                continue;
            }
            else if(j >= length() - 5)
            {
                if(!Check())
                    if(!SolveLast6Brutal(animated))
                        return false;
                break;
            }
            else
			{
                SolveBrtualBegining(j,notSorted,animated);
				continue;
			}
        }

        j++;
    }

    return true;
}

int SolutionInkProblem::SolveBrtualBegining(int j, char notSorted, bool animated)
{
	if(too_slow)
		return -2;
    string ShelfEnding = "";
    string sShelf = ToString();

	if(length() - j <= 6)
		return 0;

    for(int l = j; l < length(); l++)
        ShelfEnding += sShelf[l];

    list<int> transforamtions;
    transforamtions.push_back(-1);
    for(int deep = 0;transforamtions.front() == -1; deep++)
        transforamtions = BrutalPermutation(ShelfEnding,notSorted,deep);

    if(transforamtions.front() != -1)
    {
        for(list<int>::iterator l = transforamtions.begin(); l != transforamtions.end(); l++)
                Move4InksBottles((*l) + j,animated);
        return true;
    }
    else
		return false;
}

int SolutionInkProblem::SolveBrtualBeginingSparing(char biggestInBegin, int j, char notSorted, bool animated)
{
	if(too_slow)
		return -2;
    string ShelfEnding = "";
    string sShelf = ToString();

	if(length() - j <= 6)
		return 0;

    for(int l = j; l < length(); l++)
        ShelfEnding += sShelf[l];

    list<int> transforamtions;
    transforamtions.push_back(-1);
    for(int deep = 0;transforamtions.front() == -1; deep++){
        transforamtions = BrutalPermutationSparing(biggestInBegin, ShelfEnding,notSorted,deep);
		if(transforamtions.front() == -2)
		{
			too_slow = true;
			return -2;
		}
	}

    if(transforamtions.front() != -1)
    {
        for(list<int>::iterator l = transforamtions.begin(); l != transforamtions.end(); l++)
                Move4InksBottles((*l) + j,animated);
        return true;
    }
    else return false;
}

int SolutionInkProblem::SolveLast6Brutal(bool animated)
{
    string ShelfEnding = "";
    string sShelf = ToString();

    for(int i = length() - 6; i < length(); i++)
        ShelfEnding += sShelf[i];

    list<int> transforamtions;

    transforamtions.push_back(-1);

    for(int deep = 0;transforamtions.front() == -1; deep++)
        transforamtions = BrutalPermutationLast6(ShelfEnding,deep);

    if(transforamtions.front() != -1)
    {
        for(list<int>::iterator l = transforamtions.begin(); l != transforamtions.end(); l++)
                Move4InksBottles((*l) + length() - 6,animated);
        return true;
    }
    else
    return false;
}

int SolutionInkProblem::SolveLast6Brutal(bool animated, int firsts)
{
    string ShelfEnding = "";
    string sShelf = ToString();

    for(int i = length() - 6; i < length(); i++)
        ShelfEnding += sShelf[i];

    list<int> transforamtions;

    transforamtions.push_back(-1);

    for(int deep = 0;transforamtions.front() == -1; deep++)
        transforamtions = BrutalPermutationLast6(ShelfEnding,deep,firsts);

    if(transforamtions.front() != -1)
    {
        for(list<int>::iterator l = transforamtions.begin(); l != transforamtions.end(); l++)
                Move4InksBottles((*l) + length() - 6,animated);
        return true;
    }
    else
    return false;
}

int SolutionInkProblem::SolveLast6List(bool animated)
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

int SolutionInkProblem::SolveMod4(int actPos, int bottleToBeMoved, char biggestInBegin, bool animated)
{
    int distance;
    Shelf permutationShelf(shelf);

    if(actPos >= length() - 6 || actPos < 0 || bottleToBeMoved >= length() || bottleToBeMoved < 0)
        return -1;
    if(actPos > bottleToBeMoved)
        return -1;

    while(actPos != bottleToBeMoved)
    {
#ifdef __WIN32__
        LARGE_INTEGER nStopTime;
        LARGE_INTEGER nElapsed;
        LARGE_INTEGER nFrequency;
        ::QueryPerformanceCounter(&nStopTime);
        nElapsed.QuadPart = (nStopTime.QuadPart - nStartTime.QuadPart) * 1000000;
        nElapsed.QuadPart /= nFrequency.QuadPart;

       if((nElapsed).QuadPart > 5000)
		{
			cout << "Too long: " << (nElapsed).QuadPart << endl;
			too_slow = true;
			throw to_string((nElapsed).QuadPart);
		}
#else
        steady_clock::time_point t2 = steady_clock::now();
        duration = t2-start_time;
		if((duration).count() > TIME_LIMIT)
		{
			cout << "Too long: " << (duration).count() << endl;
			too_slow = true;
			throw to_string((duration).count());
		}
#endif

        permutationShelf = shelf;
        distance = bottleToBeMoved - actPos;

        if(distance%4 == 0)
        {
            bool do_last_6 = (biggestInBegin == '0');
            Ink ink(biggestInBegin);

            //cout << permutationShelf.ToString() << endl;
            for(int k = actPos; k < bottleToBeMoved; k++)
                if((*permutationShelf[k]) > ink)
                {
                    //cout << permutationShelf.GetInk(k).GetInkType() << endl;
                    biggestInBegin = permutationShelf.GetInk(k).GetInkType();
                    ink = biggestInBegin;
                    if(biggestInBegin == 'C')
                        break;
                }

            string sShelf2 = "";
            for(int k = bottleToBeMoved + 1; k < permutationShelf.length(); k++)
                sShelf2 += permutationShelf.ToString()[k];
            //cout << sShelf2 << endl;
			if(sShelf2.length() > 7)
            if((do_last_6 && sShelf2.length() - bottleToBeMoved > 5) || bottleToBeMoved < ((int)sShelf2.length()) - 6)
            {
                SolutionInkProblem sip(sShelf2);
                sip.Solve(biggestInBegin,4,false);
                /*for(list<int>::iterator i = sip.transfers.begin(); i != sip.transfers.end(); i++)
                    cout << (*i);
                cout << endl;*/
                if(!sip.transfers.empty())
                    for(list<int>::iterator k = sip.transfers.begin(); k != sip.transfers.end(); k++)
                        Move4InksBottles(bottleToBeMoved + 1 + (*k), animated);
            }

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
                permutationShelf = shelf;

                if(bottleToBeMoved >= length() - 4 && nextPos <  bottleToBeMoved)
                {
                    bool do_last_6 = (biggestInBegin == '0');
                    Ink ink(biggestInBegin);

                    //cout << permutationShelf.ToString() << endl;
                    for(int k = actPos; k < bottleToBeMoved; k++)
                        if((*permutationShelf[k]) > ink)
                        {
                            //cout << permutationShelf.GetInk(k).GetInkType() << endl;
                            biggestInBegin = permutationShelf.GetInk(k).GetInkType();
                            ink = biggestInBegin;
                            if(biggestInBegin == 'C')
                                break;
                        }

                    string sShelf2 = "";
                    for(int k = bottleToBeMoved + 1; k < permutationShelf.length(); k++)
                        sShelf2 += permutationShelf.ToString()[k];
                    //cout << sShelf2 << endl;

					if(sShelf2.length() > 7)
                    if((do_last_6 && sShelf2.length() - bottleToBeMoved > 5) || bottleToBeMoved < ((int)sShelf2.length()) - 6)
                    {
                        SolutionInkProblem sip(sShelf2);
                        sip.Solve(biggestInBegin,4,false);
                        if(!sip.transfers.empty())
                            for(list<int>::iterator k = sip.transfers.begin(); k != sip.transfers.end(); k++)
                                Move4InksBottles(bottleToBeMoved + 1 + (*k), animated);
                    }

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
                            bool do_last_6 = (biggestInBegin == '0');
                            Ink ink(biggestInBegin);

                            //cout << permutationShelf.ToString() << endl;
                            for(int k = actPos; k < bottleToBeMoved; k++)
                                if((*permutationShelf[k]) > ink)
                                {
                                    //cout << permutationShelf.GetInk(k).GetInkType() << endl;
                                    biggestInBegin = permutationShelf.GetInk(k).GetInkType();
                                    ink = biggestInBegin;
                                    if(biggestInBegin == 'C')
                                        break;
                                }

                            string sShelf2 = "";
                            for(int k = bottleToBeMoved + 1; k < permutationShelf.length(); k++)
                                sShelf2 += permutationShelf.ToString()[k];
                            //cout << sShelf2 << endl;

							if(sShelf2.length() > 7)
                            if((do_last_6 && sShelf2.length() - bottleToBeMoved > 5) || bottleToBeMoved < ((int)sShelf2.length()) - 6)
                            {
                                SolutionInkProblem sip(sShelf2);
                                sip.Solve(biggestInBegin,4,false);
                                if(!sip.transfers.empty())
                                    for(list<int>::iterator k = sip.transfers.begin(); k != sip.transfers.end(); k++)
                                        Move4InksBottles(bottleToBeMoved + 1 + (*k), animated);
                            }

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

