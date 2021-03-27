#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <wait.h>
#include "Assistant.h"
#include <stdbool.h>
#define FILEPATH "History.txt"

int LinePosition = 1;
char path[20] = "/dev/pts/";
bool isFirst = true;

void assistant(char *outgoingBuffer){
	//Storage for stuff from manager
	char *name[30];
	char *title[30];
	char *status[30];
	char temp [93];
	int fd;
	char pipe[] = ".pipe";

	//Setting up socket connection
	int network_socket = socket(AF_INET,SOCK_STREAM, 0);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	/*Connect to the server and verify that the connection succeeded*/
	int connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    if(connection_status == -1){
        perror("There was an error establishing a connection");
        exit(EXIT_FAILURE);
    }

	/* create the FIFO (named pipe) */
	mkfifo(pipe, 0666);

	// Open pipe as read only for the assistant
	if((fd = open(pipe, O_RDONLY | O_CREAT)) < 0) perror("Pipe creation failure");

	while(TRUE){
		//reading info from pipe
		if(read(fd, &temp, sizeof(temp) + 1) < 0) perror("Read failure");
		sscanf(temp, "%[^,]%*c%[^,]%*c%[^\n]%*c", &name, title, status);

		// Go looking for the employee here
	}

    int LineCount = 0;
    char storeC;
    char outgoingBuffer[256];
    printf("%s\n", outgoingBuffer);

    // check number of lines written in file
    FILE *ftemp;
    FILE *fp = fopen("History.txt", "r");

    if(fp == NULL){
	    printf("unable to open file\n");
	    exit(EXIT_FAILURE);
    }

    while((storeC = fgetc(fp)) != EOF){
	    if(storeC == '\n'){
		    LineCount++;
	    }
    }

    int count = 0;
    char incomingBuffer[256];

	else{
   	send(network_socket, outgoingBuffer, 256, 0);
   	recv(network_socket, incomingBuffer, sizeof(incomingBuffer), 0);
	 	if(strcmp(incomingBuffer, "INVALID")==0){
			//if file has 10 lines use position to overwrite records
		}else if(LineCount == 10){
			//program uses temp.txt to store records from History.txt
			fp = fopen("History.txt", "r");
			ftemp = fopen("temp.txt", "w");

			while((fgets(lineBuffer, 256, fp)) != NULL){
				count++;

				if(count == LinePosition){
					fprintf(ftemp, "%s\n", incomingBuffer);
				}else{
					fprintf(ftemp, "%s", lineBuffer);
				}
			}

			fclose(fp);
			fclose(ftemp);

			//replace History.txt with the temp.txt
			remove("History.txt");
			rename("temp.txt", "History.txt");
			LinePosition++;

			if(LinePosition == 11){
				LinePosition = 1;
			}
		}else{
			fp = fopen("History.txt", "a");
			fprintf(fp, "%s\n", incomingBuffer);
			fclose(fp);
		}

		termPrinter(incomingBuffer);
		close(network_socket);
    }
}

//function that prints to a new terminal
//requires tty ID for printing
void termPrinter(char *results){
	if(isFirst){
		printf("please type terminal tty ID number(type tty into the terminal you wish to print on and enter the last digit shown)\n");
		char id[2];
		scanf("%[^\n]%*c", id);
		strcat(path, id);
		isFirst = false;
	}

	FILE *fterm = fopen(path, "wr");

	if(fterm != NULL){
		fprintf(fterm, "%s\n", results);
	}else{
		perror("tty terminal not found");
		exit(EXIT_FAILURE);
	}

	fclose(fterm);
}
