all: Sudoku.o givequestion.cpp solve.cpp transform.cpp
	g++ -o givequestion givequestion.cpp Sudoku.o
	g++ -o solve solve.cpp Sudoku.o
	g++ -o transform transform.cpp Sudoku.o
	
	
Sudoku.o:	Sudoku.cpp Sudoku.h
	g++ -c Sudoku.cpp 

clean:
	rm Sudoku*.o
