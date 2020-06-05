#include "Tests.hpp"
#include "Ink.hpp"
#include "Shelf.hpp"
#include "SolutionInkProblem.hpp"
#include "PresentSolutionInkProblem.hpp"

using namespace std;

bool Tests::testAll()
{
    if(!InkTest())
        return false;
    if(!ShelfTest())
        return false;
    if(!SolutionInkProblemTest())
        return false;
    if(!PresentSolutionInkProblemTest())
        return false;

    cout << "All OK." << endl;
    return true;
}

bool Tests::InkTest()
{
    try
    {
        Ink inkC('C'), inkM('M'), inkY('Y'), inkK('K'), inkC2('C'), inkM2('M'), inkY2('Y'), inkK2('K');

        if(inkC.GetInkType() != 'C')
            throw PreperExceptionData("Ink","GetInkType","Bad returned value!");
        if(inkM.GetInkType() != 'M')
            throw PreperExceptionData("Ink","GetInkType","Bad returned value!");
        if(inkY.GetInkType() != 'Y')
            throw PreperExceptionData("Ink","GetInkType","Bad returned value!");
        if(inkK.GetInkType() != 'K')
            throw PreperExceptionData("Ink","GetInkType","Bad returned value!");

        if(inkC.GetNumbValue() != 0)
            throw PreperExceptionData("Ink","GetNumbValue","Bad returned value!");
        if(inkM.GetNumbValue() != 1)
            throw PreperExceptionData("Ink","GetNumbValue","Bad returned value!");
        if(inkY.GetNumbValue() != 2)
            throw PreperExceptionData("Ink","GetNumbValue","Bad returned value!");
        if(inkK.GetNumbValue() != 3)
            throw PreperExceptionData("Ink","GetNumbValue","Bad returned value!");

        if(inkC < inkM || inkC < inkY || inkC < inkK || inkM < inkY || inkM < inkK || inkY < inkK)
            throw PreperExceptionData("Ink","operator<","Bad returned value!");
        if(inkK > inkY || inkK > inkM || inkK > inkC || inkY > inkM || inkY > inkC || inkM > inkC)
            throw PreperExceptionData("Ink","operator>","Bad returned value!");
        if(inkC <= inkM || inkC <= inkY || inkC <= inkK || inkM <= inkY || inkM <= inkK || inkY <= inkK)
            throw PreperExceptionData("Ink","operator<=","Bad returned value!");
        if(inkK >= inkY || inkK >= inkM || inkK >= inkC || inkY >= inkM || inkY >= inkC || inkM >= inkC)
            throw PreperExceptionData("Ink","operator>=","Bad returned value!");
        if(!(inkC == inkC2) || !(inkM == inkM2) || !(inkY == inkY2) || !(inkK == inkK2))
            throw PreperExceptionData("Ink","operator==","Bad returned value!");
        if(inkC == inkM || inkC == inkY || inkC == inkK || inkM == inkY || inkM == inkK || inkY == inkK)
            throw PreperExceptionData("Ink","operator==","Bad returned value!");
        if(!(inkC == 'C') || !(inkM == 'M') || !(inkY == 'Y') || !(inkK == 'K'))
            throw PreperExceptionData("Ink","operator==","Bad returned value!");
        if(inkC == 'M' || inkC == 'Y' || inkC == 'K' || inkM == 'Y' || inkM == 'K' || inkY == 'K')
            throw PreperExceptionData("Ink","operator==","Bad returned value!");
        if(inkC != inkC2 || inkM != inkM2 || inkY != inkY2 || inkK != inkK2)
            throw PreperExceptionData("Ink","operator!=","Bad returned value!");
    }
    catch(exceptionData exc)
    {
        cout << exc << endl;
        return false;
    }

    return true;
}

