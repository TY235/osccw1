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
	struct process * oTemp;

	for(int i = 0; i < NUMBER_OF_JOBS; i++){
		oTemp = generateProcess();
		addLast(oTemp,&pHead,&pTail);
	}	
	
	pPointer = pHead;

	for(int j = 0; j < NUMBER_OF_JOBS; j++){
		runNonPreemptiveJob((struct process*)pPointer->pData, &oStartTime, &oEndTime);	
		responseTime = getDifferenceInMilliSeconds(((struct process*)(pPointer->pData))->oTimeCreated,oStartTime);
		turnAroundTime = getDifferenceInMilliSeconds(((struct process*)(pPointer->pData))->oTimeCreated,oEndTime);
		avgResponseTime += responseTime;
		avgTurnAroundTime += turnAroundTime; 
		printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %d, Turn Around Time = %d\n",((struct process*)(pPointer->pData))->iProcessId,((struct process*)(pPointer->pData))->iInitialBurstTime,((struct process*)(pPointer->pData))->iRemainingBurstTime,responseTime,turnAroundTime);
		pPointer = pPointer->pNext; 
	}
	printf("Average response time = %.6f\n",avgResponseTime/NUMBER_OF_JOBS);
	printf("Average turn around time = %.6f\n",avgTurnAroundTime/NUMBER_OF_JOBS);

	for(int k = 0; k < NUMBER_OF_JOBS; k++){
		removeFirst(&pHead,&pTail);

	}
}
