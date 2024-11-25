#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sqlite3.h>

typedef struct Registration {
  char *name;
  char *email;
  char *password_hash;
} Reg;

int open_database(const char* name, sqlite3 *db);
int create_user(const char *name, sqlite3 *db, Reg incoming);
