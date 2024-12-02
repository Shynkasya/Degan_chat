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
#include <signal.h>
#include <pthread.h>


#define PID_FILE "/tmp/pid_file" //временный каталог в который записуется pid демона

typedef enum Operations{
	REGISTRATION,
	LOGIN,
	RECONNECTION,
	NEW_ROOM,
	NEW_CHAT,
	ADD_MEMBER,	
	SEND,
	RECIEVE, //????????????????????????????????????
	DELETE,
	EDIT,
	SEARCH_MESSAGE,
	SEARCH_CONTACT
} request;


typedef struct Message{
	int id;
	char*name;
	//need to add time
	char* text;
} Mess;

typedef struct Registration {
  char *name;
  char *email;
  char *password_hash;
} Reg;

void daemon_server();
void signal_handler(int sig);
void *client_handler(void *arg);

int open_database(const char* name, sqlite3 *db);

//connection.c
int connection(int argc, char *argv[]);
int Socket(int domain, int type, int protocol);
int port_checker(int argc, char* argv[]);
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);

int create_user(const char *name, sqlite3 *db, Reg incoming);
