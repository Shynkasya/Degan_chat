#include"../inc/server.h"



int main(int argc, char* argv[]) {

	//daemon_server();
	database_init();
	int sockfd = connection(argc, argv);
	while(1) {
		int *clientfd = malloc(sizeof(int));
		struct sockaddr_in client_addr;
		socklen_t addr_len = sizeof(client_addr);
		*clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len);

		if (*clientfd < 0) {
			perror("error connection");
			free(clientfd);
			continue;
		}
		printf("Client %d connected to server\n", *clientfd);
	
		pthread_t tid;
		if ((pthread_create(&tid, NULL, &client_handler, clientfd)) != 0){
			perror("error creating thread");
			close(*clientfd);
			free(clientfd);
			continue;
        	}

		pthread_detach(tid);
	}
	close(sockfd);
	exit(0);
}





