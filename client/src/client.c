#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "client.h"

#define SERVER_PORT 8000


int main(int argc, char* argv[]) {
	int sockfd;
	struct sockaddr_in client_addr;
	
	if(argc != 3){
		fprintf(stderr, "usage: ./uchat [IP adress] [network port]\n");
		return -1;
	}

    	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        	fprintf(stderr, "Socket creation error\n");
        	return -1;
    	}

   	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(SERVER_PORT);
	//client_addr.sin_addr.s_addr = inet_addr(argv[1]);
	inet_pton(AF_INET, argv[1], &client_addr.sin_addr.s_addr);
	//bzero(&remote_server.sin_zero , 0);
	
	//char buffer[256];
	
	
	if (connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
		perror("Connection failed");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	
	char *msg = "Hello from client!";
	send(sockfd, msg, strlen(msg), 0);
	printf("Connection established!\n");
    
	//calling for a window initialization
	interface_init();
    
	close(sockfd);
    
    return 0;
}

