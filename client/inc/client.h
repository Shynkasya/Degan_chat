#ifndef CLIENT_H
#define CLIENT_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
} t_sign_up_data;

GtkWidget *create_header();
GtkWidget *create_chat_interface(GtkWidget *stack);
GtkWidget *create_login_interface(GtkWidget *stack);
GtkWidget *create_sign_in_interface(GtkWidget *stack);

void switch_to_chat(GtkButton *button, gpointer stack);
void switch_to_sign_in(GtkButton *button, gpointer stack);
void switch_to_login(GtkButton *button, gpointer stack);

void apply_css(GtkWidget *widget, const char *css);
int interface_init(void);
void validate_sign_up(GtkButton *button, gpointer user_data);

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
