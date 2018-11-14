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
	int  value;
	struct node *next;
 };

struct single_list {
     struct node *head;
     struct node *tail;
     int size;
     pthread_mutex_t sem;
 };

void single_list_init( struct single_list list ) {
     list.head = NULL;
     list.tail = NULL;
     list.size = 0;
     pthread_mutex_init(&(list.sem), NULL);
 };

void* producer(void*);
void* consumer(void*);
void printer(int, int);
int remove_from_buffer(struct node *);
void insert(struct node *, int); 
struct single_list buffer;
double g_time[2];
int remaining;
int num_p;
int num;
sem_t spaces;
sem_t items;
pthread_mutex_t mutex;


int main(int argc, char *argv[])
{
	int maxmsg;
	int num_c;
	struct timeval tv;	

	if (argc != 5) {
		printf("Usage: %s <N> <B> <P> <C>\n", argv[0]);
		exit(1);
	}

	num = atoi(argv[1]);	/* number of items to produce */
	maxmsg = atoi(argv[2]); /* buffer size                */
	num_p = atoi(argv[3]);  /* number of producers        */
	num_c = atoi(argv[4]);  /* number of consumers        */
	remaining = num; 

	sem_init( &spaces, 0, maxmsg);
	sem_init( &items, 0, 0);
	single_list_init(buffer);

	pthread_mutex_init(&mutex, NULL);
	
	pthread_t producer_threads[num_p];
    pthread_t consumer_threads[num_c];

	gettimeofday(&tv, NULL);
	g_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.;
	for (int i = 0; i < num_p ; i++){
		int* id = malloc(sizeof(int));
		*id = i;
		pthread_create(&producer_threads[i], NULL, producer, id);
    }
	
	for (int j = 0; j < num_c; j++ ){
		int* tmp_id = malloc(sizeof(int));
		*tmp_id = j;
		pthread_create(&consumer_threads[j], NULL, consumer, tmp_id);
	}
	
	for( int k = 0; k < num_p; k ++){
		pthread_join(producer_threads[k], NULL);
	}
    
    for ( int m = 0; m < num_c; m ++){
        insert(malloc(sizeof(struct node)), -1);
    }
        
	for ( int l = 0; l < num_c; l ++){
		pthread_join(consumer_threads[l], NULL);
	}


	gettimeofday(&tv, NULL);
    g_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

    printf("System execution time: %.6lf seconds\n", \
        	g_time[1] - g_time[0]);
	sem_destroy( &spaces );
	sem_destroy( &items );
	pthread_mutex_destroy( &mutex );

	exit(0);
}

void* consumer(void* argument){
	int* id = (int*) argument;
	int consumed_val = -1;
	//printf("consumer id: %d started\n", *id);
    while (1) {	
        struct node *tmp = malloc(sizeof(struct node));
		consumed_val = remove_from_buffer( tmp );
	    if (consumed_val == -1){
            break;
        }	
		printer(consumed_val, *id); // print the squar root
	}
    //printf("consumer:%d exited\n", *id);
	pthread_exit(NULL);
}


void* producer(void* argument){
	int* id = (int*) argument;
    int produced = 0;
    int iterated = 0;

    while (produced < num/num_p){ 
        if ((iterated%num_p) == *id){
			struct node* tmp_p = malloc(sizeof(struct node));
			insert(tmp_p, iterated);
            produced ++;
		}
        iterated ++;
	}
    //printf("producer: %d exited\n", *id);
	pthread_exit(NULL);
}


void insert(struct node* tmp_p, int i){
	sem_wait(&spaces); // wait for spaces available
    pthread_mutex_lock(&(buffer.sem)); // then wait for there to buffer to be free
			
	tmp_p->next = NULL; // This will go to the end of the list
	tmp_p->value=i; // Set the value
		
	if (buffer.size == 0) {
		buffer.head = tmp_p;
		buffer.tail = tmp_p;	
	} else {
		buffer.tail->next=tmp_p; // Point the tail to the temp
		buffer.tail = tmp_p; // set the tail to tmp
	}

	buffer.size ++; // increase the buffer count
    pthread_mutex_unlock(&(buffer.sem)); // free the buff
	sem_post(&items); // post to items
	
    pthread_mutex_lock( &mutex); // This could be bad	
	remaining --;
	pthread_mutex_unlock( &mutex); //unlock
}


int remove_from_buffer( struct node * tmp){
    int consumed_val = -1; sem_wait(&items); // wait on available items
    pthread_mutex_lock(&(buffer.sem)); // wait on buffer being available

	tmp = buffer.head; // set temp to the head of the list
	consumed_val = tmp->value; // get the value of that item
	if (buffer.size <= 1){
		buffer.head = NULL;			
        buffer.tail = NULL;
	} else {
		buffer.head = tmp->next; // adjust the buffer head
	}
	buffer.size --; // adjust the size of the buffer

	pthread_mutex_unlock(&(buffer.sem)); // signal that the buffer is free
	sem_post(&spaces); // signal that an item has been removed 
	free(tmp); // free the old head/tmp
    //printf("Removing into the queue: %d\n", consumed_val);
    return(consumed_val);
}

void printer(int n, int id){
    if (n==0 || n==1){
        printf("%d %d %d \n", id, n, n);
    }
    for (int i = 0; i < (n); i++){
		if ( (i*i) == n ) {
		    printf("%d %d %d \n", id, n, i);
        }
	}

}


