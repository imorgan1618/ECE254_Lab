// Use this to see if a number has an integer square root
#define EPS 1.E-7


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

double g_time[2];
int produced;
int num_p;
int num;
int *buffer;
sem_t empty_buffer;
sem_t num_available;


int main(int argc, char *argv[])
{
	int maxmsg;
	int num_c;
	int i;
	struct timeval tv;
	

	if (argc != 5) {
		printf("Usage: %s <N> <B> <P> <C>\n", argv[0]);
		exit(1);
	}

	sem_init( &empty_buffer, 0, maxmsg);
	sem_init( &num_available, 0, 0);

	num = atoi(argv[1]);	/* number of items to produce */
	maxmsg = atoi(argv[2]); /* buffer size                */
	num_p = atoi(argv[3]);  /* number of producers        */
	num_c = atoi(argv[4]);  /* number of consumers        */
	num_total_t = num_p + num_c;


	//create buffer or shared memory thing
	buffer = malloc(maxmsg * sizeof(int));
	for (int l= 0; l < maxmsg; l++){
		buffer[l] = -1;
	}

	pthread_t theads[num_total_t];

	for (int i = 0; i < num_total_t -num_c; i++){
		int* tmp = malloc(sizeof(int));
		*tmp = i;
		pthread_create(&(threads[i], NULL, producer, tmp);
	
	}
	
	for (int j = num_c; j < num_total_t; j++ ){
		int* tmp_id = malloc(sizeof(int));
		*tmp_id = j-num_c;
		pthread_create(&(threads[j], NULL, producer, tmp_id);
	
	}

	gettimeofday(&tv, NULL);
	g_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.;


    gettimeofday(&tv, NULL);
    g_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

    printf("System execution time: %.6lf seconds\n", \
            g_time[1] - g_time[0]);
	exit(0);
}

void* consumer(void* arugument){
	int* id = (int*) argument;
	int num;
	int sqrt;
	
	while (1) {	
		// check if tasks are empty
			// if empty kill the thread
		
		// get stuff from the buffer	
		sem_wait(&num_availble);

		// free the buffer
		sem_post(&empty_buffer);
		

		for (int = 0; i < (num/2); i++){
			if ( (i*i) == num ) {
				printf("%d %d %d\n", *id, num, sqrt);
			}
		}
		
	}

}

void* producer(void* argument){
	int* id = (int*) argument;
	
	for (i=0; i < num; i++){
		//check if the buffer is full
		if ((i%num_p) == *id){
			//lock something
			// add iterm to the buffer
			// unlock something
			
		}
	}
}


