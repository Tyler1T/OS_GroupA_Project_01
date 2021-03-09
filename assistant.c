#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	// for fork
#include <sys/types.h>	// for pid_t
#include <sys/stat.h>  //for mkfifo
#include <stdlib.h>	// for exit(1)
#include <string.h>	// for strlen
#include <sys/wait.h>	// for wait

void assistant() {
  char *name[30];
  char *title[30];
  char *status[30];
  int fd;
  char *pipe = "/tmp/pipe";

  /* create the FIFO (named pipe) */
  mkfifo(pipe, 0666);

  // Open pipe as read only for the manager
  fd = open(pipe, O_RONLY);

  while(true){
    read(fd, name, sizeof(name));
    printf("Manager is looking for: %s, %s, %s\n", name, title, status);

    //writing info to pipe
    read(fd, name, sizeof(name));
  }

  // Close plpe
  close(fd);

  /* remove the FIFO */
  unlink(pipe);
  return 0;
}
