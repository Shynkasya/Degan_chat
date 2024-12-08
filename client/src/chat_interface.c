#include "client.h"

// Масив чатів
t_chat chats[5]; // Наприклад, максимум 5 чатів

// Функція для отримання поточного часу
void get_current_time(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

// Функція для відправки повідомлення
void send_message(GtkButton *button, gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    const char *message = gtk_entry_get_text(GTK_ENTRY(entry));

    if (strlen(message) > 0) {
        int chat_index = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(entry), "chat_index"));
        t_chat *chat = &chats[chat_index];

        // Додаємо нове повідомлення
        t_message *new_message = &chat->messages[chat->message_count++];
        new_message->user_id = 1;  // У цьому випадку ID користувача = 1
        strncpy(new_message->text, message, sizeof(new_message->text));
        get_current_time(new_message->timestamp, sizeof(new_message->timestamp));

        // Вставляємо повідомлення у буфер
        GtkTextIter end;
        gtk_text_buffer_get_end_iter(chat->buffer, &end);

        char display_message[512];
        snprintf(display_message, sizeof(display_message), "[%s] User %d: %s\n",
                 new_message->timestamp, new_message->user_id, new_message->text);

        gtk_text_buffer_insert(chat->buffer, &end, display_message, -1);

        // Очищаємо поле введення
        gtk_entry_set_text(GTK_ENTRY(entry), "");
    } else {
        g_print("Поле порожнє!\n");
    }
    (void)button;
}

// Функція для створення інтерфейсу чату
GtkWidget *create_chat_interface(GtkWidget *stack) {
    (void)stack;

    GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);

    // Sidebar
    GtkWidget *sidebar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_size_request(sidebar, 250, -1);
    apply_css(sidebar, "* { background-color: #192943; color: #FFFFFF; }");

    GtkWidget *chat_list = gtk_list_box_new();
    gtk_box_pack_start(GTK_BOX(sidebar), chat_list, TRUE, TRUE, 5);

    // Ініціалізація чатів
    for (int i = 0; i < 5; i++) {
        snprintf(chats[i].name, sizeof(chats[i].name), "Chat %d", i + 1);
        chats[i].chat_view = gtk_text_view_new();
        chats[i].buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chats[i].chat_view));
        chats[i].message_count = 0;

        GtkWidget *row = gtk_label_new(chats[i].name);
        gtk_list_box_insert(GTK_LIST_BOX(chat_list), row, -1);
    }

    // Main Area
    GtkWidget *main_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    apply_css(main_area, "* { background-color: #E9E4D1; }");

    GtkWidget *scroll_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    GtkWidget *chat_view = chats[0].chat_view;  // Вибираємо перший чат
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(chat_view), GTK_WRAP_WORD_CHAR);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(chat_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scroll_window), chat_view);

    gtk_box_pack_start(GTK_BOX(main_area), scroll_window, TRUE, TRUE, 5);

    GtkWidget *entry_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *message_entry = gtk_entry_new();
    GtkWidget *send_button = gtk_button_new_with_label("Send");

    gtk_box_pack_start(GTK_BOX(entry_box), message_entry, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(entry_box), send_button, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(main_area), entry_box, FALSE, FALSE, 5);

    g_object_set_data(G_OBJECT(message_entry), "chat_index", GINT_TO_POINTER(0));

    g_signal_connect(send_button, "clicked", G_CALLBACK(send_message), message_entry);
    g_signal_connect(message_entry, "activate", G_CALLBACK(send_message), message_entry);

    gtk_paned_pack1(GTK_PANED(paned), sidebar, FALSE, TRUE);
    gtk_paned_pack2(GTK_PANED(paned), main_area, TRUE, TRUE);

    return paned;
}

