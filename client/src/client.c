#include "client.h"

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
	client_addr.sin_port = htons(atoi(argv[2]));
	client_addr.sin_addr.s_addr = inet_addr(argv[1]);
	//char buffer[256] = {0};
	if (connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
		perror("Connection failed");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	
	char *msg = "Hello from client!";
	send(sockfd, msg, strlen(msg), 0);
	printf("Connection established!\n");

	//calling for a window initialization
	interface_init(sockfd);

    
	//printf("Disconect\n");
	close(sockfd);
    return 0;
}

