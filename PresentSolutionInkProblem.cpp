#include "PresentSolutionInkProblem.hpp"

#include <math.h>
#include <string>
#include <fstream>

using namespace std;

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

void PresentSolutionInkProblem::Solve(bool animated)
{
    string s;
    for(list<SolutionInkProblem*>::iterator g = GetBegin(); g != GetEnd(); g++)
    {
        s = (*g)->ToString();
        for(int i = 0; i < (*g)->length() - 4; i++)
            (*g)->Solve(animated);
        if(!(*g)->Check())
        {
            cout << (*g)->ToString() << "\t";
            cout << s << endl;
        }
    }
}

PresentSolutionInkProblem::~PresentSolutionInkProblem()
{
    for(list<SolutionInkProblem*>::iterator i = solutions.begin(); i != solutions.end(); i++)
    {
        delete (*i);
    }
}
