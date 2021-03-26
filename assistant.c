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
  char *name[30];
  char *title[30];
  char *status[30];
  char temp [93];
  int fd;
  char pipe[] = ".pipe";

  /* create the FIFO (named pipe) */
  mkfifo(pipe, 0666);

  // Open pipe as read only for the assistant
  fd = open(pipe, O_RDONLY);
  if(fd < 0) perror("Pipe failure");

  while(1 == 1){
      sleep(1);
      if(read(fd, &temp, sizeof(temp) + 1) < 0) perror("Stuck");
      sscanf(temp, "%[^,]%*c%[^,]%*c%[^\n]%*c", &name, title, status);
      printf("Manager is looking for: %s, %s, %s\n", name, title, status);
      // Go looking for the employee here
      //reading info from pipe
  }

  // Close plpe
  close(fd);

  /* remove the FIFO */
  unlink(pipe);
  return 0;
}
