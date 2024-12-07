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
	
	request op;
	op = SEND;
	send(sockfd, &op, sizeof(op), 0);
	int chat_id = 4;
	send(sockfd, &chat_id, sizeof(chat_id), 0);
	int user_id = 42;
	send(sockfd, &user_id, sizeof(user_id), 0);
	char text[1024];
	strcpy(text, "Some string");
	send(sockfd, text, sizeof(text), 0);
	
	
	
	  
	printf("Connection established!\n");
    
	//calling for a window initialization
	//interface_init(argc, argv);
    
	//printf("Disconect\n");
	close(sockfd);
    return 0;
}

