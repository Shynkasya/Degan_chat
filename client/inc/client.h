#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <jansson.h>
#include <sys/socket.h>
#include <openssl/evp.h>
#include <openssl/sha.h>


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

typedef struct s_sign_up_data {
	GtkWidget *username;
	GtkWidget *email;
	GtkWidget *password;
	GtkWidget *password_repeat;
	GtkWidget *error_username_label;
	GtkWidget *error_email_label;
	GtkWidget *error_password_label;
	GtkWidget *error_password_label2;
	GtkWidget *stack;
	int sockfd;
} t_sign_up_data;

typedef struct s_login_data {
	int sockfd;
	GtkWidget *username_entry;
	GtkWidget *password_entry;
} t_login_data;

GtkWidget *create_header();
GtkWidget *create_chat_interface(GtkWidget *stack);
GtkWidget *create_login_interface(GtkWidget *stack, int sockfd);
GtkWidget *create_sign_in_interface(GtkWidget *stack);

void switch_to_chat(GtkButton *button, gpointer stack);
void switch_to_sign_in(GtkButton *button, gpointer stack);
void switch_to_login(GtkButton *button, gpointer stack);

void login(int sockfd, const char *email, const char *password);
void receive_response(int sockfd);
void register_user(int sockfd, const char *username, const char *email, const char *password);

void apply_css(GtkWidget *widget, const char *css);
int interface_init(int sockfd);
void validate_sign_up(GtkButton *button, gpointer user_data);

int send_request(int sockfd, int operation, const char *login, const char *passhash, const char *email);

char *hash_password(const char *password);

char *mx_strrchr(const char *str, int ch);
char *mx_strstr(const char *haystack, const char *needle);
char *mx_strcpy(char *dst, const char *src);
int mx_strlen(const char *s);

bool mx_isalpha(int c);
bool mx_isdigit(int c);
bool mx_isspace(char c);
bool mx_ispunct(int ch);
bool mx_isupper(int c);
bool mx_islower(int c);

#endif

