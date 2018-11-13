// Use this to see if a number has an integer snuare root
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

struct node {
	int*  value;
	struct single_node *next;
 };

struct single_list {
     struct node *head;
     struct node *tail;
     int size;
     sem_t sem;
 };

void single_list_init( buffer *list ) {
     list->head = NULL;
     list->tail = NULL;
     list->size = 0;
     sem_init(&(list->sem), 0, 1);
 };

struct single_list buffer;
double g_time[2];
int remaining;
int num_p;
int num;
sem_t spaces;
sem_t items;
pthread_mutex_t mutex;


void main(int argc, char *argv[])
{
	int maxmsg;
	int num_c;
	int i;
	struct timeval tv;
	

	if (argc != 5) {
		printf("Usage: %s <N> <B> <P> <C>\n", argv[0]);
		exit(1);
	}

	sem_init( &spaces, 0, maxmsg);
	sem_init( &items, 0, 0);
	single_list_init(buffer);

	pthread_mutex_init(&mutex, NULL);
	
	num = atoi(argv[1]);	/* number of items to produce */
	maxmsg = atoi(argv[2]); /* buffer size                */
	num_p = atoi(argv[3]);  /* number of producers        */
	num_c = atoi(argv[4]);  /* number of consumers        */
	num_total_t = num_p + num_c;
	remaining = num;

	pthread_t theads[num_total_t];

	for (int i = 0; i < num_total_t -num_c; i++){
		int* tmp = malloc(sizeof(int));
		*tmp = i;
		pthread_create(&(threads[i]), NULL, producer, tmp);
	
	}
	
	for (int j = num_c; j < num_total_t; j++ ){
		int* tmp_id = malloc(sizeof(int));
		*tmp_id = j-num_c;
		pthread_create(&(threads[j]), NULL, producer, tmp_id);
	
	}

	gettimeofday(&tv, NULL);
	g_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.;


    gettimeofday(&tv, NULL);
    g_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

    printf("System execution time: %.6lf seconds\n", \
            g_time[1] - g_time[0]);
	exit(0);
}
/*
void* consumer(void* arugument){
	int* id = (int*) argument;
	int num;
	int sqrt;
	
	while (1) {	
		// check if tasks are empty
			// if empty kill the thread
		pthread_mutex_lock( &mutex);
		if (remaining <= 0 and buffer.size <= 0 ){
			return 0;
		}
		pthread_mutex_unlock(&mutex);
		
		node *tmp = malloc(sizeof(node));
		// get stuff from the buffer	
		sem_wait(&items);
		sem_wait(&(buffer.sem));
		tmp = buffer.head;
		num = tmp->value;
		buffer.head = tmp->next;
		buffer.size --;
		free(tmp);
		sem_post(&(buffer.sem));
		sem_post(&spaces); // signal that an item has been removed 

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
			node* tmp_p = malloc(sizeof(node));
			//lock something
			sem_wait(&spaces);
			sem_wait(buffer.sem);

			tmp_p->next = NULL;
			tmp_p->value=i;

			buffer.tail->next=tmp_p;
			buffer.tail = tmp_p;
			buffer.size ++;
			
			pthread_mutex_lock( &mutex);			
			remaining --;
			pthread_mutex_unlock( &mutex);

			sem_post(&(buffer.sem));
			sem_post(&items);
			// add iterm to the buffer
			// unlock something
			
		}
	}
}

*/
