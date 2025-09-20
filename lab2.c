#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char *line = NULL;
  size_t len = 0;
  ssize_t readn;

  while (1) {
    printf("Enter programs to run.\n");

    fflush(stdout);
    readn = getline(&line, &len, stdin);
    if (readn == -1) {

      break;
    }
    if (line[readn - 1] == '\n') {
      line[readn - 1] = '\0';
    }
    pid_t pid = fork();
    if (pid == -1) {
      perror("fork");
      continue;
    }
    if (pid == 0) {
      execl(line, line, (char *)NULL);
      perror("Exec failue");
      exit(EXIT_FAILURE);
    } else {
      int status;
      waitpid(pid, &status, 0);
    }
  }
  free(line);
  return 0;
}
