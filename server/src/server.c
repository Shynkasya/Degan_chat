#include"../inc/server.h"

int main(int argc, char* argv[]) {
	//daemon_server();
	if (sqlite3_config(SQLITE_CONFIG_SERIALIZED) != SQLITE_OK) {
		fprintf(stderr, "SQLite does not support serialized mode.\n");
		return 1;
	}
	sqlite3* db;
	open_database("server/database/Uchat.db", &db);
	create_user_table(&db);
	create_chat_table(&db);
	create_member_table(&db);
	create_messages_table(&db);
	create_file_descriptor_table(&db);
	sqlite3_close(db);
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





