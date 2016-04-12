#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;
class Sudoku{
	public:
		void solve();
		void givequestion();
		void readIn();
		void change();
		void rotate(int n);
		void changeNum(int a,int b);
		void changeRow(int a,int b);
		void changeCol(int a,int b);
		void flip(int n);
		void transform();
		void printOut(bool isAns);
		bool isAns();
		bool findzero();
		void possible(int arr[]);
		void backtrack();
		int allzero();
		static const int sudokuSize=81;
	private:
		int map[sudokuSize];
		int ans[sudokuSize];
		int zeroind;
		bool checking(int arr[]);
		int q[81];
		int everyzero[81];
		int answer;
		int current;
		int used[9];
		int possibleN[9];
		int z;
};