bool Tests::ShelfTest()
{
    try
    {
        Shelf s1(6), s2(9), s3("CCCCCC"), s4("CYKMCYKMY");
        if(s1.empty())
            throw PreperExceptionData("Shelf","Shelf(int)","Shelf was not build!");
        if(s3.empty())
            throw PreperExceptionData("Shelf","Shelf(std::string)","Shelf was not build!");

        if(!(s1.length() == 6))
            throw PreperExceptionData("Shelf","length()","Bad returned value!");
        if(!(s2.length() == s4.length()))
            throw PreperExceptionData("Shelf","length()","Bad returned value!");

        s1.clear();
        if(!s1.empty())
            throw PreperExceptionData("Shelf","clear()","Shelf was not cleared!");

        s1.BuildShelf(6);
        s3.BuildShelf("CCMYYK");
        if(s1.empty())
            throw PreperExceptionData("Shelf","BuildShelf(int)","Shelf was not build!");
        if(s3.empty())
            throw PreperExceptionData("Shelf","BuildShelf(std::string)","Shelf was not build!");
        if(s1.length() != 6)
            throw PreperExceptionData("Shelf","BuildShelf(int)","Shelf was not build properly!");
        if(s3.length() != 6)
            throw PreperExceptionData("Shelf","BuildShelf(std::string)","Shelf was not build properly!");

        if(!s3.Check())
            throw PreperExceptionData("Shelf","Check","Checked not properly!");
        if(s4.Check())
            throw PreperExceptionData("Shelf","Check","Checked not properly!");

        s4.Move4InksBottles(0);
        if(!(s4 == "CYKMYCYKM"))
            throw PreperExceptionData("Shelf","Move4InksBottles","Bottles ware moved not properly!");
        s4.Move4InksBottles(1);
        if(!(s4 == "CCYKMYKMY"))
            throw PreperExceptionData("Shelf","Move4InksBottles","Bottles ware moved not properly!");
        s4.Move4InksBottles(2);
        if(!(s4 == "CCKMYYKMY"))
            throw PreperExceptionData("Shelf","Move4InksBottles","Bottles ware moved not properly!");
        s4.Move4InksBottles(3);
        if(!(s4 == "CCKMYMYYK"))
            throw PreperExceptionData("Shelf","Move4InksBottles","Bottles ware moved not properly!");
        s4.Move4InksBottles(4);
        if(!(s4 == "CCKMKYMYY"))
            throw PreperExceptionData("Shelf","Move4InksBottles","Bottles ware moved not properly!");
        s4.Move4InksBottles(5);
        if(!(s4 == "CCKMKYMYY"))
            throw PreperExceptionData("Shelf","Move4InksBottles","Bottles ware moved not properly!");
        s4.Move4InksBottles(6);
        if(!(s4 == "CCKMKYMYY"))
            throw PreperExceptionData("Shelf","Move4InksBottles","Bottles ware moved not properly!");
        s4.Move4InksBottles(7);
        if(!(s4 == "CCKMKYMYY"))
            throw PreperExceptionData("Shelf","Move4InksBottles","Bottles ware moved not properly!");
        s4.Move4InksBottles(8);
        if(!(s4 == "CCKMKYMYY"))
            throw PreperExceptionData("Shelf","Move4InksBottles","Bottles ware moved not properly!");

        if(!(s4.Sort() == "CCMMYYYKK"))
            throw PreperExceptionData("Shelf","Sort","Bottles ware sorted not properly!");
        if(!(s3.Sort() == "CCMYYK"))
            throw PreperExceptionData("Shelf","Sort","Bottles ware sorted not properly!");

        if(!(s4.ToString() == "CCKMKYMYY"))
            throw PreperExceptionData("Shelf","ToString","The Shelf was converted not properly!");

        s1 = "CKYMMY";
        if(!(s1 == "CKYMMY"))
            throw PreperExceptionData("Shelf","operator=(std::string)","Bad value returned!");

        if(s1 == s3)
            throw PreperExceptionData("Shelf","operator==","Compared not properly!");
        if(s1 > s3)
            throw PreperExceptionData("Shelf","operator>","Compared not properly!");
        if(s1 >= s3)
            throw PreperExceptionData("Shelf","operator>=","Compared not properly!");
        if(s3 < s1)
            throw PreperExceptionData("Shelf","operator<","Compared not properly!");
        if(s3 <= s1)
            throw PreperExceptionData("Shelf","operator<=","Compared not properly!");

        s1 = s3;
        if(!(s1 == s3))
            throw PreperExceptionData("Shelf","operator==","Compared not properly!");
        if(!(s1 >= s3))
            throw PreperExceptionData("Shelf","operator>=","Compared not properly!");
        if(!(s3 <= s1))
            throw PreperExceptionData("Shelf","operator<=","Compared not properly!");

    }
    catch(exceptionData exc)
    {
        cout << exc << endl;
        return false;
    }

    return true;
}

