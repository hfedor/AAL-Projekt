#include "PresentSolutionInkProblem.hpp"
#include "Tests.hpp"

#include <math.h>
#include <string>
#include <fstream>
#include <chrono>
#include "table_printer.h"
#include <cstdint>

#ifdef __WIN32__

#include <windows.h>

#else

#endif

using namespace std;
using namespace std::chrono;

PresentSolutionInkProblem::PresentSolutionInkProblem()
{

}

PresentSolutionInkProblem::PresentSolutionInkProblem(int solutionNmb, int inksNumb)
{
    for(int i = 0; i < solutionNmb; i++)
    {
        SolutionInkProblem *newSolution = new SolutionInkProblem(inksNumb);
        solutions.push_back(newSolution);
    }
}

PresentSolutionInkProblem::PresentSolutionInkProblem(int solutionNmb, string newShelf)
{
    for(int i = 0; i < solutionNmb; i++)
    {
        SolutionInkProblem *newSolution = new SolutionInkProblem(newShelf);
        solutions.push_back(newSolution);
    }
}

PresentSolutionInkProblem::PresentSolutionInkProblem(string fileName)
{
    fstream file;
    string line;
    int solutionsSize;

    file.open( fileName, std::ios::in);

    while(getline(file,line))
    {
        SolutionInkProblem *newSolution = new SolutionInkProblem(line);
        solutions.push_back(newSolution);
    }

    file.close();
}

SolutionInkProblem* PresentSolutionInkProblem::AddSolution(string shelf)
{
    SolutionInkProblem *newSolution = new SolutionInkProblem(shelf);
    solutions.push_back(newSolution);
    return newSolution;
}

bool PresentSolutionInkProblem::Check()
{
    for(list<SolutionInkProblem*>::iterator i = solutions.begin(); i != solutions.end(); i++)
        if((*i)->Check() == false)
            return false;

    return true;
}

SolutionInkProblem* PresentSolutionInkProblem::FindGame(string shelf)
{
    for(list<SolutionInkProblem*>::iterator i = solutions.begin(); i != solutions.end(); i++)
    {
        if((*(*i)) == shelf)
            return (*i);
    }
    return NULL;
}

void PresentSolutionInkProblem::Loadsolutions(string f)
{
    fstream file;
    string line;

    file.open( f, std::ios::in);

    while(getline(file,line))
        AddSolution(line);

    file.close();
}

void PresentSolutionInkProblem::Print()
{
    for(list<SolutionInkProblem*>::iterator i = solutions.begin(); i != solutions.end(); i++)
        (*i)->Print();
}

void PresentSolutionInkProblem::PrintShelf()
{
    for(list<SolutionInkProblem*>::iterator i = solutions.begin(); i != solutions.end(); i++)
    {
        (*i)->ToString();
        cout << endl;
    }
}

void PresentSolutionInkProblem::Sortsolutions()
{
    list<SolutionInkProblem*>::iterator j;
    SolutionInkProblem* tmp;
    Shelf s1, s2;

    for(list<SolutionInkProblem*>::iterator k = solutions.end(); k != solutions.begin(); k--)
    {
        for(list<SolutionInkProblem*>::iterator i = solutions.begin(); i != k; i++)
        {
            j = i;
            j++;
            if(j == k)
                break;
            s1 = (*i)->GetShelf();
            s2 = (*j)->GetShelf();
            if(s1 < s2)
            {
                tmp = (*i);
                (*i) = (*j);
                (*j) = (tmp);
            }
        }
    }
}

void PresentSolutionInkProblem::Solve(int mode, bool animated)
{
    string s;

    if(animated)
        AddSolution(s);

    if(animated)
        solutions.front()->Solve(mode,animated);

    list<SolutionInkProblem*>::iterator g = GetBegin();
    if(animated)
        g++;

#ifdef __WIN32__
	LARGE_INTEGER nStartTime;
	LARGE_INTEGER nStopTime;
	LARGE_INTEGER nElapsed;
	LARGE_INTEGER nFrequency;

	::QueryPerformanceFrequency(&nFrequency);
	::QueryPerformanceCounter(&nStartTime);
#else
    steady_clock::time_point t1 = steady_clock::now();
#endif

    (*g)->Solve(mode,false);

#ifdef __WIN32__
	::QueryPerformanceCounter(&nStopTime);
	nElapsed.QuadPart = (nStopTime.QuadPart - nStartTime.QuadPart) * 1000000;
	nElapsed.QuadPart /= nFrequency.QuadPart;

   (*g)->SetDuration(nElapsed);
#else
	steady_clock::time_point t2 = steady_clock::now();
	steady_clock::duration d = t2-t1;
#endif
    if((*g)->Check())
    {
        cout << s << endl;
        (*g)->Print();
    }
}

