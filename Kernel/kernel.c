#include "kernel.h"

#define POOL_SIZE 10

process * pool[POOL_SIZE];

int start, end;

char kernelInit(void){
	start = 0;
	end = 0;
	return SUCCESS;
}

char kernelAddProc(process * newProc){
	//checking for free space
	if ( ((end+1)%POOL_SIZE) != start){
		pool[end] = newProc;
		end = (end+1)%POOL_SIZE;
		return SUCCESS;
	}
	return FAIL;
}

void kernelLoop(void){
  for(;;){
    //Do we have any process to execute?
      if (start != end){
        for (int i = 0; i < 9; i++){
            pool[i].pr
        }
        //check if there is need to reschedule
        if (pool[start]->func() == REPEAT){
          kernelAddProc(pool[start]);
        }
        //prepare to get the next process; 
        start = (start+1)%POOL_SIZE;
      }
   }
}
