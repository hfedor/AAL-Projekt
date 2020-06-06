CXX = g++

all: Ink.o Shelf.o SolutionInkProblem.o table_printer.o PresentSolutionInkProblem.o Tests.o main.o
	$(CXX) Ink.o Shelf.o SolutionInkProblem.o table_printer.o PresentSolutionInkProblem.o Tests.o main.o -o solveInkProblem

Ink.o: Ink.cpp Ink.hpp
	$(CXX) Ink.cpp -c -o Ink.o

Shelf.o: Shelf.cpp Shelf.hpp Ink.hpp
	$(CXX) Shelf.cpp -c -o Shelf.o

SolutionInkProblem.o: SolutionInkProblem.cpp SolutionInkProblem.hpp Shelf.hpp
	$(CXX) SolutionInkProblem.cpp -c -o SolutionInkProblem.o

table_printer.o: table_printer.cpp table_printer.h table_printer.tpp.h
	$(CXX) table_printer.cpp -c -o table_printer.o 

PresentSolutionInkProblem.o: PresentSolutionInkProblem.cpp PresentSolutionInkProblem.hpp SolutionInkProblem.hpp table_printer.h table_printer.tpp.h
		$(CXX) PresentSolutionInkProblem.cpp -c -o PresentSolutionInkProblem.o

Tests.o: Tests.cpp Tests.hpp Ink.hpp Shelf.hpp SolutionInkProblem.hpp PresentSolutionInkProblem.hpp
	$(CXX) Tests.cpp -c -o Tests.o

main.o: main.cpp Ink.hpp Shelf.hpp SolutionInkProblem.hpp PresentSolutionInkProblem.hpp Tests.hpp
	$(CXX) main.cpp -c -o main.o

clean:
	rm -f *.o test
