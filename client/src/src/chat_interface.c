#include "client.h"

void settings(GtkWidget *widget, gpointer data)
{
	(void)widget;
	g_print("Кнопка нажата! %s\n", (char *)data);
}

GtkWidget *create_chat_interface(GtkWidget *stack){
	(void)stack;
	
	// Создание `GtkPaned` для разделения окна
	GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);

	// Создание `sidebar` (левая часть)
	GtkWidget *sidebar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_widget_set_size_request(sidebar, 250, -1);
	apply_css(sidebar, "* { background-color: #192943; }");

	//кнопки сайдбар
	GtkWidget *button1 = gtk_button_new_with_label("Settings");
	gtk_box_pack_start(GTK_BOX(sidebar), button1, FALSE, FALSE, 0);
	g_signal_connect(button1, "clicked", G_CALLBACK(settings), "Settings");
    
	// Создание `main` (правая часть)
	GtkWidget *main_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	apply_css(main_area, "* { background-color: #E9E4D1; }");
	apply_css(main_area, 
			"* { "
			"background-image: url('assets/pics/light_bg1.png'); "
			"background-size: 15% 25%; "
			"background-repeat: no-repeat; "
			"background-position: center; "
			"}");

	// Добавление `sidebar` и `main` в `GtkPaned`
	gtk_paned_pack1(GTK_PANED(paned), sidebar, FALSE, TRUE);
	gtk_paned_pack2(GTK_PANED(paned), main_area, TRUE, TRUE);

	return paned;
}

