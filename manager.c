#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	// for fork
#include <sys/types.h>	// for pid_t
#include <sys/stat.h>  //for mkfifo
#include <stdlib.h>	// for exit(1)
#include <string.h>	// for strlen
#include <sys/wait.h>	// for wait
#include <fcntl.h> //for file stuff

int main() {
  char *temp[30];
  char *toSend[93];
  int fd;
  char *pipe = "pipe";

  /* create the FIFO (named pipe) */
  mkfifo(pipe, 0666);
  printf("hang\n");
  // Open pipe as write only for the manager
  if ((fd = open(pipe, O_WRONLY | O_CREAT)) < 0){
      printf("Pipe did not open\n");
      return 0;
  }
  printf("hang\n");

  while(1==1){
    printf("Hello, What employee would you like information on?\n");
    scanf("%[^\n]%*c", temp);
    strcat(*toSend, *temp);
    strcat(*toSend, ",");

    printf("What is %s's job title?\n", temp);
    scanf("%[^\n]%*c", temp);
    strcat(*toSend, *temp);
    strcat(*toSend, ",");

    printf("What is %s's job status?\n", temp);
    scanf("%[^\n]%*c", temp);
    strcat(*toSend, *temp);

    printf("You are looking for: %s\n", toSend);

    //writing info to pipe
    write(fd, toSend, sizeof(toSend));
  }

  // Close plpe
  close(fd);

  /* remove the FIFO */
  unlink(pipe);
  return 0;
}
