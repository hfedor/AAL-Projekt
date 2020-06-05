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
    int m;
    int argNumb;

    cout << "\tThe program sorting ink bottles.\n" <<
			"\t\ttest\ttesting program\n" <<
			"\t\tstring with only 'C', 'M', 'Y' and 'K' - solve given shelf (ex. solveInkProblem CCMYCK)\n" <<
			"\t\tfile \"fileName.txt\" - solve every shelf infile with given name (ex. file = \"CYKCYM\\nYKCYK\\nKYMKNY...\")\n" <<
			"\t\tnumb - generate randomly shelf with given length and solve it\n" <<
			"\t\t<n1,n2> - solve shelves with lengths from n1 to n2\m" <<
			"\t\thelp - this text\n" <<
			"\t\texit - close program\n";

    while(1)
    {
        cout << "Enter arguments:" << endl;
        cin >> s;

        if(s == "help")
            cout << "\tThe program sorting ink bottles.\n" <<
                "\t\ttest\ttesting program\n" <<
                "\t\tstring with only 'C', 'M', 'Y' and 'K' - solve given shelf (ex. solveInkProblem CCMYCK)\n" <<
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

            psip.Solve(m, s == "Y");

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
                PresentSolutionInkProblem psip(1,s);
                string oldShelf = s;
                cout << "Animate?[Y/N]" << endl;

                cin >> s;

                while(s != "Y" && s != "N" && s != "y" && s != "n")
                {
                    cout << "Animate?[Y/N]" << endl;

                    cin >> s;
                }

                cout << "With mode?" << endl;

                cin >> m;

                psip.Solve(m,s == "Y" || s == "y");

                return 0;
            }

            bool numb = true;
            if(s[0] < '1' || s[0] > '9')
                numb = false;

            if(numb)
                for(int i = 1; i < s.length(); i++)
                    if(s[i] < '0' || s[i] > '9')
                    {
                        numb = false;
                        break;
                    }
            if(numb)
            {
                PresentSolutionInkProblem psip(1,stoi(s));
                string oldShelf = s;

                while(s != "Y" && s != "N" && s != "y" && s != "n")
                {
                    cout << "Animate?[Y/N]" << endl;

                    cin >> s;
                }

                cout << "With mode?" << endl;

                cin >> m;

                psip.Solve(m, s == "Y" || s == "y");

                return 0;
            }

            bool range = false;

            if(s[0] == '<')
                range = true;
            int i = 1;
            int n1, n2;
            string n1s = "", n2s = "";
            while(range)
            {
                if(s[i] == ',')
                {
                    if(n1s != "")
                        n1 = stoi(n1s);
                    i++;
                    break;
                }
                if(s[i] < '0' || s[i] > '9')
                    range = false;
                n1s += s[i];
                i++;
            }
            while(range)
            {
                if(s[i] == '>')
                {
                    if(n2s != "")
                        n2 = stoi(n2s);
                    break;
                }
                if(s[i] < '0' || s[i] > '9')
                    range = false;
                n2s += s[i];
                i++;
            }
            if(range && n1 > n2)
            {
                range = false;
                cout << "n1(" << n1 << ") > n2(" << n2 << ")!" << endl;
            }

            if(range)
            {
                PresentSolutionInkProblem psip;
                string oldShelf = s;

                psip.SolveN(n1,n2);

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
