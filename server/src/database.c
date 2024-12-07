#include"../inc/server.h"

void open_database(const char* name, sqlite3 **db){
	int rc = sqlite3_open(name, *&db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
		sqlite3_close(*db);
		exit(EXIT_FAILURE);
	}
}
void create_user_table(sqlite3** db){
	char* err_msg = NULL;
	char *sql = "CREATE TABLE IF NOT EXISTS User (Id INTEGER PRIMARY KEY AUTOINCREMENT, Username TEXT, Password_Hash TEXT, Email TEXT);";
	int rc = sqlite3_exec(*db, sql, 0, 0, &err_msg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		sqlite3_close(*db);
		exit(EXIT_FAILURE);
	}
	//free(sql);
}
void create_chat_table(sqlite3** db){
	char* err_msg = NULL;
	char *sql = "CREATE TABLE IF NOT EXISTS Chat (CHAT_ID INTEGER PRIMARY KEY, CHAT_NAME TEXT);";
	int rc = sqlite3_exec(*db, sql, 0, 0, &err_msg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		sqlite3_close(*db);
		exit(EXIT_FAILURE);
	}
	//free(sql);
}
void create_member_table(sqlite3** db){
	char* err_msg = NULL;
	char *sql = "CREATE TABLE IF NOT EXISTS Member (Id INTEGER PRIMARY KEY AUTOINCREMENT, CHAT_ID INTEGER, USER_ID INTEGER, FOREIGN KEY (CHAT_ID) REFERENCES Chat(CHAT_ID), FOREIGN KEY (USER_ID) REFERENCES User(Id))";
	int rc = sqlite3_exec(*db, sql, 0, 0, &err_msg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		sqlite3_close(*db);
		exit(EXIT_FAILURE);
	}
	//free(sql);
}
void create_messages_table(sqlite3** db){
	char* err_msg = NULL;
	char *sql = "CREATE TABLE IF NOT EXISTS Messages (Id INTEGER PRIMARY KEY AUTOINCREMENT, CHAT_ID INTEGER, USER_ID INTEGER, MESSAGE_CONTENT BLOB, DATE INTEGER, FOREIGN KEY (CHAT_ID) REFERENCES Chat(CHATS_ID), FOREIGN KEY (USER_ID) REFERENCES User(Id))";
	int rc = sqlite3_exec(*db, sql, 0, 0, &err_msg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		sqlite3_close(*db);
		exit(EXIT_FAILURE);
	}
	//free(sql);
}



void create_file_descriptor_table(sqlite3** db){
	char* err_msg = NULL;
	char *sql = "CREATE TABLE IF NOT EXISTS fd_table(USER_ID INTEGER PRIMARY KEY, SOCKET_FD INTEGER); DELETE FROM fd_table; VACUUM";
	int rc = sqlite3_exec(*db, sql, 0, 0, &err_msg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		sqlite3_close(*db);
		exit(EXIT_FAILURE);
	}
	//free(sql);
}


void database_init(){
	if (sqlite3_config(SQLITE_CONFIG_SERIALIZED) != SQLITE_OK) {
		fprintf(stderr, "SQLite does not support serialized mode.\n");
		exit(1);
	}
	sqlite3* db;
	open_database("server/database/Uchat.db", &db);
	create_user_table(&db);
	create_chat_table(&db);
	create_member_table(&db);
	create_messages_table(&db);
	//create_file_descriptor_table(&db);
	sqlite3_close(db);
}

