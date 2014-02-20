#include <fcntl.h>              
#include <stdio.h>              
#include <stdlib.h>             

int main(int argc, char **args) {
  printf("ATTEMPTING OPEN:\n");

  int fd = open("/Users/timmattison/Desktop/annex/github/sjmmie/testing", O_WRONLY | O_APPEND);

  printf("file descriptor: %d\n", fd);

  return 0;
}
