#include"../inc/server.h"

int error_handler(int argc, char* argv[]){
	if(argc != 2){
		fprintf(stderr, "usage: ./uchat_server [network port]\n");
		return -1;
	}
	int i = 0;
	int port = 0;
	while(argv[1][i] != '\0'){
		port = port * 10 + argv[1][i] - '0';
		i++;
	}
	return port;
}
void *client_handler(void* client){
	int sockfd = *(int*) client;
	char buffer[1024];
	printf("%i\n", sockfd);
	recv(sockfd, buffer, 1024, 0);
	printf("%s", buffer);
	//sqlite3 *db = NULL;
	//sqlite3_open("database/Uchat.db", &db);
	
	//sqlite3_close(db);
	return NULL;
	
}
void create_thread(int* client){
	pthread_t thread;
	pthread_create(&thread, NULL, &client_handler,(void*)client);
	pthread_detach(thread);
}

int main(int argc, char* argv[]) {
	int port = error_handler(argc, argv);
	if(port == -1) return -1;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address = {0};
	address.sin_port = htons(port);
	address.sin_family = AF_INET;
	if(bind(sockfd, (struct sockaddr*)&address, sizeof(address)) == -1){
		printf("Binding isn't succesfull\n");
		close(sockfd);
		return -1;
	}
	if(listen(sockfd, 5) < 0){
		printf("Listen isn't succesfull\n");
		close(sockfd);
		return -1;
	}
	int* client;
    	sqlite3 *db = NULL;
    	if(open_database("database/Uchat.db", db) == -1) return -1;


	while(1){
		client = malloc(sizeof(int));
		*client = accept(sockfd, NULL, NULL);
		printf("New client added\n");

		create_thread(client);
 	}


    sqlite3_close(db);
 	close(sockfd);
    return 0;
}
