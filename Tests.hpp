#ifndef TESTS_HPP
#define TESTS_HPP

#include"SolutionInkProblem.hpp"
#include <iostream>

class Tests
{
    public:
        bool testAll();
        bool InkTest();
        bool ShelfTest();
        bool SolutionInkProblemTest();
        void SIPTMove(SolutionInkProblem* sip,std::string transfers,std::string shelfResult,int distanceResult, std::string transfersResult);
        void SIPTMove4InksBottles(SolutionInkProblem* sip,int transfer,std::string shelfResult,int distanceResult, std::string transfersResult);
        void SIPTMoveBottleToPos(SolutionInkProblem* sip,int actPos,int bottleToBeMoved);
};

struct exceptionData
{
    std::string thrownClass;
    std::string thrownFunction;
    std::string thrownStatement;
};

std::ostream & operator<< (std::ostream &out, const exceptionData &exc);

exceptionData PreperExceptionData(std::string className, std::string functionName, std::string statement);

#endif // TESTS_HPP
