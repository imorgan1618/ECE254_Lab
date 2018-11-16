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
#include "point.h"

#define _XOPEN_SOURCE 600

bool g_continue = true;

void sig_handler(int sig)
{
	g_continue = false;
}

int main(int argc, char*argv[])
{
	mqd_t qdes;
	char *qname = NULL;
	mode_t mode = S_IRUSR | S_IWUSR;
	struct mq_attr attr;
	int id = atoi(argv[4]);
	int pt;
	int sq;

	qname ="/mailbox1_i2morgan";

	attr.mq_maxmsg = QUEUE_SIZE;
	attr.mq_msgsize = sizeof(int);
	attr.mq_flags = 0;
	
	qdes = mq_open(qname, O_RDONLY, mode, &attr);
	if (qdes == -1) {
		perror("mq_open()");
		exit(1);
	}

//	signal(SIGINT, sig_handler);

	while (1) {
		int number;
		if (mq_receive(qdes, (char *)&number, sizeof(int)*QUEUE_SIZE, 0) == -1) {
			perror("mq_receive() failed");
			break;			
		} else {
			if (number == 0 || number == 1) {
				printf("%d %d %d\n", id, number, number);
			}

			for (int i = 0; i < number; i++) {
				if (i*i == number) {
					printf("%d %d %d \n", id, number, i);
				}
			} 

//			if (number == -1) {
//				break;
//			}
		}
	}

	printf("Closing consumer");
	if (mq_close(qdes) == -1) {
		perror("mq_close() failed in receiver");
		exit(2);
	}

	return 0;
}


