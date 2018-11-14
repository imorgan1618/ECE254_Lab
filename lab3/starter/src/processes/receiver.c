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

	int pt;
	int sq;

/* 	if (argc != 4) {
		printf("Usage: %s <qname>\n", argv[0]);
		printf("The qname must start with a \"/\".\n");
		printf("An example qname: /mailbox1_i2morgan\n");
		exit(1);
	} 
*/
	qname ="/mailbox1_i2morgan";  // argv[1];

	attr.mq_maxmsg = QUEUE_SIZE;
	attr.mq_msgsize = sizeof(struct point);
	attr.mq_flags = 0;

	qdes = mq_open(qname, O_RDONLY, mode, &attr);
	if (qdes == -1) {
		perror("mq_open()");
		exit(1);
	}

	signal(SIGINT, sig_handler);

	while (g_continue) {
		struct point pt;
		struct timespec ts = {time(0) + 5, 0};
		
		if (mq_timedreceive(qdes, (char *) &pt, \
		    sizeof(struct point), 0, &ts) == -1) {
			perror("\nmq_timedreceive() failed");
			printf("Type Ctrl-C and wait for 5 seconds to terminate.\n");
		} else {
			printf("Received a random point at (%d, %d)\n", \
				get_x_coord(pt), get_y_coord(pt));
		}
	}

	while (1) {
		if (mq_receive(qdes, (char *)&ptr, sizeof(int), 0) == -1) {
			perror("mq_receive() failed");
		} else {
			i++;
		}
	}


	if (mq_close(qdes) == -1) {
		perror("mq_close() failed");
		exit(2);
	}

	return 0;

    /*mqd_t qdes;
    char qname[] = "/mailbox1_i2morgan";
    mode_t mode = S_IRUSR | S_IWUSR;
    struct mq_attr attr;

    int N = atoi(argv[1]);
    int B = atoi(argv[2]);

    if (argc != 3) {
        printf("Usage: produce %d %d\n", N, B);
        exit(1);
    }

    attr.mq_maxmsg = B;
    attr.mq_msgsize = sizeof(int);
    attr.mq_flags = 0;

    qdes = mq_open(qname, O_RDONLY, mode, &attr);
    if (qdes == -1) {
        perror("mq_open()");
        exit(1);
    }

    int count = 0;
    while (count < N) {
        int number;
        if (mq_receive(qdes, (char *) &number, sizeof(int), 0) == -1) {
             perror("mq_receive() failed");
        } else {
             printf("%d is consumed\n", number);
             count++;
        }
    }

   if (mq_close(qdes) == -1) {
        perror("mq_close() failed");
        exit(2);
    }

    return 0; */
}


