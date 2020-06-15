#ifndef SOLUTIONINKPROBLEM_HPP
#define SOLUTIONINKPROBLEM_HPP

#include "Shelf.hpp"
#include <fstream>
#include <chrono>
#include <math.h>	
#include <cstdint>

#ifdef __WIN32__

#include <windows.h>

#else

#endif

const long TIME_LIMIT = 50000000000;

/*
    Class for solving problem of sorting ink bottles by the machine described in the task.
*/
class SolutionInkProblem
{
    private:
        Shelf shelf; // shelf with ink bottles
        int pointer; // number of ink bottle under the machine arm
        int distance; // distance traveled by the arm of the machine
        int numberOfShifts; // number of ink bottles transfers made by the chine
        int start; // position where the arm of the machine starts
        std::list<int> transfers; // list of ink bottles (firsts of them from the left) moved by the arm of the machine
		int teoretical_cost = 1; // teoretical cost
		bool too_slow = false;
#ifdef __WIN32__
        LARGE_INTEGER nStartTime;
        LARGE_INTEGER duration;
#else
        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
		std::chrono::steady_clock::duration duration;
#endif
        std::string shelfOnBegining;
    public:
        SolutionInkProblem(int inksNumb); // constructor with given number of ink bottles on the constructed shelf
        SolutionInkProblem(std::string new_shelf); // constructor with given ink bottles on the constructed shelf
        std::list<Ink>::iterator begin(){return shelf.begin();}
        std::list<int> BrutalPermutation(std::string sShelf, char notSorted, int deep);
        std::list<int> BrutalPermutationSparing(char biggestInBegin, std::string sShelf, char notSorted, int deep);
        std::list<int> BrutalPermutationSparing2(std::string sShelf, char notSorted, int deep);
        std::list<int> BrutalPermutationLast6(std::string sShelf,int deep);
        std::list<int> BrutalPermutationLast6(std::string sShelf,int firsts, int deep);
        bool Check(); // check the shelf
        bool Check(int firsts); // check given number of firsts bottles of the shelf
        std::list<Ink>::iterator end(){return shelf.end();}
        void ClearTerminal();
		int CountCostLast6Brutal();
        int CountCostLast6List();
        int CountCostBeginingBrutal(int l);
        int CountCostBeginingBrutalSparing(int l);
        int CountCostMod4(int l);
        int CountCostMod4Recurent(int l);
		int CountCost(int mode);
        std::list<Ink>::iterator FindByNumber(int numb); // return Ink bottle by the number from the left
        std::list<int> GetTransfers(){return transfers;}
        std::string GetTransfersByString();
        int GetDistance(){return distance;}
#ifdef __WIN32__
        LARGE_INTEGER GetDuration(){return duration;}
#else
        std::chrono::steady_clock::duration GetDuration(){return duration;}
#endif
        int GetNumberOfShifts(){return numberOfShifts;}
        int GetPointer(){return pointer;}
        int GetStart(){return start = shelf.length() - 4;}
		bool GetTooSlow(){return too_slow;}
        int GetPermutationLevel(){return length() - start;}
        Shelf GetShelf(){return shelf;}
        std::string GetShelfOnBegining(){return shelfOnBegining;}
		int GetTeoreticalCost(){return teoretical_cost;}
        int length(){return shelf.length();}
        std::string LoadMovesFromFile(std::string fileName, std::string sShelf);
        int MovePointer(int newPosition, bool animated);
        void Modify(int i);
        void Move(std::list<int>, bool animated);
        int MoveBottleToPos(int actPos, int moved, bool animated);
        bool Move4InksBottles(int first, bool animated); // take 4 ink bottles in the row and update distance, pointer position and number of shifts
        char NextToSort(char &actualySorted);
        void Play();
        int PointerLeft();
        int PointerRight();
        void Print();
        void PrintForAnimation(int sted);
        void PrintForPlay();
        bool RandomlyComplicate();
        void SaveToFile(std::fstream f);
        std::list<int> ScaleTransfersFrom6(std::string transfersFor6);
#ifdef __WIN32__
        void SetDuration(LARGE_INTEGER d){duration = d;}
#else
        void SetDuration(std::chrono::steady_clock::duration d){duration = d;}
#endif
		void SetTooSlow(bool t){too_slow = t;}
        void SleepASecond(int);
        int Solve(int mode, bool animated);
        int Solve(char biggestInBegin, int mode, bool animated);
        int SolveBrutal(bool animated);
        int SolveBrtualBegining(int actPos, char notSorted, bool animated);
        int SolveBrtualBeginingSparing(char biggestInBegin, int j, char notSorted, bool animated);
        int SolveMod4(int actPos, int moved, char biggestInBegin, bool animated);
        int SolveLast6Brutal(bool animated);
        int SolveLast6Brutal(bool animated, int firsts);
        int SolveLast6List(bool animated);
        bool Sort(){shelf.Sort();};
        std::string ToString(){return shelf.ToString();}
        SolutionInkProblem &operator= ( SolutionInkProblem & );
        bool operator== ( std::string & );
        bool operator== ( SolutionInkProblem & );
        bool operator< ( SolutionInkProblem & );
        bool operator> ( SolutionInkProblem & );
        bool operator<= ( SolutionInkProblem & );
        bool operator>= ( SolutionInkProblem & );
        friend std::ostream & operator<< (std::ostream &out, SolutionInkProblem &isg);
        friend std::istream & operator>> (std::istream & in, SolutionInkProblem &isg);
};


#endif // SOLUTIONINKPROBLEM_HPP
