#include <mqueue.h>
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
#include "point.h"

int spawn(char* program, char** arg_list)
{
    pid_t child_pid;
    
    /* Duplicate this process. */
    child_pid = fork();
    if (child_pid != 0) {
        /* This is the parent process. */
        return child_pid;
    } else {
        execvp(program, arg_list);
        fprintf(stderr, "an error occurred in execvp\n");
        abort();
    }
}


int main(int argc, char *argv[])
{
   	mqd_t qdes;
	char *qname = NULL;
	
	int produced = 0;
	int iterated = 0;
	int endItem = -1;

	int num = atoi(argv[1]);
	int num_p = atoi(argv[3]);
	int id = atoi(argv[4]); 

	mode_t mode = S_IRUSR | S_IWUSR;
    	struct mq_attr attr;

	qname = "/mailbox1_i2morgan";

   	attr.mq_maxmsg = QUEUE_SIZE;
	attr.mq_msgsize = sizeof(int);
	attr.mq_flags = 0;

    	qdes = mq_open(qname, O_RDWR | O_CREAT, mode, &attr);
    	if (qdes == -1) {
        	perror("mq_open() failed");
        	exit(1);
    	}

	if (id == -1) {
		if (mq_send(qdes, (char *)&endItem, sizeof(int), 0) == -1) {
			perror("mq_send() failed");
		}
	} else {
		while (produced < num/num_p) {
			int item;
			if ((iterated%num_p) == id) {
				item = iterated;
				if (mq_send(qdes, (char *)&item, sizeof(int), 0) == -1) {
					perror("mq_send() failed");
					break;
				}
				produced++;
			}
			iterated++;
		}
	}

	if (mq_close(qdes) == -1) {
		perror("mq_close() failed");
		exit(2);
	}

	if (mq_unlink(qname) != 0) {
		perror("mq_unlink() failed");
		exit(3);
	}
    	return 0;
}
