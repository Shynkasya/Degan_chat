#include "../inc/server.h"
//название таблицы с регистрации = users

void login_request(int sockfd, sqlite3 *db) {
    json_t *root = NULL;
    char buffer[1024] = {0};
    ssize_t nread = recv(sockfd, buffer, sizeof(buffer)-1, 0); //принимаем данные по запросу от клиента
    printf("%s\n", buffer);
    printf("Bytes read %d\n", (int)nread);
    json_error_t err_msg;
    root = json_loads(buffer, 0, &err_msg); //загружаем в json формат нашу строчку(char *)
    const char *login = json_string_value(json_object_get(root, "login"));//получаем значения по ключу
    const char *passhash = json_string_value(json_object_get(root, "passhash"));

    char *sql2 = "SELECT * FROM users WHERE login = ? AND passhash = ?;";//проверяем есть ли такой логин и хеш в бд
    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL) != SQLITE_OK) {printf("%s\n", sqlite3_errmsg(db));};
    if (sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC) != SQLITE_OK) {printf("%s\n", sqlite3_errmsg(db));};
    if (sqlite3_bind_text(stmt, 2, passhash, -1, SQLITE_STATIC) != SQLITE_OK) {printf("%s\n", sqlite3_errmsg(db));};
    if (sqlite3_step(stmt) != SQLITE_ROW) {
      	send(sockfd, "false", sizeof("false"), 0);
        printf("%s\n", sqlite3_errmsg(db));
        json_decref(root);
        return;
    }

    send(sockfd, "true", sizeof("true"), 0);
    const unsigned char *user_name = sqlite3_column_text(stmt, 0);
    const unsigned char *user_password = sqlite3_column_text(stmt, 1);
    printf("FOUND-> Login: %s ; password: %s\n", user_name, user_password);
        //отправить данные - авторизация успешна

	sqlite3_finalize(stmt);
	json_decref(root);
}
