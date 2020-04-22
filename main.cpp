#include <iostream>
#include "Ink.hpp"
#include "Shelf.hpp"
#include "Tests.hpp"
#include "PresentSolutionInkProblem.hpp"

using namespace std;

int main(int argc, char **argv)
{
	if(argc == 1)
		cout << "\tThe program sorting ink bottles.\n" <<
			"\t\ttest\ttesting program\n" <<
			"\t\tstring with only 'C', 'M', 'Y' and 'K' - sole given shelf (ex. solveInkProblem CCMYCK)\n" <<
			"\t\tfile \"fileName.txt\" - solve every shelf infile with given name (ex. file = \"CYKCYM\\nYKCYK\\nKYMKNY...\")\n" <<
			"\t\tnumb - generate randomly shelf with given length and solve it\n" <<
			"\t\t\t anim - solve with animation\n";
	if(argc == 2)
	{
		if(argv[1] == "test")
		{
		    Tests t;
		    t.testAll();
		}

		string args = argv[1];

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
			SolutionInkProblem sip(argv[1]);
			string oldShelf = sip.ToString();
			sip.Solve(false);
			cout << "\n" << oldShelf << " -> ";
			sip.Print();
			return 0;
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
			SolutionInkProblem sip(atoi(argv[1]));
			string oldShelf = sip.ToString();
			sip.Solve(false);
			cout << "\n" << oldShelf << " -> ";
			sip.Print();
			return 0;
		}

		cout << "Wrong arguments!" << endl;
	}
	else if(argc == 3)
	{
		if(argv[1] == "file")		
		{
			PresentSolutionInkProblem psip(argv[1]);
			psip.Solve(false);
			psip.Print();
			cout << endl;
			return 0;
		}

		if(argv[2] != "anim")
		{
			string args = argv[1];

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
				SolutionInkProblem sip(argv[1]);
				string oldShelf = sip.ToString();
				sip.Solve(true);
				cout << "\n" << oldShelf << " -> ";
				sip.Print();
				return 0;
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
				SolutionInkProblem sip(atoi(argv[1]));
				string oldShelf = sip.ToString();
				sip.Solve(true);
				cout << "\n" << oldShelf << " -> ";
				sip.Print();
				return 0;
			}
		}

		cout << "Wrong arguments!" << endl;
	}	

    return 0;
}
