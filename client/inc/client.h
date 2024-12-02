#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <gtk/gtk.h>


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




GtkWidget *create_header();
GtkWidget *create_chat_interface(GtkWidget *stack);
GtkWidget *create_login_interface(GtkWidget *stack);

void switch_to_chat(GtkButton *button, gpointer stack);
void apply_css(GtkWidget *widget, const char *css);
int interface_init(int argc, char *argv[]);

#endif
