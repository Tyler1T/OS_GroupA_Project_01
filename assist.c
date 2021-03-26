#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <wait.h>
#define FILEPATH "History.txt"

int main(){

    int network_socket = socket(AF_INET,SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;
    int LineCount = 0;
    char storeC;
    // check number of lines written in file
    FILE *fp = fopen("History.txt", "r");
    while((storeC = fgetc(fp)) != EOF){
	    if(storeC == '\n'){
		    LineCount++;
	    }
    }
//    printf("%d\n", LineCount);
    fp = fopen("History.txt", "a");

    char outgoingBuffer[256], incomingBuffer[256];
    /*Connect to the server and verify that the connection succeeded*/
    int connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    if (connection_status == -1){
        perror("There was an error establishing a connection");
        exit(EXIT_FAILURE);
    }else{
//	while(1){
       	 printf("Enter a query: ");
       	 scanf("%[^\n]", outgoingBuffer);
       	 send(network_socket, outgoingBuffer, sizeof(outgoingBuffer), 0);
       	 recv(network_socket, incomingBuffer, sizeof(incomingBuffer), 0);
     	 printf("Message Received from Server: \n%s", incomingBuffer);
	 if(LineCount == 10){
		 fp = fopen("History.txt", "r+");
		 fprintf(fp, "%s\n", incomingBuffer);
	 }
	 else{
		 fp = fopen("History.txt", "a");
	  	 fprintf(fp, "%s\n", incomingBuffer);
	 }
       	 fclose(fp);
       	 close(network_socket);
//	}
    }


    return 0;
}
