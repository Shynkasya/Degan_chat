#include "../inc/server.h"
//название таблицы с регистрации = users

void login_request(int sockfd, sqlite3 *db) {
    json_t *root = NULL;
    char buffer[1024] = {0};
    ssize_t nread = recv(sockfd, buffer, sizeof(buffer)-1, 0);
    buffer[nread] = '\0';
    printf("%s\n", buffer);
    printf("Bytes read %d\n", (int)nread);
    json_error_t err_msg;
    root = json_loads(buffer, 0, &err_msg);
    const char *login = json_string_value(json_object_get(root, "login"));
    const char *passhash = json_string_value(json_object_get(root, "passhash"));
	printf("login: |%s|\n", login);
    printf("passhash: |%s|\n", passhash);

	json_decref(root);
    char *sql = "SELECT * FROM users WHERE login = ? AND passhash = ?;";
    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {printf("%s\n", sqlite3_errmsg(db));};
    if (sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC) != SQLITE_OK) {printf("%s\n", sqlite3_errmsg(db));};
    if (sqlite3_bind_text(stmt, 2, passhash, -1, SQLITE_STATIC) != SQLITE_OK) {printf("%s\n", sqlite3_errmsg(db));};
    printf("Sql: %s\n", sqlite3_expanded_sql(stmt));
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
