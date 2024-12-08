#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "sqlite3.h"
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <signal.h>
#include <pthread.h>
#include "../../libraries/jansson/jansson.h"

#define DB_PATH "server/database/Uchat.db" 
#define PID_FILE "/tmp/pid_file" //временный каталог в который записуется pid демона
#define DATABASE "server/database/Uchat.db"


extern pid_t pid;

typedef enum Operations{
	REGISTRATION,
	LOGIN,
	RECONNECTION,
	NEW_ROOM,
	NEW_CHAT,
	ADD_MEMBER,	
	SEND,
	RECEIVE, //????????????????????????????????????
	DELETE,
	EDIT,
	SEARCH_MESSAGE,
	SEARCH_CONTACT
} request;
//Functions for Operations(requests)
void login_request(int sockfd);
void create_user(int sockfd);

void daemon_server();
void *client_handler(void *arg);


//Database
void open_database(const char* name, sqlite3 **db);
void create_user_table(sqlite3** db);
void create_chat_table(sqlite3** db);
void create_member_table(sqlite3** db);
void create_messages_table(sqlite3** db);
void create_file_descriptor_table(sqlite3** db);
void database_init();

//connection.c
int connection(int argc, char *argv[]); //return socket fd



