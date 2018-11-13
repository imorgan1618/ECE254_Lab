#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>

double ta;
double tb;
struct timeval tv;

char* pro_arg_list[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

char* con_arg_list[] = {
    NULL,
    NULL,
    NULL,
    NULL.
    NULL,
    NULL
};

int spawn(char* program, char** arg_list)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid != 0) {
         return child_pid;
    } else {
         execvp(program, arg_list);
         fprintf(stderr, "an error occurred in axecvp\n");
         abort();
    }
}

int main(int argc, char *argv[])
{
    int i;
    int j;
    int status;
    int k;

    pro_arg_list[0] = "./sender.out";
    pro_arg_list[1] = argv[1];
    pro_arg_list[2] = argv[2];
    pro_arg_list[3] = argv[3];
    pro_arg_list[5] = NULL;

    con_arg_list[0] = "./receiver.out";
    con_arg_list[1] = argv[1];
    con_arg_list[2] = argv[2];
    con_arg_list[3] = argv[4];
    con_arg_list[5] = NULL;

    gettimeofday(&tv, NULL);
    ta = tv.tv_sec + tv.tv_usec/1000000.0;

    for (i = 0; i < atoi(argv[3]; i++)) {
        char str[15];
        sprintf(str, "%d", i);
        pro_arg_list[4] = str;
        spawn("./sender.out", pro_arg_list);
    }

    for (j = 0; j < atoi(argv[4]); j++) {
        char str[15];
        sprintf(str, "%d", j);
        spawn("./receiver.out", con_arg_list);
    }

    for (k = atoi(argv[3]) + atoi(argv[4]); k > 0; k--) {
        wait(&status);
        if (WIFEXITED(status))
        {
            /* Normal Exit */
        } else {
            printf("Abnormal exit");
        }
    }

    exittimeofday(&tv, NULL);
    tb = tv.tv_sec + tv.tv_usec/1000000.0;

    printf("System execution time: %.6lf seconds", tb-ta-1);

    return 0;
}