bool Tests::SolutionInkProblemTest()
{
    try
    {
        SolutionInkProblem sip1(6), sip2(8), sip3("KYMCYK"), sip4("MKYMCYCK");

        if(sip1.GetDistance() != 0)
            throw PreperExceptionData("SolutionInkProblem","SolutionInkProblem(int)","Object wa not constructed properly!");
        if(!sip1.GetTransfersByString().empty())
            throw PreperExceptionData("SolutionInkProblem","SolutionInkProblem(int)","Object wa not constructed properly!");
        if(sip1.GetStart() != 2)
            throw PreperExceptionData("SolutionInkProblem","SolutionInkProblem(int)","Object wa not constructed properly!");
        if(sip1.GetPointer() != sip1.GetStart())
            throw PreperExceptionData("SolutionInkProblem","SolutionInkProblem(int)","Object wa not constructed properly!");
        if(sip1.GetShelf().length() != 6)
            throw PreperExceptionData("SolutionInkProblem","SolutionInkProblem(int)","Object wa not constructed properly!");

        if(sip3.GetDistance() != 0)
            throw PreperExceptionData("SolutionInkProblem","SolutionInkProblem(std::string)","Object wa not constructed properly!");
        if(!sip3.GetTransfersByString().empty())
            throw PreperExceptionData("SolutionInkProblem","SolutionInkProblem(std::string)","Object wa not constructed properly!");
        if(sip3.GetStart() != 2)
            throw PreperExceptionData("SolutionInkProblem","SolutionInkProblem(std::string)","Object wa not constructed properly!");
        if(sip3.GetPointer() != sip3.GetStart())
            throw PreperExceptionData("SolutionInkProblem","SolutionInkProblem(std::string)","Object wa not constructed properly!");
        if(sip3.GetShelf().length() != 6)
            throw PreperExceptionData("SolutionInkProblem","SolutionInkProblem(std::string)","Object wa not constructed properly!");
        if(!(sip3.GetShelf() == "KYMCYK"))
            throw PreperExceptionData("SolutionInkProblem","SolutionInkProblem(std::string)","Object wa not constructed properly!");

        SIPTMove4InksBottles(&sip4,0,"CYCKMKYM",16,"0");
        SIPTMove4InksBottles(&sip4,1,"CKYMYCKM",30,"01");
        SIPTMove4InksBottles(&sip4,2,"CKKMYMYC",42,"012");
        SIPTMove4InksBottles(&sip4,3,"CKKCMYMY",52,"0123");
        SIPTMove4InksBottles(&sip4,4,"CKKCMYMY",52,"0123");
        SIPTMove4InksBottles(&sip4,5,"CKKCMYMY",52,"0123");
        SIPTMove4InksBottles(&sip4,6,"CKKCMYMY",52,"0123");
        SIPTMove4InksBottles(&sip4,7,"CKKCMYMY",52,"0123");
        SIPTMove4InksBottles(&sip4,8,"CKKCMYMY",52,"0123");

        SIPTMove(&sip4,"0","MYMYCKKC",68,"01230");
        SIPTMove(&sip4,"1","MKKCYMYC",82,"012301");
        SIPTMove(&sip4,"2","MKYCKCYM",94,"0123012");
        SIPTMove(&sip4,"3","MKYMCKCY",104,"01230123");
        SIPTMove(&sip4,"4","MKYMCKCY",104,"01230123");
        SIPTMove(&sip4,"01","CKYMKCYM",134,"0123012301");
        SIPTMove(&sip4,"10","KYMKCCYM",164,"012301230110");
        SIPTMove(&sip4,"102","YMYMKCKC",206,"012301230110102");

        SIPTMoveBottleToPos(&sip2);

        //if(!(sip4.ScaleTransfersFrom6("012345") == "234567"))
            //throw PreperExceptionData("SolutionInkProblem","ScaleTransfersFrom6","Transfer was not scaled properly!");
        //if(!(sip4.ScaleTransfersFrom6("01234") == "23456"))
            //throw PreperExceptionData("SolutionInkProblem","ScaleTransfersFrom6","Transfer was not scaled properly!");

        sip2 = sip4;
        if(!sip4.Solve(1,false))
	    throw PreperExceptionData("SolutionInkProblem","Solve","Can not solve!");

        if(!(sip4.ToString() == sip2.GetShelf().Sort()))
        {
            string className = "SolutionInkProblem";
            string functionName = "Solve";
            string message = "Bottles were transported not properly!\nresult:\t\t";
            message += sip4.ToString();
            message +=  "\nexpected:\t";
            message += sip2.GetShelf().Sort();
            throw PreperExceptionData(className,functionName,message);
            throw PreperExceptionData(className,functionName,message);
        }
    }
    catch(exceptionData exc)
    {
        cout << exc << endl;
        return false;
    }

    return true;
}

