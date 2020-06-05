#include "PresentSolutionInkProblem.hpp"
#include "Tests.hpp"

#include <math.h>
#include <string>
#include <fstream>
#include <chrono>
#include "table_printer.h"

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
    int i = 1;
    for(; g != GetEnd(); g++)
    {
        cout << "\nmode: " << i << endl;

        steady_clock::time_point t = steady_clock::now();

        (*g)->Solve(i,false);

        steady_clock::duration d = steady_clock::now()-t;
        (*g)->SetDuration(d);

        if((*g)->Check())
        {
            cout << s << endl;
            (*g)->Print();
        }

        i++;
    }
}

void PresentSolutionInkProblem::SolveN(int n1, int n2)
{
    string s;

    for(int i = n1; i <= n2; i++)
    {
        SolutionInkProblem sip(i);
        s = sip.ToString();
        for(int j = 0; j < 6; j++)
            AddSolution(s);
    }

    list<SolutionInkProblem*>::iterator g = GetBegin();
    int i = 0;
    for(; g != GetEnd(); g++)
    {
        steady_clock::time_point t = steady_clock::now();

        (*g)->Solve(i%6 + 1,false);

        steady_clock::duration d = steady_clock::now()-t;
        (*g)->SetDuration(d);

        i++;
    }

    bprinter::TablePrinter tp(&std::cout,"|");
    tp.AddColumn("Mode1", n2);
    tp.AddColumn("Mode2", 5);
    tp.AddColumn("Mode3", 5);
    tp.AddColumn("Mode4", 10);

    tp.PrintHeader();
    for(g = GetBegin(); g != GetEnd(); g++)
    {
        tp << (*g)->ToString() << (*g)->GetDistance() << (*g)->GetNumberOfShifts() << duration_cast<nanoseconds>((*g)->GetDuration()).count();
    }
    tp << bprinter::endl();
    tp.PrintFooter();
    /*
    i = 0;
    g = GetBegin();
    string tabs = "\t";
    string line = "--------------";
    for(int j = 0; j < ((n2 + 1)-((n2 + 1)%16))/16; j++)
    {
        tabs += "\t";
        line += "--------------";
    }
    string line2 = line;
    for(int j = 0; j < 6; j++)
    {
        line += line2;
    }
    line += "\n";
    for(int j = n1; j <= n2; j++)
    {
        list<SolutionInkProblem*>::iterator tmp = g;
        cout << line;
        for(int l = 0; l < 6; l++)
        {
            cout << (*g)->ToString() << tabs <<"|";
            g++;
        }
        g = tmp;
        cout << "\n|";
        for(int l = 0; l < 6; l++)
        {
            cout << (*g)->GetDistance() << tabs << "\t|";
            g++;
        }
        cout << "\n|";
        g = tmp;
        for(int l = 0; l < 6; l++)
        {
            cout << (*g)->GetNumberOfShifts() << tabs << "\t|";
            g++;
        }
        cout << "\n|";
        g = tmp;
        for(int l = 0; l < 6; l++)
        {
            cout << duration_cast<microseconds>((*g)->GetDuration()).count() << tabs << "\t|";
            g++;
        }
        cout << "\n";
    }
    cout << line;*/

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
    for(int i = 0; i < argNumb; i++)
        cout << arguments[i] << " ";
    cout << endl;

    if(argNumb == 1)
		cout << "\tThe program sorting ink bottles.\n" <<
			"\t\ttest\ttesting program\n" <<
			"\t\tstring with only 'C', 'M', 'Y' and 'K' - solve given shelf (ex. solveInkProblem CCMYCK)\n" <<
			"\t\tfile \"fileName.txt\" - solve every shelf infile with given name (ex. file = \"CYKCYM\\nYKCYK\\nKYMKNY...\")\n" <<
			"\t\tnumb - generate randomly shelf with given length and solve it\n" <<
			"\t\t\t anim - solve with animation\n" << endl;
	if(argNumb == 2)
	{
		if(arguments[1] == "test")
		{
		    Tests t;
		    t.testAll();
		}

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
}

PresentSolutionInkProblem::~PresentSolutionInkProblem()
{
    for(list<SolutionInkProblem*>::iterator i = solutions.begin(); i != solutions.end(); i++)
    {
        delete (*i);
    }
}
