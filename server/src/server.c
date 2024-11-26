#include"../inc/server.h"

int main(int argc, char* argv[]) {
	int port = port_checker(argc, argv);
	int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address = {0}; //server address
	address.sin_port = htons(port);
	address.sin_family = AF_INET;
	Bind(sockfd, (struct sockaddr*)&address, sizeof(address));
	Listen(sockfd, 5);
	int clientfd;
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr); 
	while(1) {
		clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len);
		if (clientfd < 0) {
			perror("error connection");
			continue;
		}
		
		char client_ip[INET_ADDRSTRLEN];
		if (inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip)) == NULL) {
			perror("inet_ntop");
			close(sockfd);
			exit(EXIT_FAILURE);
		}
		printf("Connected: %s\n", client_ip);
		
		const char *response = "Hi from server";
		send(clientfd, response, strlen(response), 0);
		close(clientfd);
 	}

    sqlite3 *db = NULL;
    if(open_database("database/Uchat.db", db) == -1) return -1;



    sqlite3_close(db);
 	close(sockfd);
    return 0;
}
