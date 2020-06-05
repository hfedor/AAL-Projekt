CXX = g++

all: clean 6result.txt Ink.o Shelf.o SolutionInkProblem.o PresentSolutionInkProblem.o Tests.o main.o
	$(CXX) Ink.o Shelf.o SolutionInkProblem.o PresentSolutionInkProblem.o Tests.o main.o -o test

Ink.o: Ink.cpp Ink.hpp
	$(CXX) Ink.cpp -c -o Ink.o

Shelf.o: Shelf.cpp Shelf.hpp Ink.hpp
	$(CXX) Shelf.cpp -c -o Shelf.o

SolutionInkProblem.o: SolutionInkProblem.cpp SolutionInkProblem.hpp Shelf.hpp 6result.txt
	$(CXX) SolutionInkProblem.cpp -c -o SolutionInkProblem.o

PresentSolutionInkProblem.o: PresentSolutionInkProblem.cpp PresentSolutionInkProblem.hpp SolutionInkProblem.hpp 
	$(CXX) PresentSolutionInkProblem.cpp -c -o PresentSolutionInkProblem.o

Tests.o: Tests.cpp Tests.hpp Ink.hpp Shelf.hpp SolutionInkProblem.hpp PresentSolutionInkProblem.hpp 6result.txt
	$(CXX) Tests.cpp -c -o Tests.o

main.o: main.cpp Ink.hpp Shelf.hpp SolutionInkProblem.hpp PresentSolutionInkProblem.hpp Tests.hpp 6result.txt
	$(CXX) main.cpp -c -o main.o

clean:
	rm -f *.o test
