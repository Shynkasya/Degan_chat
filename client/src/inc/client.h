#ifndef CLIENT_H
#define CLIENT_H

#include <gtk/gtk.h>

GtkWidget *create_header();
GtkWidget *create_chat_interface(GtkWidget *stack);
GtkWidget *create_login_interface(GtkWidget *stack);

void switch_to_chat(GtkButton *button, gpointer stack);
void apply_css(GtkWidget *widget, const char *css);
int interface_init(int argc, char *argv[]);

#endif
