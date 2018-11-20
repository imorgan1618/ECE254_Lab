// Use this to see if a number has an integer square root
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

double g_time[2];

int spawn (char* program, char** arg_list)
{
  	pid_t child_pid;
	int errno = -1;

  	/* Duplicate this process.  */
  	child_pid = fork();
  
  	if (child_pid != 0) {
    		/* This is the parent process.  */
    		return child_pid;
	} else {
    		/* Now execute PROGRAM, searching for it in the path.  */
    		execvp(program, arg_list);
    		/* The execvp function returns only if an error occurs.  */
    		fprintf (stderr, "an error occurred in execvp\n");
    		exit(errno);
		abort();
  	}
}

int main(int argc, char *argv[])
{
//	int num = 0;
//	int maxmsg = 0;
	
	int num_p = 0;
	int num_c = 0;
	int i = 0;
	int j = 0;
	int status;
	int finished = 0;

	struct timeval tv;
	char* pro_arg_list[6];
	char* con_arg_list[6];

	if (argc != 5) {
		printf("Usage: %s <N> <B> <P> <C>\n", argv[0]);
		exit(1);
	}
        gettimeofday(&tv, NULL);
        g_time[0] = (tv.tv_sec) + tv.tv_usec/1000000.;
//	num = atoi(argv[1]);	/* number of items to produce */
//	maxmsg = atoi(argv[2]); /* buffer size                */
	num_p = atoi(argv[3]);  /* number of producers        */
	num_c = atoi(argv[4]);  /* number of consumers        */
	
	if (atoi(argv[1]) < 1 || atoi(argv[2]) < 1 || atoi(argv[3]) < 1 || atoi(argv[4]) < 1) {
        	gettimeofday(&tv, NULL);
        	g_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

        	printf("System execution time: %.6lf seconds\n", \
        	    g_time[1] - g_time[0]);
	        exit(0);
	}

	pro_arg_list[0] = "/mailbox1_i2morgan";
	pro_arg_list[1] = argv[1];
	pro_arg_list[2] = argv[2];
	pro_arg_list[3] = argv[3];
	pro_arg_list[4] = NULL;
	pro_arg_list[5] = NULL;	

	con_arg_list[0] = "/mailbox1_i2morgan";
	con_arg_list[1] = argv[1];
	con_arg_list[2] = argv[2];
	con_arg_list[3] = argv[4];
	con_arg_list[4] = NULL;
	con_arg_list[5] = NULL;

	for (i = 0; i < num_p; i++) {
        	char str[15];
		sprintf(str, "%d", i);
		pro_arg_list[4] = str;
		spawn("./sender.out", pro_arg_list);
        }

	for (i = 0; i < num_c; i++) {
		char str[15];
		sprintf(str, "%d", i);
		con_arg_list[4] = str;
		spawn("./receiver.out", con_arg_list);
	}

	for (i = num_p + num_c; i > 0; i--) {
		wait(&status);
		if (WIFEXITED(status)) {
			finished++;
			if (finished >= num_p) {
        			for (j = 0; j < num_c; j++) {
					char str[15];
	              			sprintf(str, "%d", -1);
                			pro_arg_list[4] = str;
                			spawn("./sender.out", pro_arg_list);
				}
				break;
			}
		} else {
			printf("Abnormal exit\n");
		}
	}

	 gettimeofday(&tv, NULL);
        g_time[1] = (tv.tv_sec) + tv.tv_usec/1000000.;

    	printf("System execution time: %.6lf seconds\n", \
            g_time[1] - g_time[0]);
	exit(0);
}
