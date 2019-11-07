#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUMBER_OF_JOBS 1000


sem_t delayConsumer;				//used to delay consumer
sem_t sync;							

int stars = 0;
int temp = 0;
int z, w;

int produced = 0;
int consumed = 0;

 int printStars(int stars, int type) {

 	if(type == 1)
 		printf("Consumer, ");
 	else
 		printf("Producer, ");

 	printf("Produced = %d, Consumed = %d: ", produced, consumed);
	for(int i = 0; i < stars; i++)
 		printf("*");
	  
 	printf("\n");

 }

void * consumer() {
	sem_wait(&delayConsumer);
	
	for (w = 0; w < NUMBER_OF_JOBS; w++)
	{
		sem_wait(&sync);
		stars--; 
		consumed++;
		temp = stars;
		printStars(stars,1);
		sem_post(&sync);
		if (temp == 0)
			sem_wait(&delayConsumer);


	}

}


void * producer() {

	for(z=0; z<NUMBER_OF_JOBS; z++)
	{
		sem_wait(&sync);
		stars++;
		produced++;
		printStars(stars,2);
		
		if(stars==1)
			sem_post(&delayConsumer);
			sem_post(&sync);
	}		
	sem_post(&delayConsumer);
}



int main(int argc, char** argv) {

	sem_init(&delayConsumer, 0, 0);		//initializes delayConsumer semaphore used to delay the consumer
	sem_init(&sync, 0, 1);

	pthread_t prod, cons;

	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);

	pthread_join(prod,NULL);
	pthread_join(cons,NULL);
	

	int isync, dconsumer;

	sem_getvalue(&sync, &isync);
	sem_getvalue(&delayConsumer, &dconsumer);

	printf("sSync=%d, sDelayConsumer=%d\n", isync, dconsumer);


	return 0;
}


