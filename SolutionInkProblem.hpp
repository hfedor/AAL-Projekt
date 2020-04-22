#ifndef SOLUTIONINKPROBLEM_HPP
#define SOLUTIONINKPROBLEM_HPP

#include "Shelf.hpp"
#include <fstream>

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
    public:
        SolutionInkProblem(int inksNumb); // constructor with given number of ink bottles on the constructed shelf
        SolutionInkProblem(std::string new_shelf); // constructor with given ink bottles on the constructed shelf
        std::list<Ink>::iterator begin(){return shelf.begin();}
        bool Check(); // check the shelf
        std::list<Ink>::iterator end(){return shelf.end();}
        std::list<Ink>::iterator FindByNumber(int numb); // return Ink bottle by the number from the left
        int FindInkFrom(int actPos, char toFind); // find bottle with given ink type which could by moved by the arm of the machine to given position with minimizing the distance traveled
        std::list<int> GetTransfers(){return transfers;}
        std::string GetTransfersByString();
        int GetDistance(){return distance;}
        int GetNumberOfShifts(){return numberOfShifts;}
        int GetPointer(){return pointer;}
        int GetStart(){return start = shelf.length() - 4;}
        int GetPermutationLevel(){return length() - start;}
        Shelf GetShelf(){return shelf;}
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
        void SaveToFile(std::fstream f);
        std::list<int> ScaleTransfersFrom6(std::string transfersFor6);
        bool Solve(bool animated);
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