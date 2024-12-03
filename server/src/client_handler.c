#include "../inc/server.h"
void *client_handler(void *arg) {
	int clientfd = *(int *)arg;
	//char buffer[1024];
	request op_number;
	sqlite3 *db = NULL;
	open_database("server/database/Uchat.db", &db);
    /////////////////////////////////////////
    char *err_msg = NULL;
    char *sql = "CREATE TABLE IF NOT EXISTS users (login TEXT, password TEXT);"
                "INSERT INTO users (login, password) VALUES ('Vlad', '53225d');";
    int rc;
    if ((rc = sqlite3_exec(db, sql, 0, 0, &err_msg)) != SQLITE_OK) {
    	printf("SQL error: %s\n", err_msg);
        close(clientfd);
        sqlite3_close(db);
    }
    printf("users created\n");



	int i = 0;
    /////////////////////////////////
	//const char *response;
	while(i < 1){
          i++;
		//recv(clientfd, &op_number, sizeof(op_number) - 1, 0);
		pthread_mutex_lock(&mutex);
                op_number = LOGIN;
		switch(op_number){
			case REGISTRATION:
			  	break;
		  	case LOGIN: login_request(clientfd, db);

 			  	break;
		  	case RECONNECTION:
		  		break;
		  	case NEW_ROOM:
		  		break;
		  	case NEW_CHAT:
  		  		break;
		  	case ADD_MEMBER:	
		  		break;
		  	case SEND:
		  		break;
		  	case RECEIVE: //????????????????????????????????????
		  		break;
		  	case DELETE:
		  		break;
		  	case EDIT:
		  		break;
		  	case SEARCH_MESSAGE:
		  		break;
		  	case SEARCH_CONTACT:
		  		break;

		  }
		  pthread_mutex_unlock(&mutex);
		  
	}
	close(clientfd);
	free(arg);
	printf("Client %d disconnected from server\n", clientfd);
	sqlite3_close(db);
	pthread_exit(0);
}
