#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUMBER_OF_JOBS 1000


sem_t delayConsumer; //  A binary semaphore to make sure consumer goes to sleep				
sem_t sync; // A binary semaphore to synchronize across the semaphores

int stars = 0;
int temp = 0;

int produced = 0;
int consumed = 0;


// Visualise function
int printStars(int stars, int type) {

 	if(type == 1){
 		printf("Consumer, ");
	}
	else{
 		printf("Producer, ");
	}

 	printf("Produced = %d, Consumed = %d: ", produced, consumed);
	
	for(int i = 0; i < stars; i++){
 		printf("*");
	}

 	printf("\n");

}

// Consumer function
void * consumer() {

	sem_wait(&delayConsumer);
	
	for (int w = 0; w < NUMBER_OF_JOBS; w++){
		
		sem_wait(&sync);
		stars--; 
		consumed++;
		temp = stars;
		printStars(stars,1);
		sem_post(&sync);
	
		if (temp == 0){
			sem_wait(&delayConsumer);
		}
	}
}

// Producer function
void * producer() {

	for(int z=0; z < NUMBER_OF_JOBS; z++){

		sem_wait(&sync);
		stars++;
		produced++;
		printStars(stars,2);
		
		if(stars==1){
			sem_post(&delayConsumer);
		}
		sem_post(&sync);
	}		
	sem_post(&delayConsumer);
}

int main(int argc, char** argv) {

	sem_init(&delayConsumer, 0, 0); // Initializes delayConsumer semaphore to 0
	sem_init(&sync, 0, 1); // Initializes sync semaphore to 1

	pthread_t prod, cons;

	// Create thread
	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);

	// Join thread
	pthread_join(prod,NULL);
	pthread_join(cons,NULL);

	// Declare variables to store semaphores values
	int isync, dconsumer;

	// Get the semaphores values
	sem_getvalue(&sync, &isync);
	sem_getvalue(&delayConsumer, &dconsumer);

	// Print out the final semaphores value
	printf("sync = %d, delayConsumer = %d\n", isync, dconsumer);

	return 0;

}
