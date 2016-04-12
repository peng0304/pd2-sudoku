all: sudoku.o givequestion.cpp solve.cpp transform.cpp
	g++ -o givequestion givequestion.cpp sudoku.o
	g++ -o solve solve.cpp sudoku.o
	g++ -o transform transform.cpp sudoku.o
	
	
sudoku.o:	sudoku.cpp Sudoku.h
	g++ -c sudoku.cpp 

clean:
	rm sudoku*.o
