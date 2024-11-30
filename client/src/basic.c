#include "client.h"

GtkWidget *create_header() {
	// Создание заголовочной панели
	GtkWidget *header = gtk_header_bar_new();
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);

	// Создание контейнера (GtkBox) для иконки и текста
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5); // Горизонтальный контейнер с отступом 5 пикселей

	// Создание текстового ярлыка
	GtkWidget *label = gtk_label_new("HolyChat");
	gtk_widget_set_halign(label, GTK_ALIGN_START); // Выравнивание по левому краю
	gtk_widget_set_margin_start(label, 5);        // Отступ текста от контейнера

	// Создание пользовательской иконки
	GdkPixbuf *icon = gdk_pixbuf_new_from_file("assets/pics/icon.png", NULL); // Загружаем изображение

	// Масштабируем изображение до 40x40 пикселей
	GdkPixbuf *scaled_icon = gdk_pixbuf_scale_simple(icon, 40, 40, GDK_INTERP_BILINEAR);

	// Создаем виджет изображения
	GtkWidget *image = gtk_image_new_from_pixbuf(scaled_icon);

	// Добавляем иконку и текст в контейнер
	gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

	// Освобождаем память для изображений
	g_object_unref(icon);
	g_object_unref(scaled_icon);

	// Добавляем контейнер в заголовочную панель
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), box);

	return header;
}

void apply_css(GtkWidget *widget, const char *css) {
	GtkStyleContext *context = gtk_widget_get_style_context(widget);
	GtkCssProvider *provider = gtk_css_provider_new();
	gtk_css_provider_load_from_data(provider, css, -1, NULL);
	gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	g_object_unref(provider);
}

