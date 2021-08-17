#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 256
#define MAX_PASSWORD 10

#define SUCCESS "Password verified\n"
#define INVALID "Invalid password\n"
#define NO_USER "No such user\n"

int main(void) {
  char user_id[MAXLINE];
  char password[MAXLINE];

  if(fgets(user_id, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }
  if(fgets(password, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }

  int fd[2], process;            // create pipe
  if (pipe(fd) == -1) {
    fprintf(stderr, "Error: Failed to create pipe.\n");
    exit(1);
  }

  process = fork(); // create new process

  if (process == -1) {
    fprintf(stderr, "Error: fork\n");
    exit(1);
  }

  if (process == 0) {   // child process;
    dup2(fd[0], fileno(stdin));
    close(fd[0]);
    close(fd[1]);
    execl("./validate", "validate", NULL);
    printf("failed\n");
  }

  if (process > 0) {   // parent process
    int saved_stdout = dup(STDOUT_FILENO);
    dup2(fd[1], fileno(stdout));
    close(fd[0]);
    close(fd[1]);

    // send username
    int n = write(STDOUT_FILENO, user_id, strlen(user_id));
    for (int i = 0; i < 10 - strlen(user_id); i++) {
      n +=write(STDOUT_FILENO, "\0", 1);
    }

    // send password
    n = write(STDOUT_FILENO, password, strlen(password));
    for (int i = 0; i < 10 - strlen(password); i++) {
      n += write(STDOUT_FILENO, "\0", 1);
    }

    int pid;
    int status;
    if ((pid = wait(&status)) == -1 ) {
      fprintf(stderr, "Error: wait.\n");
      exit(1);
    }
    if (WIFEXITED(status)) {
      status = WEXITSTATUS(status);
    }

    dup2(saved_stdout, fileno(stdout));
    close(saved_stdout);
    if (status == 0) {
      printf("Password verified\n");
    } else if (status == 2) {
      printf("Invalid password\n");
    } else if (status == 3) {
      fprintf(stderr, "%d\n", status);
      printf("No such user\n");
    }
  }
  return 0;
}
