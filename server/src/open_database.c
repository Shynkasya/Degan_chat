#include"../inc/server.h"

int open_database(const char* name, sqlite3 *db){
	char* err_msg = NULL;
	int rc = sqlite3_open(name, &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}
    char *sql = "CREATE TABLE IF NOT EXISTS User (Id INTEGER PRIMARY KEY, Username TEXT, Password_Hash TEXT, Email TEXT);";

	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		sqlite3_close(db);
		return -1;
	}
	//free(sql);
	return 0;
}