void Tests::SIPTMove(SolutionInkProblem* sip,string transfers,string shelfResult,int distanceResult,string transfersResult)
{
    string className = "SolutionInkProblem";
    string functionName = "Move";
    list<int> transfersList;

    for(int i = 0; i < transfers.length(); i++)
        transfersList.push_back(transfers[i] - 48);

    sip->Move(transfersList,false);
    if(!(sip->GetShelf() == shelfResult))
    {
        string message = "Bottles were transported not properly!\nresult:\t\t";
        message += sip->GetShelf().ToString();
        message +=  "\nexpected:\t";
        message += shelfResult;
        throw PreperExceptionData(className,functionName,message);
    }
    if(!(sip->GetPointer() == sip->GetStart()))
    {
        string message = "Pointer in wrong place!\nresult:\t\t";
        message += to_string(sip->GetPointer());
        message +=  "\nexpected:\t";
        message += to_string(sip->GetStart());
        throw PreperExceptionData(className,functionName,message);
    }
    if(!(sip->GetDistance() == distanceResult))
    {
        string message = "Not correct distance!\nresult:\t\t";
        message += to_string(sip->GetDistance());
        message +=  "\nexpected:\t";
        message += to_string(distanceResult);
        throw PreperExceptionData(className,functionName,message);
    }
    if(!(sip->GetTransfersByString() == transfersResult))
    {
        string message = "Not correct Transfers!!\nresult:\t\t";
        message += sip->GetTransfersByString();
        message +=  "\nexpected:\t";
        message += transfersResult;
        throw PreperExceptionData(className,functionName,message);
    }
}

void Tests::SIPTMove4InksBottles(SolutionInkProblem* sip,int transfer,string shelfResult,int distanceResult,string transfersResult)
{
    string className = "SolutionInkProblem";
    string functionName = "Move";

    sip->Move4InksBottles(transfer,false);
    if(!(sip->GetShelf() == shelfResult))
    {
        string message = "Bottles were transported not properly!\nresult:\t\t";
        message += sip->GetShelf().ToString();
        message +=  "\nexpected:\t";
        message += shelfResult;
        throw PreperExceptionData(className,functionName,message);
    }
    if(!(sip->GetPointer() == sip->GetStart()))
    {
        string message = "Pointer in wrong place!\nresult:\t\t";
        message += to_string(sip->GetPointer());
        message +=  "\nexpected:\t";
        message += to_string(sip->GetStart());
        throw PreperExceptionData(className,functionName,message);
    }
    if(!(sip->GetDistance() == distanceResult))
    {
        string message = "Not correct distance!\nresult:\t\t";
        message += to_string(sip->GetDistance());
        message +=  "\nexpected:\t";
        message += to_string(distanceResult);
        throw PreperExceptionData(className,functionName,message);
    }
    if(!(sip->GetTransfersByString() == transfersResult))
    {
        string message = "Not correct Transfers!!\nresult:\t\t";
        message += sip->GetTransfersByString();
        message +=  "\nexpected:\t";
        message += transfersResult;
        throw PreperExceptionData(className,functionName,message);
    }
}

void Tests::SIPTMoveBottleToPos(SolutionInkProblem* sip,int actPos,int bottleToBeMoved)
{
    string className = "SolutionInkProblem";
    string functionName = "MoveBottleToPos";

    char inkToBeMoved = sip->ToString()[bottleToBeMoved];
    string result = sip->ToString();

    for(int i = 0; i< sip->length(); i++)
    {
        if(i == actPos)
            result[i] = inkToBeMoved;
        else if(i > actPos)
            result[i] = '#';
    }

    if(sip->MoveBottleToPos(actPos,bottleToBeMoved,false) == -1)
        return;

    for(int i = 0; i <= actPos; i++)
        if(!(sip->ToString()[i] == result[i]))
        {
            string message = "Bottles were transported not properly!\nactual position:\t";
            message += to_string(actPos);
            message +=  "\tbottle to be moved:\t";
            message += to_string(bottleToBeMoved);
            message +=  "\nresult:\t\t";
            message += sip->ToString();
            message +=  "\nexpected:\t";
            message += result;
            throw PreperExceptionData(className,functionName,message);
        }

}

void Tests::SIPTMoveBottleToPos(SolutionInkProblem* sip)
{
    for(int i = -1; i <= sip->length(); i++)
        for(int j = -1; j <= sip->length(); j++)
            SIPTMoveBottleToPos(sip,i,j);
}

bool Tests::PresentSolutionInkProblemTest()
{
    try
    {
        PresentSolutionInkProblem psip("every7.txt");

        psip.Solve(1,false);


    }
    catch(exceptionData exc)
    {
        cout << exc << endl;
        return false;
    }

    return true;
}

ostream & operator<< (ostream &out, const exceptionData &exc)
{
    return out << "Error in " << exc.thrownClass << "::" << exc.thrownFunction << ": " << exc.thrownStatement;
}

exceptionData PreperExceptionData(string className, string functionName, string statement)
{
    exceptionData exc;
    exc.thrownClass = className;
    exc.thrownFunction = functionName;
    exc.thrownStatement = statement;
    return exc;
}
