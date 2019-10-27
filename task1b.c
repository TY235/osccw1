#include <stdlib.h>
#include <stdio.h>
#include "coursework.h"
#include "linkedlist.h"

int main(){

	struct element *pHead = NULL;
	struct element *pTail = NULL;
	struct element *pPointer = NULL;
	struct timeval oStartTime;
	struct timeval oEndTime; 
	double avgResponseTime = 0;
	double avgTurnAroundTime = 0;
	int responseTime = 0;
	int turnAroundTime = 0;
	
    printf("PROCESS LIST:\n");
    for(int i = 0; i < NUMBER_OF_JOBS; i++){
		struct process * oTemp = generateProcess();
		addLast(oTemp,&pHead,&pTail);
        printf("         Process Id = %d, Initial Burst Time = %d, Remaining Burst Time = %d\n",((struct process*)(pTail->pData))->iProcessId,((struct process*)(pTail->pData))->iInitialBurstTime,((struct process*)(pTail->pData))->iRemainingBurstTime);
	}
    printf("PROCESS LIST:\n\n");

    pPointer = pHead;

    for(int j = 0; j < NUMBER_OF_JOBS; j++){
        runPreemptiveJob((struct process*)pPointer->pData, &oStartTime, &oEndTime);	
        responseTime = getDifferenceInMilliSeconds(((struct process*)(pPointer->pData))->oTimeCreated,oStartTime);
        printf("Process Id = %d, Previous Burst Time = %d, Remaining Burst Time = %d, Response Time = %d\n",((struct process*)(pPointer->pData))->iProcessId,((struct process*)(pPointer->pData))->iInitialBurstTime,((struct process*)(pPointer->pData))->iRemainingBurstTime,responseTime);
        pPointer = pPointer->pNext;
    }
    
    pPointer = pHead;

    while(((struct process*)(pTail->pData))->iRemainingBurstTime != 0){
        runPreemptiveJob((struct process*)pPointer->pData, &oStartTime, &oEndTime);
        printf("Process Id = %d, Previous Burst Time = %d, Remaining Burst Time = %d\n",((struct process*)(pPointer->pData))->iProcessId,((struct process*)(pPointer->pData))->iInitialBurstTime,((struct process*)(pPointer->pData))->iRemainingBurstTime);
        pPointer = pPointer->pNext;
    }
    //     turnAroundTime = getDifferenceInMilliSeconds(((struct process*)(pPointer->pData))->oTimeCreated,oEndTime);
    //     if(turnAroundTime)
	// avgResponseTime += responseTime;
	// avgTurnAroundTime += turnAroundTime; 


}