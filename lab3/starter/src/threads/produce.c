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

double g_time[2];
int produced;
int num_p;
int num;

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

	num = atoi(argv[1]);	/* number of items to produce */
	maxmsg = atoi(argv[2]); /* buffer size                */
	num_p = atoi(argv[3]);  /* number of producers        */
	num_c = atoi(argv[4]);  /* number of consumers        */
	num_total_t = num_p + num_c;

	pthread_t theads[num_total_t];

	for (int i = 0; i < num_total_t -num_c; i++){
		int* tmp = malloc(sizeof(int));
		*tmp = ij;
		pthread_create(&(threads[i], NULL, producer, tmp);
	
	}
	
	for (int j = num_c; j < num_total_t; j++ ){
		pthread_create(&(threads[j], NULL, producer, NULL);
	
	}

	gettimeofday(&tv, NULL);
	g_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.;


    gettimeofday(&tv, NULL);
    g_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

    printf("System execution time: %.6lf seconds\n", \
            g_time[1] - g_time[0]);
	exit(0);
}

void* consumer(){

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
