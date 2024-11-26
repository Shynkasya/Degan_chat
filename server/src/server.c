#include"../inc/server.h"

void *client_handler(void* client){
	int sockfd = *(int*) client;
	free(client);
	//int client_request;
	
	
	//while(true){
	//	recv(sockfd, client_request, sizeof(client_request), 0);
	//
	//	switch(client_request){
	//	
	//	
	//	
	//	}
	//
	//}
	
	
	
	char buffer[1024];
	ssize_t bytes_read;
	bytes_read = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
	buffer[bytes_read] = '\0';
    	close(sockfd);
   	return NULL;
	//sqlite3 *db = NULL;
	//sqlite3_open("database/Uchat.db", &db);
	
	//sqlite3_close(db);
}
void create_thread(int* client){
	pthread_t thread;
	pthread_create(&thread, NULL, &client_handler,(void*)client);
	pthread_detach(thread);
}


int main(int argc, char* argv[]) {
	//deamonisation();
	sqlite3 *db = NULL;
    	open_database("database/Uchat.db", &db);

    	create_user_table(&db);
	int sockfd = connect_to_port(argc, argv);
	int *clientfd;
	while(1) {
		clientfd = malloc(sizeof(int));
		*clientfd = accept(sockfd, NULL, NULL);
		if (*clientfd < 0) {
			perror("error connection");
			free(clientfd);
			continue;
		}
		create_thread(clientfd);
 	}

	sqlite3_close(db);
	close(sockfd);
	return 0;
}
