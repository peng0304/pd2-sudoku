#include "Sudoku.h"
#include <cstdio>
#include <iostream>
using namespace std;

void Sudoku::transform(){
	readIn();
	change();
	printOut(false);
}
void Sudoku::change(){
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
}
void Sudoku::printOut(bool isAns){
	int i;
	if(!isAns){
		for(i=0;i<sudokuSize;i++){
			printf("%d%c",map[i],(i+1)%9==0?'\n':' ');
		}
	}
	else
		for(i=0;i<sudokuSize;i++){
			printf("%d%c",ans[i],(i+1)%9==0?'\n':' ');
		}
}
void Sudoku::readIn(){
	for(int i=0;i<sudokuSize;i++){
		scanf("%d",&map[i]);
	}
}
void Sudoku::givequestion(){
	int q[sudokuSize]={
		9,0,6,0,1,3,0,0,8,
		0,5,8,0,0,0,0,9,0,
		0,3,0,0,0,0,0,1,0,
		0,6,0,8,0,0,9,2,0,
		0,0,3,4,0,9,1,0,0,
		0,4,9,0,0,6,0,3,0,
		0,9,0,0,0,0,0,8,0,
		0,1,0,0,0,0,6,7,0,
		4,0,0,9,6,0,3,0,1,
	};
	for(int i=0;i<sudokuSize;i++){
		printf("%d%c",q[i],(i+1)%9==0?'\n':' ');
	}
}

void Sudoku::changeNum(int a,int b){
	for(int i=0;i<sudokuSize;i++){
		if(map[i]==a)
			map[i]=b;
		else if(map[i]==b)
			map[i]=a;
	}
}
void Sudoku::changeRow(int a,int b){
	int reg;
	for(int i=0;i<27;i++){
		reg = map[a*27+i];
		map[a*27+i] = map[b*27+i];
		map[b*27+i] = reg;
	}
}
void Sudoku::changeCol(int a,int b){
	int reg;
	for(int i=0;i<81;i=i+9){
		for(int j=0;j<3;j++){
			reg = map[j+a*3+i];
			map[j+a*3+i] = map[j+b*3+i]; 
			map[b*3+j+i] = reg;
		}	
	}
}
void Sudoku::rotate(int n){
	int temp[81];
	if(n%4==0)
		return;
	if(n%4==1){
		for(int i=72,n=0;i<81,n<9;i++,n++){
			for(int j=0,g=0;j<81,g<9;j=j+9,g++){
					temp[n*9+g]=map[i-j];
			}
		}
	
	}
	//
	if(n%4==2){
		for(int i=0,j=80;i<81,j>=0;i++,j--){
			temp[i]=map[j];	
		}
	}
	if(n%4==3){
		for(int i=80,n=0;i>71,n<9;i--,n++){
			for(int j=0,g=8;j<9,g>=0;j++,g--){
				temp[n*9+j]=map[i-9*g];
			}
		}
	}
	for(int i=0;i<81;i++){
		map[i]=temp[i];
	}
}
void Sudoku::flip(int n){
	int temp[81];
	if(n==0){
		for(int i=0,m=72;i<9,m>=0;i++,m=m-9){
			for(int j=0;j<9;j++){
				temp[i*9+j]=map[m+j];
			}
		}
	}
	else{
		for(int i=0;i<9;i++){
			for(int j=0,m=8;j<9,m>=0;j++,m--){
				temp[i*9+j]=map[i*9+m];
			}
		}
	}
	for(int i=0;i<81;i++){
		map[i]=temp[i];
	}
}

bool Sudoku::checking(int arr[]){
	int c[9];
	for(int i=0;i<9;i++){
		c[i]=0;
	}
	for(int i=0;i<9;i++){
		if(arr[i]==0)continue;
		else{
			c[arr[i]-1]=c[arr[i]-1]+1;
		}
	}
	for(int i=0;i<9;i++){
		if(c[i]>1)
			return false;
	}
	return true;
}
bool Sudoku::isAns(){
	bool res;
	int check[9];
	int x;
	for(int i=0;i<81;i+=9){
		for(int j=0;j<9;j++){
			check[j]=map[i+j];	
		}
		res=checking(check);
		if(res==false) 
			return false;
	}
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			check[j]=map[i+j*9];
		}
		res=checking(check);
		if(res==false)
			return false;
	}
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			x=27*(i/3)+3*(i%3)+9*(j/3)+(j%3);
			check[j]=map[x];	
		}
		res=checking(check);
		if(res==false)
			return false;
	}
	return true;
}
void Sudoku::possible(int arr[]){
	int a=0;
	for(int i=0;i<9;i++){
		possibleN[i]=0;
	}
	for(int i=0;i<81;i++){
		if(map[i]==0){
			zeroind=i;
			break;
		}
	}
	int temp[9];
	for(int j=0;j<9;j++)
		temp[j]=0;
	int row=0,col=0,block=0;
	row=zeroind/9;
	col=zeroind-9*row;
	block=(row/3)*3+(col/3);
	for(int j=row*9;j<row*9+9;j++){
		if(arr[j]!=0)
			temp[arr[j]-1]=1;
	}
	for(int j=col;j<81;j+=9){
		if(arr[j]!=0)
			temp[arr[j]-1]=1;
	}
	for(int j=(block/3)*27+(col/3)*3;j<(block/3)*27+(col/3)*3+3;j++){
		for(int i=0;i<27;i+=9){
			if(arr[j+i]!=0)
				temp[arr[j+i]-1]=1;
		}
	}
	int counter=0;
	for(int j=0;j<9;j++){
		if(temp[j]==0){
			possibleN[counter]=j+1;
			counter++;
		}
	}
}
bool Sudoku::findzero(){
	for(int i=0;i<sudokuSize;i++){
		if(map[i]==0)
			return false;
	}
	return true;
}
int Sudoku::allzero(){
	int x=0;
	for(int i=0;i<81;i++){
		everyzero[i]=0;
	}
	for(int i=0;i<81;i++){
		if(map[i]==0){
			everyzero[x]=i;
			x++;
		}
	}
}
void Sudoku::backtrack(){
	if(isAns()!=true){
		map[everyzero[z]]=0;
		possible(map);
		return;
	}
	if(findzero()==true){
		for(int i=0;i<sudokuSize;i++){
			ans[i]=map[i];
		}
		answer+=1;
		if(answer==2){
			printf("2\n");
			exit(0);
		}
		map[everyzero[z]]=0;
		possible(map);
		return;
	}
	possible(map);
	z++;
	if(possibleN[0]==0){
			z--;
			map[everyzero[z]]=0;
			possible(map);
			return;
	}
	if(answer>=2){
		printf("2\n");
		exit(0);
	}
	for(int i=0;possibleN[i]>0;i++){
		map[everyzero[z]]=possibleN[i];
		backtrack();
	}
	z--;
	if(z<0){
		return;
	}
	map[everyzero[z]]=0;
	possible(map);
}
void Sudoku::solve(){
	if(isAns()==false){
		cout<<"0"<<endl;
		exit(0);
	}
	if(findzero()==true&&isAns()==true){
		cout<<"1"<<endl;
		printOut(false);
		exit(0);
	}
	allzero();
	answer=0;
	z=-1;
	backtrack();
	if(answer==0){
		cout<<"0"<<endl;
		exit(0);
	}
	if(answer==1){
		printf("1\n");
		printOut(true);
	}	
}























