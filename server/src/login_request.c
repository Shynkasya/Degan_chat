#include "../inc/server.h"
//название таблицы с регистрации = users

void login_request(int sockfd, sqlite3 *db) {
    char password[64], login[64];
    int nread = recv(sockfd, &login, sizeof(login), 0);
    login[nread] = '\0';
    nread = recv(sockfd, &password, sizeof(password), 0);
    password[nread] = '\0';




    char *sql = "SELECT 1 FROM users WHERE login = ? AND password = ?;";
    sqlite3_stmt *stmt = NULL;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_ROW) {
      printf("%s\n", sqlite3_errmsg(db));
      return;
    } else {
      const unsigned char *user_name = sqlite3_column_text(stmt, 0);
      const unsigned char *user_password = sqlite3_column_text(stmt, 1);
      printf("Login: %s ; password: %s\n", user_name, user_password);
    }


    sqlite3_finalize(stmt);
}