void PresentSolutionInkProblem::SolveN(int n1, int n2)
{
    string s, stmp1, stmp2;

    Shelf shelfTmp1(n1 - 1);

    s = shelfTmp1.ToString();

	int mediana = (n2-n1+2)/2;
	SolutionInkProblem *tmp;
	vector<SolutionInkProblem*> mediana_solution;

	bool count[8];
	for(int i = 0; i < 8; i++)
	{
		count[i] = true;
	}

    srand(time(NULL));

    for(int n = n1; n <= n2; n++)
    {
        int iter = rand()%s.length();
        for(int i = s.length()-1; i >= 0; i--)
        {
            stmp1 = "";

            if(i == 0)
            {
                if(s[iter] == 'C')
                    stmp1 += 'M';
                else if(s[iter] == 'Y')
                    stmp1 += 'K';
                else
                    stmp1 += 'Y';

                stmp1 += s;
                break;
            }

            stmp2 = s[iter-1] + s[iter];
            Shelf shelfTmp2(stmp2);
            if(shelfTmp2.Check())
            {
                for(int j = 0; j < iter; j++)
                    stmp1 += s[j];
                if(s[i] == 'C')
                    stmp1 += 'M';
                else if(s[iter] == 'M')
                    stmp1 += 'Y';
                else if(s[iter] == 'Y')
                    stmp1 += 'K';
                else
                    stmp1 += 'C';
                for(int j = iter; j < s.length(); j++)
                    stmp1 += s[j];
                break;
            }

            iter--;
            if(iter <= 0)
                iter = s.length() - 1;
        }

        s = stmp1;

        SolutionInkProblem sip(s);
        for(int j = 0; j < 8; j++){
            tmp = AddSolution(s);
		}
    }

    list<SolutionInkProblem*>::iterator g = GetBegin();
    int i = 0;
	int n = 0;
    for(; g != GetEnd(); g++)
    {
			if(i%8 == 0)
				n++;
#ifdef __WIN32__
        LARGE_INTEGER nStartTime;
        LARGE_INTEGER nStopTime;
        LARGE_INTEGER nElapsed;
        LARGE_INTEGER nFrequency;

        ::QueryPerformanceFrequency(&nFrequency);
        ::QueryPerformanceCounter(&nStartTime);
#else
        steady_clock::time_point t1 = steady_clock::now();
#endif

		if(count[i%8])
		{
			try
			{
				(*g)->Solve(i%8 + 1,false);
			}
			catch (string err)
			{
				cout << err << endl;
				count[i%8] = false;
			}
		}
		else
			(*g)->SetTooSlow(true);

#ifdef __WIN32__
        ::QueryPerformanceCounter(&nStopTime);
        nElapsed.QuadPart = (nStopTime.QuadPart - nStartTime.QuadPart) * 1000000;
        nElapsed.QuadPart /= nFrequency.QuadPart;

       (*g)->SetDuration(nElapsed);
#else
         steady_clock::time_point t2 = steady_clock::now();
        steady_clock::duration d = t2-t1;

		(*g)->SetDuration(d);
#endif

		if(count[i%8])
		{
			if(n <= mediana)
			{
				if(mediana_solution.size() < 8)
					mediana_solution.push_back(*	g);
				else
					mediana_solution[i%8] = (*g);
			}

			(*g)->CountCost(i%8);
		}

        i++;
    }

    bprinter::TablePrinter tp(&std::cout,"|");
    tp.AddColumn("n", 4);
    tp.AddColumn("Last6/Begining", 15);
    tp.AddColumn("Shelf befor soritng", max(n2,20));
    tp.AddColumn("Shelf after soritng", max(n2,20));
    tp.AddColumn("distance", 8);
    tp.AddColumn("shifts", 8);
    tp.AddColumn("duration", 10);
    tp.AddColumn("teoretical cost", 15);

    tp.PrintHeader();
    i = 0;
    for(g = GetBegin(); g != GetEnd(); g++)
    {
		float q = 0;
		string sShelf = (*g)->ToString();
		if((*g)->GetTooSlow())
			sShelf = "It was to slow...";

		string mode;
		switch(i%8)
		{
			case 0:
				mode = "Brut  /  Brutal";
				break;
			case 1:
				mode = "Brut  / BrutRec";
				break;
			case 2:
				mode = "Brut  /    Mod4";
				break;
			case 3:
				mode = "Brut  / Mod4Rec";
				break;
			case 4:
				mode = "List  /  Brutal";
				break;
			case 5:
				mode = "List  / BrutRec";
				break;
			case 6:
				mode = "List  /    Mod4";
				break;
			case 7:
				mode = "List  / Mod4Rec";
				break;
		}
#ifdef __WIN32__
		if(!mediana_solution.empty())
			if(mediana_solution[i%8] != NULL)
			{
                q = (float)((*g)->GetDuration()).QuadPart;
				q *=  (float)((*mediana_solution[i%8]).GetTeoreticalCost());
				q /= (float)((*mediana_solution[i%8]).GetDuration().QuadPart);
				q /= (float)((*g)->GetTeoreticalCost());
			}
			else q = -2;
		tp << (*g)->GetShelfOnBegining().length() << mode << (*g)->GetShelfOnBegining() <<  sShelf << (*g)->GetDistance() << (*g)->GetNumberOfShifts() <<((*g)->GetDuration()).QuadPart << q ;
#else
		if(!mediana_solution.empty())
			if(mediana_solution[i%8] != NULL)
				q = (float)((*g)->GetDuration()).count() *  (float)(*mediana_solution[i%8]).GetTeoreticalCost() /((float)((*mediana_solution[i%8]).GetDuration()).count() *(float)(*g)->GetTeoreticalCost() );
			else q = -2;
		else
			q = -1;
		tp << (*g)->GetShelfOnBegining().length() << mode << (*g)->GetShelfOnBegining() << sShelf << (*g)->GetDistance() << (*g)->GetNumberOfShifts() <<duration_cast<microseconds>((*g)->GetDuration()).count() << q;
#endif
		if(i%8 == 7)
            tp.PrintFooter();
        i++;
    }
    if(i%8 != 0)
        tp << bprinter::endl();
    tp.PrintFooter();
}

