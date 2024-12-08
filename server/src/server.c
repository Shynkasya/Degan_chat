#include"../inc/server.h"

int main(int argc, char* argv[]) {
//	daemon_server();


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
	
		pthread_t tid;
		if ((pthread_create(&tid, NULL, &client_handler, (void *)clientfd)) != 0){
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





