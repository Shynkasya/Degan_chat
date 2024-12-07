#include "../inc/server.h"
void *client_handler(void *arg) {
	int clientfd = *(int *)arg;
	//char buffer[1024];
	request op_number;
	sqlite3 *db = NULL;
	open_database("server/database/Uchat.db", &db);
    /////////////////////////////////////////
    char *err_msg = NULL;
    char *sql = "DROP TABLE IF EXISTS users;"
        		"CREATE TABLE IF NOT EXISTS users (login TEXT, passhash TEXT);"
                "INSERT INTO users (login, passhash) VALUES ('Vlad', 'fetewyghdfr');";
    int rc;
    if ((rc = sqlite3_exec(db, sql, 0, 0, &err_msg)) != SQLITE_OK) {
    	printf("SQL error: %s\n", err_msg);
        close(clientfd);
        sqlite3_close(db);
        return NULL;
    }
    printf("users created\n");

    /////////////////////////////////
	while(1){
		int nread = recv(clientfd, &op_number, sizeof(op_number), 0);
                if (nread <= 0) {
                	if (nread == 0) printf("Connection %d closed\n", clientfd);
                    else perror("recv error: ");
                    break;
                }
                op_number = ntohl(op_number);
                printf("Bytes read: %d\n", nread);
                printf("op number = %d\n", op_number);
		pthread_mutex_lock(&mutex);
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
            default:
              printf("Unknown operation number: %d\n", op_number);
              break;

		  }
		  pthread_mutex_unlock(&mutex);
		  
	}
	close(clientfd);
	free(arg);
	sqlite3_close(db);
	pthread_exit(0);
}