void PresentSolutionInkProblem::SolveN(int length, int n1, int n2)
{
    string s;


    SolutionInkProblem sip(length);
    sip.Sort();

    for(int i = 0; i <= n2; i++)
    {
        sip.RandomlyComplicate();
        s = sip.ToString();
        if(i >= n1)
            for(int j = 0; j < 8; j++)
                AddSolution(s);
    }

    list<SolutionInkProblem*>::iterator g = GetBegin();
    int i = 0;
    for(; g != GetEnd(); g++)
    {
#ifdef __WIN32__
        LARGE_INTEGER nStartTime;
        LARGE_INTEGER nStopTime;
        LARGE_INTEGER nElapsed;
        LARGE_INTEGER nFrequency;

        ::QueryPerformanceFrequency(&nFrequency);
        ::QueryPerformanceCounter(&nStartTime);
#else
        steady_clock::time_point t1 = steady_clock::now();
#endif

        (*g)->Solve(i%8 + 1,false);

#ifdef __WIN32__
        ::QueryPerformanceCounter(&nStopTime);
        nElapsed.QuadPart = (nStopTime.QuadPart - nStartTime.QuadPart) * 1000000;
        nElapsed.QuadPart /= nFrequency.QuadPart;

       (*g)->SetDuration(nElapsed);
#else
         steady_clock::time_point t2 = steady_clock::now();
        steady_clock::duration d = t2-t1;
#endif

        i++;
    }

    bprinter::TablePrinter tp(&std::cout,"|");
    tp.AddColumn("Mode1", length);
    tp.AddColumn("Mode1", length);
    tp.AddColumn("Mode2", 5);
    tp.AddColumn("Mode3", 5);
    tp.AddColumn("Mode4", 10);

    tp.PrintHeader();
    i = 0;
    for(g = GetBegin(); g != GetEnd(); g++)
    {
        //int64_t c =
        tp << (*g)->GetShelfOnBegining().length() << (*g)->GetShelfOnBegining() << (*g)->ToString() << (*g)->GetDistance() << (*g)->GetNumberOfShifts() <<
#ifdef __WIN32__
		((*g)->GetDuration()).QuadPart ;
#else
		duration_cast<microseconds>((*g)->GetDuration()).count();
#endif
		if(i%8 == 7)
            tp.PrintFooter();
        i++;
    }
    if(i%8 != 0)
        tp << bprinter::endl();
    tp.PrintFooter();
}

void PresentSolutionInkProblem::SolveBrutal(bool animated)
{
    string s;
    for(list<SolutionInkProblem*>::iterator g = GetBegin(); g != GetEnd(); g++)
    {
        s = (*g)->ToString();
        for(int i = 0; i < (*g)->length() - 4; i++)
            (*g)->SolveBrutal(animated);

        if(!(*g)->Check())
        {
            cout << (*g)->ToString() << "\t";
            cout << s << endl;
        }
    }
}

