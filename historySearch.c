#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void searchHistory(char *findItem);

void main(){
    char name[255]="ThOMas is ";
    searchHistory(name);
}

void searchHistory(char *findItem){
  FILE* fpointer;
	int wordExists=0;
	int bufferLength = 255;

	char buffer[bufferLength];
	fpointer = fopen("history.txt", "r");

	/* fopen() return NULL if last operation was unsuccessful */
    if(fpointer == NULL){
        /* File not created hence, create the file and exit */
        printf("No history file found.\n");
        printf("\nCreating a new history file...\n");
        fpointer = fopen("history.txt", "a+");

        exit(EXIT_FAILURE);
    }

    //copies the contents in the file to a character buffer
	while(fgets(buffer, bufferLength, fpointer)){
	    //substring of the buffer and the string item to search
	    //and checks if the search string is in file
	    //THE StrStrIA is a function that ignores case when comparing strings
		char *ptr = StrStrIA(buffer,findItem);
		if (ptr != NULL){
			wordExists=1;
			break;
		}
	}
	fclose(fpointer);

	//check if the string exists the history file
	if (wordExists==1){
		printf("String exists.");
	}else{
		printf("String does not exist.\n");
		printf("Will add strings to history file...\n");
	}

	fclose(fpointer);
}
