#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *buff = NULL;
  size_t size = 0;

  printf("Please enter some text: ");
  ssize_t num_char = getline(&buff, &size, stdin);
  if (num_char == -1) {
    perror("getline failed");
    free(buff);
    exit(EXIT_FAILURE);
  }
  printf("Tokens:\n");
  char *saveptr;
  char *tok = strtok_r(buff, " ", &saveptr);

  while (tok != NULL) {
    printf(" %s\n", tok);
    tok = strtok_r(NULL, " \n", &saveptr);
  }

  free(buff);
  return 0;
}
