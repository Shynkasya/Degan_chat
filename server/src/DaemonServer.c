#include "../inc/server.h"

#define PID_FILE "/tmp/pid_file"

static void signal_handler(int sig) {
  if (sig == SIGTERM) {
    printf("SIGTERM received\n");
    remove(PID_FILE);
    exit(0);
  }
}

void *Potok(void *arg) {
  int clientfd = *(int *)arg;
  printf("Client connected to server\n");

    const char *response = "Hi from server";
    send(clientfd, response, strlen(response), 0);

  char buffer[1024];
	int nread = recv(clientfd, buffer, sizeof(buffer), 0);
        if (nread == -1) {fprintf(stderr, "Error receiving data from server"); exit(1);}
    buffer[nread] = '\0';
    printf("Received data: %s\n", buffer);


    close(clientfd);
    free(arg);
    printf("Client disconnected from server\n");
    pthread_exit(0);
}

void DaemonServer(int argc, char* argv[]) {
  freopen("log.txt", "a", stderr);
  freopen("log.txt", "a", stdout); //всё выводится в log.txt
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);
  printf("==========NEW_SESSION==========\n");
  signal(SIGTERM, signal_handler);

  int sockfd = _connection(argc, argv);

  while(1) {
    int *clientfd = malloc(sizeof(int));
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    *clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len);
    if (*clientfd < 0) {
      perror("error connection");
      continue;
    }

    pthread_t tid;
	if ((pthread_create(&tid, NULL, &Potok, (void *)clientfd)) != 0){
		perror("error creating thread");
        close(*clientfd);
        free(clientfd);
        continue;
        }

    pthread_detach(tid);
  }

  sqlite3 *db = NULL;
  if(open_database("database/Uchat.db", db) == -1) exit(1);



  sqlite3_close(db);
  close(sockfd);
  exit(0);
}
