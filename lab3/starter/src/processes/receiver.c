#include <mqueue.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "common.h"

#define _XOPEN_SOURCE 600

void busy_loop(int iters)
{
  volatile int sink;
  do
  {
    sink = 0;
  } while (--iters > 0);
  (void)sink;
}

int main(int argc, char*argv[])
{
	mqd_t qdes;
	char *qname = NULL;
	mode_t mode = S_IRUSR | S_IWUSR;
	struct mq_attr attr;
	int id = atoi(argv[4]);

	qname ="/mailbox1_i2morgan";

	attr.mq_maxmsg = QUEUE_SIZE;
	attr.mq_msgsize = sizeof(int);
	attr.mq_flags = 0;
	
	qdes = mq_open(qname, O_RDONLY | O_CREAT, mode, &attr);
	if (qdes == -1) {
		perror("mq_open() in receiver\n");
		exit(1);
	}

	while (1) {
		int number;
		
		if (mq_receive(qdes,(char *)&number, sizeof(int)*QUEUE_SIZE, 0) == -1) {
			perror("mq_receive() failed\n");
			break;			
		} else {
			if (number == -200) {
				break; // death pill
			}
		
            		// normal loop function
            		if (number == 0 || number == 1) {
				printf("%d %d %d\n", id, number, number);
			}

			for (int i = 0; i < number; i++) {
				if (i*i == number) {
					// Busy loop for testing purposes
                    			busy_loop(30000);
					printf("%d %d %d \n", id, number, i);
				}
			} 
		}
	}

	if (mq_close(qdes) == -1) {
		perror("mq_close() failed in receiver\n");
		exit(2);
	}
	return 0;
}



