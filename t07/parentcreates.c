#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

	int i;
	int n;
	int num_kids;

	if (argc != 2) {
		fprintf(stderr, "Usage: parentcreates <numkids>\n");
		exit(1);
	}

	num_kids = strtol(argv[1], NULL, 10);

	for (i = 0; i < num_kids; i++) {
		n = fork();
		if (n < 0) {
			perror("fork");
			exit(1);
		}
 		printf("pid = %d, ppid = %d, i = %d\n", getpid(), getppid(), i);
		if (n == 0) {
			break;
		}
	}
	if (n != 0) {
		int pid;
		int status;
		for (i = 0; i < num_kids; i++) {
			if ((pid = wait(&status)) == -1) {
				fprintf(stderr, "Error: wait.\n");
			}
		}
	}

	return 0;
}
