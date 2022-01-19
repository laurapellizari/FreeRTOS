#include <stdio.h>

#define BUFFERSIZE 10

int start = 0;
int end = 0;
int aux = 0;
 
typedef void (*pf)(void);

typedef struct {
	char *ProcessName;
	int Time;
	pf Pointer;
} process;

process buff[BUFFERSIZE];

void AddProc(char *nProcessName, int nTime, pf nPointer){
	if (((end+1)%BUFFERSIZE != start)){
		buff[end].ProcessName = nProcessName;
		buff[end].Time = nTime;
		buff[end].Pointer = nPointer;
		end = (end+1)%BUFFERSIZE;
	}
}

void RemoveProc(){
	//Check if it is not the beginning
	if (end != start){
		start = (start+1)%BUFFERSIZE;
	}
}

void ExeProc() {
	if (start != end){
		buff[start].Pointer();
	}
}

void func1(){printf("Function 1\n");}

void func2(){printf("Function 2\n");}

void func3(){printf("Function 3\n");}

void main() {

	AddProc("name1", 1, func1);
	AddProc("name2", 2, func2);
	AddProc("name3", 3, func3);
	ExeProc();
	RemoveProc();
	ExeProc();
	RemoveProc();
	ExeProc();
	RemoveProc();
	
}
