#include "../inc/server.h"
#include <stdio.h>

bool user_exists(const char *name) {
    sqlite3* db;
    open_database(DATABASE, &db);
    char *query = "SELECT * FROM User WHERE Username = ?";
    sqlite3_stmt *stmt = NULL;
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        return true;
    }
    
    return false;
}

void create_user(int sockfd) {
    sqlite3* db;  
    open_database(DATABASE, &db);
    json_t *root = NULL;
    char buf[1024] = {0};
    ssize_t nread = recv(sockfd, buf, (sizeof buf) - 1, 0);
	  printf("%s\n", buf);
	  printf("Bytes read %d\n", (int)nread);
    json_error_t err_msg;
    root = json_loads(buf, 0, &err_msg);
    const char *username = json_string_value(json_object_get(root, "username"));
    const char *mail = json_string_value(json_object_get(root, "mail"));
    const char *passwd_hash = json_string_value(json_object_get(root, "passwd_hash"));
    sqlite3_stmt *stmt;

    if (user_exists(username)) {
        send(sockfd, "false", sizeof "false", 0);
        return;
    }
    
    char *query = "INSERT INTO User (Username, Email, PasswordHash) VALUES (?, ?, ?)";

    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, mail, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, passwd_hash, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        send(sockfd, "false", sizeof "false", 0);
        fprintf(stderr, "%s\n", sqlite3_errmsg(db));
        json_decref(root);
        return;
    }


    send(sockfd, "true", sizeof "true", 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    json_decref(root);
}

