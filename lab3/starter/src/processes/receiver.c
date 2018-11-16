#include <mqueue.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "common.h"

#define _X_OPEN_SOURCE 600

int main(int argc, char*argv[])
{
    	mqd_t qdes;
    	char *qname = NULL;
    	mode_t mode = S_IRUSR | S_IWUSR;
    	struct mq_attr attr;
 	
	int id = atoi(argv[4]);
	qname = "/mailbox1_i2morgan";

    	attr.mq_maxmsg = QUEUE_SIZE;
    	attr.mq_msgsize = sizeof(int);
    	attr.mq_flags = 0;

   	qdes = mq_open(qname, O_RDONLY, mode, &attr);
    	if (qdes == -1) {
        	perror("mq_open()");
       		exit(1);
    	}

    	while (1) {
        	int number;
        	if (mq_receive(qdes, (char *) &number, sizeof(int), 0) == -1) {
             		perror("mq_receive() failed");
			break;
        	} else {
			if (number == -1) {
				break;
			}

			if (number == 0 || number == 1) {
				printf("%d %d %d \n", id, number, number);
			}		
	
			for (int i = 0; i < number; i++) {
				if (i*i == numer) {
             				printf("%d %d %d \n", id, number, i);
				}
			}
       	 	}
    	}

   if (mq_unlink(qdes) == -1) {
        perror("mq_close() failed");
        exit(2);
    }

    return 0;
}


