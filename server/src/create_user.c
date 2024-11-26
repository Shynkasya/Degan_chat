#include "../inc/server.h"
#include <stdio.h>



int create_user(const char *name, sqlite3 *db, Reg incoming) {
    int rc = sqlite3_open(name, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_stmt *stmt;
    char *query = "INSERT INTO User (Username, Email, PasswordHash) VALUES (?, ?, ?)";

    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, incoming.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, incoming.email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, incoming.password_hash, -1, SQLITE_STATIC);

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

