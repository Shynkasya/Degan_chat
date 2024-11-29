#include"../inc/server.h"

#define PID_FILE "/tmp/pid_file" //временный каталог в который записуется pid демона
int main(int argc, char* argv[]) {

  pid_t pid;
  pid = fork();
  if (pid == -1) { perror("fork"); exit(1); }
  else if (pid == 0) {
    setsid();
    FILE *pid_file = fopen(PID_FILE, "w");
    if (!pid_file) { perror("fopen"); exit(1); }
    fprintf(pid_file, "%d\n", getpid());
    fclose(pid_file);
    DaemonServer(atoi(argv[1]));
  }
  else {
    exit(0);
  }

	int sockfd = _connection(argc, argv);
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
