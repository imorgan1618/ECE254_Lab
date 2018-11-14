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
    struct timeval tv;
    double t1;
    double t2; 
    double t3;

    int child_status;
    
    int N = atoi(argv[1]);
    int B = atoi(argv[2]);

    mqd_t qdes;

    char qname[] = "/mailbox1_i2morgan";

    mode_t mode = S_IRUSR | S_IWUSR;
    struct mq_attr attr;

    if (argc != 3) {
        printf("Usage: produce <N> <B>\n");
        exit(1);
    }

    qdes = mq_open(qname, O_RDWR | O_CREAT, mode, &attr);

    if (qdes == -1) {
        perror("mq_open() failed");
        exit(1);
    }

    char* arg_list[] = {
         "./receiver.out",
         argv[1],
         argv[2],
         NULL
    };

    srand(time(0));

    gettimeofday(&tv, NULL);
    t1 = tv.tv_sec + tv.tv_usec/1000000.0;

    spawn("./receiver.out", arg_list);

    gettimeofday(&tv, NULL);
    t2 = tv.tv_sec + tv.tv_usec/1000000.0;

    int count = 0;
    while (count < N)
    {
       int number;
       number = rand() % 100;
       
       if (mq_send(qdes, (char *)&number, sizeof(int), 0) == -1) {
           perror("mq_send() failed");
       }

       count++;
    }

    if (mq_close(qdes) == -1) {
       perror("mq_close() failed");
       exit(2);
    }
    
    wait(&child_status);

    if (WIFEXITED(child_status)) {
       gettimeofday(&tv, NULL);
       t3 = tv.tv_sec + tv.tv_usec/1000000.0;

       if (mq_unlink(qname) != 0) {
           perror("mq_unlink() failed");
           exit(3);
       }
    }

    printf("Time to initialize system: %f seconds\n", (t2-t1));
    printf("Time to transmit data: %f seconds\n", (t3-t2));

    return 0;
}