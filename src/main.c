#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char command[1024];

  setbuf(stdout, NULL);
  printf("$ ");
  fget(command, sizeof(command), stdin);

  return 0;
}
