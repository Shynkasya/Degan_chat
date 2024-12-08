#include "../inc/server.h"
void sent_message(int clientfd){
	sqlite3 *db = NULL;
	open_database(DATABASE, &db);
	

	int user_id;
	int chat_name;
	char text[1024];

	recv(clientfd, &chat_name, sizeof(chat_name), 0);
	recv(clientfd, &user_id, sizeof(user_id), 0);
	recv(clientfd, text, sizeof(text), 0);
	const char *insert_query = "INSERT INTO Messages (CHAT_ID, USER_ID, MESSAGE_CONTENT, DATE) VALUES (?, ?, ?, ?)";
	sqlite3_stmt *stmt;

	if (sqlite3_prepare_v2(db, insert_query, -1, &stmt, NULL) != SQLITE_OK) {
		fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}

	sqlite3_bind_int(stmt, 1, chat_name);
	sqlite3_bind_int(stmt, 2, user_id);
	sqlite3_bind_text(stmt, 3, text, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 4, (int)time(NULL));

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);
	
	
	
	
	
	
	
	
	
	sqlite3_close(db);
}
void recieve_messages(int chat_id, int user_id){
	sqlite3_stmt *stmt;
	const char *sql = "SELECT USER_ID FROM Member WHERE CHAT_ID = ?";
	int rc;

	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
		printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}

	sqlite3_bind_int(stmt, 1, chat_id);
	int user_count = 0;

	while (sqlite3_step(stmt) == SQLITE_ROW) user_count++;
	int *users = malloc(sizeof(int) * user_count);
	sqlite3_finalize(stmt);
    
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}
	sqlite3_bind_int(stmt, 1, chat_id);
	while (sqlite3_step(stmt) == SQLITE_ROW) {
	
        rows[row_count].id = sqlite3_column_int(stmt, 0);  // Извлечение ID
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        strncpy(rows[row_count].name, (const char *)name, sizeof(rows[row_count].name) - 1);
        rows[row_count].value = sqlite3_column_double(stmt, 2);  // Извлечение числового значения

        row_count++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    for (int i = 0; i < row_count; i++) {
        printf("Row %d: ID=%d, Name=%s, Value=%.2f\n", i, rows[i].id, rows[i].name, rows[i].value);
    }

}


void *client_handler(void *arg) {
	int clientfd = *(int *)arg;
	request op_number;
	while(1){
		int nread = recv(clientfd, &op_number, sizeof(op_number), 0);
                if (nread <= 0) {
                	if (nread == 0) printf("Connection %d closed\n", clientfd);
                    else perror("recv error: ");
                    break;
                }
		switch(op_number){
			case REGISTRATION:
			
			  	break;
		  	case LOGIN: 
				login_request(clientfd);
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
		  		sent_message(clientfd);
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
		  
	}
	close(clientfd);
	free(arg);
	pthread_exit(0);
}
