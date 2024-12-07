#include"../inc/server.h"
pthread_mutex_t mutex;
pid_t pid;

int main(int argc, char* argv[]) {
	daemon_server();

	int sockfd = connection(argc, argv);
	FILE *pid_file = fopen(PID_FILE, "w");
	if (!pid_file) {
		perror("fopen");
		exit(1);
	}
	fprintf(pid_file, "%d\n", getpid());
	fclose(pid_file);
	pthread_mutex_init(&mutex, NULL);

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
	pthread_mutex_destroy(&mutex);
	close(sockfd);
	exit(0);
}





