#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "sqlite3.h"
#include <string.h>
#include <errno.h>
#include <stddef.h>

typedef struct Registration {
  char *name;
  char *email;
  char *password_hash;
} Reg;

int open_database(const char* name, sqlite3 *db);


//Daemonisation
void deamonization();



//connection.c
int Socket(int domain, int type, int protocol);
int port_checker(int argc, char* argv[]);
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);




int create_user(const char *name, sqlite3 *db, Reg incoming);
