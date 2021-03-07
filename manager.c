#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  char *name[30];
  char *title[30];
  char *status[30];

  printf("Hello, What employee would you like information on?\n");
  scanf("%[^\n]%*c", name);

  printf("What is %s's job title?\n", name);
  scanf("%[^\n]%*c", title);

  printf("What is %s's job status?\n", name);
  scanf("%[^\n]%*c", status);

  printf("%s\t%s\t%s\n", name, title, status);
  return 0;
}