void StartProgram(int argNumb, char **arguments)
{
	cout << argNumb << endl;
    for(int i = 0; i < argNumb; i++)
        cout << arguments[i] << " ";
    cout << endl;

    if(argNumb == 1)
		cout << "\tThe program sorting ink bottles.\n" <<
			"\t\ttest\ttesting program\n" <<
			"\t\tstring with only 'C', 'M', 'Y' and 'K' - solve given shelf (ex. solveInkProblem CCMYCK)\n" <<
			"\t\tfile \"fileName.txt\" - solve every shelf infile with given name (ex. file = \"CYKCYM\\nYKCYK\\nKYMKNY...\")\n" <<
			"\t\tnumb - generate randomly shelf with given length and solve it\n" <<
			"\t\tn n1 n2- solve shelves with lengths from n1 to n2 (ex. n 7 12)\n" <<
			"\t\thelp - this text\n" <<
			"\t\texit - close program" << endl;
	if(argNumb == 2)
	{
		string args = arguments[1];
		if(args == "test")
		{
		    Tests t;
		    t.testAll();
		}

		bool shelf = true;
		for(int i = 0; i < args.length(); i++)
		{
			if(args[i] != 'C' && args[i] != 'M' && args[i] != 'Y' && args[i] != 'K')
			{
				shelf = false;
				break;
			}
		}
		if(shelf)
		{
			SolutionInkProblem sip(arguments[1]);
			string oldShelf = sip.ToString();
			sip.Solve(1,false);
			cout << "\n" << oldShelf << " -> ";
			sip.Print();
			return;
		}

		bool numb = true;
		if(args[0] < '1' || args[0] > '9')
			numb = false;

		if(numb)
			for(int i = 1; i < args.length(); i++)
			{

				if(args[i] < '0' || args[i] > '9')
				{
					numb = false;
					break;
				}
			}
		if(numb)
		{
			SolutionInkProblem sip(atoi(arguments[1]));
			string oldShelf = sip.ToString();
			sip.Solve(1,false);
			cout << "\n" << oldShelf << " -> ";
			sip.Print();
			return;
		}

		cout << "Wrong arguments!" << endl;
	}
	else if(argNumb == 3)
	{
		if(arguments[1] == "file")
		{
			PresentSolutionInkProblem psip(arguments[1]);
			psip.Solve(1,false);
			psip.Print();
			cout << endl;
			return;
		}

		if(arguments[2] != "anim")
		{
			string args = arguments[1];

			bool shelf = true;
			for(int i = 0; i < args.length(); i++)
			{
				if(args[i] != 'C' && args[i] != 'M' && args[i] != 'Y' && args[i] != 'K')
				{
					shelf = false;
					break;
				}
			}
			if(shelf)
			{
				SolutionInkProblem sip(arguments[1]);
				string oldShelf = sip.ToString();
				sip.Solve(1,true);
				cout << "\n" << oldShelf << " -> ";
				sip.Print();
				return;
			}

			bool numb = true;
			if(args[0] < '1' || args[0] > '9')
				numb = false;

			if(numb)
				for(int i = 1; i < args.length(); i++)
				{

					if(args[i] < '0' || args[i] > '9')
					{
						numb = false;
						break;
					}
				}
			if(numb)
			{
				SolutionInkProblem sip(atoi(arguments[1]));
				string oldShelf = sip.ToString();
				sip.Solve(1,true);
				cout << "\n" << oldShelf << " -> ";
				sip.Print();
				return;
			}
		}

		cout << "Wrong arguments!" << endl;
	}
	else if(argNumb == 4)
	{
		string args = arguments[1];

		if(args == "n")
		{
			bool range = true;

			args = arguments[2];

			if(args[0] < '1' || args[0] > '9')
				range = false;

			if(range)
				for(int i = 1; i < args.length(); i++)
				{
					if(args[i] < '0' || args[i] > '9')
					{
						range = false;
						break;
					}
				}

			args = arguments[3];

			if(args[0] < '1' || args[0] > '9')
				range = false;

			if(range)
				for(int i = 1; i < args.length(); i++)
				{
					if(args[i] < '0' || args[i] > '9')
					{
						range = false;
						break;
					}
				}

			if(range)
			{

				int n1 =atoi(arguments[2]), n2 = atoi(arguments[3]);

				if(range && n2 < n1)
				{
					range = false;
					cout << "n1(" << n1 << ") > n2(" << n2 << ")!" << endl;
				}

				PresentSolutionInkProblem psip;
				psip.SolveN(n1,n2);

				return ;
			}
		}

		cout << "Wrong arguments!" << endl;
	}
}

PresentSolutionInkProblem::~PresentSolutionInkProblem()
{
    for(list<SolutionInkProblem*>::iterator i = solutions.begin(); i != solutions.end(); i++)
    {
        delete (*i);
    }
}
