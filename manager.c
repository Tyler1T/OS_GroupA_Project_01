#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	// for fork
#include <sys/types.h>	// for pid_t
#include <sys/stat.h>  //for mkfifo
#include <stdlib.h>	// for exit(1)
#include <string.h>	// for strlen
#include <sys/wait.h>	// for wait

int main(int argc, char const *argv[]) {
  char *name[30];
  char *title[30];
  char *status[30];
  int fd;
  char *pipe = "/tmp/pipe";

  printf("Hello, What employee would you like information on?\n");
  scanf("%[^\n]%*c", name);

  printf("What is %s's job title?\n", name);
  scanf("%[^\n]%*c", title);

  printf("What is %s's job status?\n", name);
  scanf("%[^\n]%*c", status);

  printf("%s\t%s\t%s\n", name, title, status);

  /* create the FIFO (named pipe) */
  mkfifo(pipe, 0666);

  /* write "Hi" to the FIFO */
  fd = open(pipe, O_WRONLY);
  write(fd, "Hi", sizeof("Hi"));
  close(fd);

  /* remove the FIFO */
  unlink(pipe);
  return 0;
}
