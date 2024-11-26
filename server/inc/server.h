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
#include <sys/stat.h>
#include <pthread.h>

typedef struct Registration {
  char *name;
  char *email;
  char *password_hash;
} Reg;



//Database
void open_database(const char* name, sqlite3 **db);
void create_user_table(sqlite3** db);


//Daemonisation
void deamonisation();



//connection.c
int Socket(int domain, int type, int protocol);
int port_checker(int argc, char* argv[]);
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
void initialise_adress(struct sockaddr_in *address, int port, int domain);
int connect_to_port(int argc, char* argv[]);




int create_user(const char *name, sqlite3 *db, Reg incoming);
