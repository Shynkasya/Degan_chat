#include "client.h"


int interface_init(int sockfd) {
	(void)sockfd;
	// Инициализация GTK
	gtk_init(NULL, NULL);

	// Создание окна
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 1000, 600);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	// Установка заголовочной панели
	GtkWidget *header = create_header();
	gtk_window_set_titlebar(GTK_WINDOW(window), header);

	// Обработка закрытия окна
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    	
	//stack creation for login screen and chat screen to be able to exist in the same window
        GtkWidget *stack = gtk_stack_new();
	gtk_container_add(GTK_CONTAINER(window), stack);

 	//creating and adding Login Interface to the Stack
	GtkWidget *login_screen = create_login_interface(stack, sockfd);
	gtk_stack_add_named(GTK_STACK(stack), login_screen, "login");
	
	//creating and adding Sign In Interface to the Stack
	GtkWidget *sign_in_screen = create_sign_in_interface(stack);
	gtk_stack_add_named(GTK_STACK(stack), sign_in_screen, "sign_in"); 

	//creating and adding Chat Interface to the Stack
	GtkWidget *chat_screen = create_chat_interface(stack);
	gtk_stack_add_named(GTK_STACK(stack), chat_screen, "chat");

	//show login screen at the beginning
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "login");

	// Отображение окна
	gtk_widget_show_all(window);

	// Запуск основного цикла обработки событий
	gtk_main();

	return 0;
}

