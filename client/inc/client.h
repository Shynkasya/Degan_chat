#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <time.h>

// Операції
typedef enum e_operations {
    REGISTRATION,
    LOGIN,
    RECONNECTION,
    NEW_ROOM,
    NEW_CHAT,
    ADD_MEMBER,
    SEND,
    RECEIVE,
    DELETE,
    EDIT,
    SEARCH_MESSAGE,
    SEARCH_CONTACT
} t_request;

// Структура для повідомлень
typedef struct s_message {
    int user_id;                // ID користувача
    char text[256];             // Текст повідомлення
    char timestamp[20];         // Час відправки
} t_message;

// Структура для чату
typedef struct s_chat {
    char name[50];              // Назва чату
    GtkWidget *chat_view;       // Виджет для виводу чату
    GtkTextBuffer *buffer;      // Текстовий буфер
    t_message messages[100];    // Масив повідомлень
    int message_count;          // Кількість повідомлень
} t_chat;

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

GtkWidget *create_chat_interface(GtkWidget *stack);
void send_message(GtkButton *button, gpointer user_data);
void switch_chat(GtkListBoxRow *selected_row, gpointer data);

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

