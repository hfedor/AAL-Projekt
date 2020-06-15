#ifndef PRESENTSOLUTIONINKPROBLEM_HPP
#define PRESENTSOLUTIONINKPROBLEM_HPP

#include <list>
#include <vector>
#include "SolutionInkProblem.hpp"

/*
    Class for presentation the algorithm results.
*/

class PresentSolutionInkProblem
{
private:
    std::list<SolutionInkProblem*> solutions; // list of solved problem of sorting ink bottles
public:
    PresentSolutionInkProblem();
    PresentSolutionInkProblem(int solutionsNumb, int inksNumb); // construct given number of solutions with given numbers of ink bottles
    PresentSolutionInkProblem(int SolutionsNumb, std::string newShelf); // construct given number of solutions with given shelf
    PresentSolutionInkProblem(std::string fileNama); // load solutions from file with given name
    SolutionInkProblem* AddSolution(std::string shelf); // add solution with given shelf to the list
    bool Check();
    std::list<SolutionInkProblem*>::iterator GetBegin(){return solutions.begin();}
    std::list<SolutionInkProblem*>::iterator GetEnd(){return solutions.end();}
    SolutionInkProblem* FindGame(std::string shelf); // find in the list solution with given shelf
    int GetSize(){return solutions.size();} // get number of solutions on the list
    bool IsSolutionNew(std::list<SolutionInkProblem*>::iterator g); // check is the solution with given shelf already on the list
    void Loadsolutions(std::string file);
    void Print();
    void PrintForAnimation(std::list<SolutionInkProblem*>::iterator solution, int ste);
    void PrintShelf();
    void Savesolutions(std::string fileName);
    void Sortsolutions();
    void Solve(int mode, bool animated);
    void SolveN(int n1, int n2);
    void SolveN(int length, int n1, int n2);
    void SolveBrutal(bool animated);
    int numb(){return solutions.size();}
    ~PresentSolutionInkProblem();
};

void StartProgram(int, char**);

#endif // PRESENTSOLUTIONINKPROBLEM_HPP
