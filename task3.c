#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include "coursework.h"
#include "linkedlist.h"

sem_t delayConsumer;				//used to delay consumer
sem_t sync;							
sem_t counter;

int stars = 0;
int temp = 0;
int produced = 0;

struct element *pHead = NULL;
struct element *pTail = NULL;
struct element * pPointer = NULL;
struct process * oTemp = NULL;
int consumed = 0;

int printStars(int stars, int type) {

 	if(type == 1)
 		printf("Consumer 1, ");
 	else
 		printf("Producer 1, ");

 	printf("Produced = %d, Consumed = %d: ", produced, consumed);
	for(int i = 0; i < stars; i++)
 		printf("*");
	printf("%d\n",produced-consumed);
 }



void * consumer() {
	int g;
	for(int w = 0; w < 1000; w++)
	{   
        sem_wait(&counter); // 6. 1 -> 0 
		sem_wait(&sync); // 7. start 1 -> 0
        pPointer = pHead; 
        free(pPointer->pData);
		pPointer = pPointer->pNext;
		removeFirst(&pHead,&pTail);
		stars--; 
		consumed++;
		
		sem_getvalue(&counter,&g); // 8. get counter 0 
		printStars(stars,1);

		if(g == 48){
			sem_post(&delayConsumer);
		}
		sem_post(&sync);    // 9. end 0 -> 1
	}

}

void * producer() {
    int f;
	for(int z = 0; z < 1000; z++)
	{   
        sem_getvalue(&counter,&f); // 1. get value 0
		printf("%d ",f);
        if(f == MAX_BUFFER_SIZE - 1){
            sem_wait(&delayConsumer); // 0 -> -1
        }

		sem_wait(&sync); // 2. start 1 -> 0
        oTemp = generateProcess();
		addLast(oTemp,&pHead,&pTail);
		stars++;
		produced++;

		printStars(stars,2); 
        sem_post(&counter); // 4. increment counter 0 -> 1 2 345 49
		sem_post(&sync); // 5. End 0 -> 1 
	}		
	
}

int main(int argc, char** argv) {

    sem_init(&delayConsumer, 0, 0);		//initializes delayConsumer semaphore used to delay the consumer
	sem_init(&sync, 0, 1);
    sem_init(&counter,0,0);

	pthread_t prod, cons;

	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);

	pthread_join(prod,NULL);
	pthread_join(cons,NULL);
	

	int iSync, iConsumer, iCounter;

	sem_getvalue(&sync, &iSync);
	sem_getvalue(&delayConsumer, &iConsumer);
    sem_getvalue(&counter, &iCounter);

	printf("sSync = %d, sDelayConsumer = %d, sCounter = %d\n", iSync, iConsumer, iCounter);


	return 0;

}
