#include <iostream>
#include "Ink.hpp"
#include "Shelf.hpp"
#include "Tests.hpp"
#include "PresentSolutionInkProblem.hpp"

using namespace std;

#ifdef __WIN32__
int main()
{
    string s;
    int argNumb;

    cout << "\tThe program sorting ink bottles.\n" <<
			"\t\ttest\ttesting program\n" <<
			"\t\tstring with only 'C', 'M', 'Y' and 'K' - sole given shelf (ex. solveInkProblem CCMYCK)\n" <<
			"\t\tfile \"fileName.txt\" - solve every shelf infile with given name (ex. file = \"CYKCYM\\nYKCYK\\nKYMKNY...\")\n" <<
			"\t\tnumb - generate randomly shelf with given length and solve it\n" <<
			"\t\thelp - this text\n" <<
			"\t\texit - close program\n";

    while(1)
    {
        cout << "Enter arguments:" << endl;
        cin >> s;

        if(s == "help")
            cout << "\tThe program sorting ink bottles.\n" <<
                "\t\ttest\ttesting program\n" <<
                "\t\tstring with only 'C', 'M', 'Y' and 'K' - sole given shelf (ex. solveInkProblem CCMYCK)\n" <<
                "\t\tfile \"fileName.txt\" - solve every shelf infile with given name (ex. file = \"CYKCYM\\nYKCYK\\nKYMKNY...\")\n" <<
                "\t\tnumb - generate randomly shelf with given length and solve it\n" <<
                "\t\thelp - this text\n" <<
                "\t\texit - close program\n" << endl;
        else if(s == "exit")
            return 0;
        else if(s == "test")
        {
            Tests t;
		    t.testAll();
        }
        else if(s == "file")
        {
            cin >> s;
            PresentSolutionInkProblem psip(s);
            cout << "Animate?[Y/N]" << endl;

            cin >> s;

            if(s != "Y" && s != "N")
                return 0;

            psip.Solve(s == "Y");

            psip.Print();
            return 0;
        }
        else
        {
            bool shelf = true;
            for(int i = 0; i < s.length(); i++)
            {
                if(s[i] != 'C' && s[i] != 'M' && s[i] != 'Y' && s[i] != 'K')
                {
                    shelf = false;
                    break;
                }
            }
            if(shelf)
            {
                SolutionInkProblem sip(s);
                string oldShelf = sip.ToString();
                cout << "Animate?[Y/N]" << endl;

                cin >> s;

                if(s != "Y" && s != "N")
                    return 0;

                sip.Solve(s == "Y");

                cout << "\n" << oldShelf << " -> ";
                sip.Print();
                return 0;
            }

            bool numb = true;
            if(s[0] < '1' || s[0] > '9')
                numb = false;

            if(numb)
                for(int i = 1; i < s.length(); i++)
                {

                    if(s[i] < '0' || s[i] > '9')
                    {
                        numb = false;
                        break;
                    }
                }
            if(numb)
            {
                SolutionInkProblem sip(stoi(s));
                string oldShelf = sip.ToString();

                while(s != "Y" && s != "N" && s != "y" && s != "n")
                {
                    cout << "Animate?[Y/N]" << endl;

                    cin >> s;
                }

                sip.Solve(s == "Y" || s == "y");

                cout << "\n" << oldShelf << " -> ";
                sip.Print();
                return 0;
            }
        }
    }

    return 0;
}
#else
int main(int argc, char **argv)
{
    StartProgram(argc,argv);

    return 0;
}
#endif
