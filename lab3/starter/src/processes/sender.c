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

void busy_loop(int iters)
{
  volatile int sink;
  do
  {
    sink = 0;
  } while (--iters > 0);
  (void)sink;
}

int main(int argc, char *argv[])
{
	mqd_t qdes;
	char *qname = NULL;
	
	int endItem = -200;

	int num = atoi(argv[1]);
	int num_p = atoi(argv[3]);
	int id = atoi(argv[4]);
        char pill[15];
        sprintf(pill, "%s", "pill");

	mode_t mode = S_IRUSR | S_IWUSR;
	struct mq_attr attr;

	qname ="/mailbox1_i2morgan";

        attr.mq_maxmsg = QUEUE_SIZE;
	attr.mq_msgsize = sizeof(int);
	attr.mq_flags = 0;

	qdes = mq_open(qname, O_RDWR | O_CREAT, mode, &attr);
	if (qdes == -1) {
		perror("mq_open() failed in sender\n");
		exit(1);
	}

	if (atoi(argv[4]) == -200) {
		printf("its a pill\n");
fflush(stdout);
		if (mq_send(qdes, (char *)&endItem, sizeof(int), 0) == -1) {
	              perror("mq_send() failed in sender\n");
                }
	} else {
		//printf("Not a pill\n");
		for (int iterated = 0; iterated < num; iterated ++){
			int item;
			if ((iterated%num_p) == id) {
				item = iterated;
          		        busy_loop(30000);
				if (mq_send(qdes, (char *)&item, sizeof(int), 0) == -1) {
					perror("mq_send() failed\n");
					break;
				}
			}
		}
	}

	if (mq_close(qdes) == -1) {
		perror("mq_close() failed\n");
		exit(2);
	}

	/*if (mq_unlink(qname) != 0) {
		perror("mq_unlink() failed\n");
		exit(3);
	}*/

	return 0;
}
