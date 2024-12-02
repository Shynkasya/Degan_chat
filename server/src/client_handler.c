#include "../inc/server.h"
void *client_handler(void *arg) {
	int clientfd = *(int *)arg;
	//char buffer[1024];
	request op_number;
	sqlite3 *db = NULL;
	open_database("server/database/Uchat.db", &db);
	//const char *response;
	while(true){
		recv(clientfd, &op_number, sizeof(op_number) - 1, 0);
		switch(op_number){
			case REGISTRATION:
			
			  	break;
		  	case LOGIN:
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
		  	case RECIEVE: //????????????????????????????????????
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
		  
	}
	close(clientfd);
	free(arg);
	printf("Client disconnected from server\n");
	sqlite3_close(db);
	pthread_exit(0);
}
