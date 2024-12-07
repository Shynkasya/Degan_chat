#include "client.h"

//entry field handler
GtkWidget *create_entry_field(GtkWidget *content, const char *label_text, GtkWidget **entry, GtkWidget **error_label) {
	//label above the entry
	GtkWidget *label = gtk_label_new(label_text);
	apply_css(label, "label { color: #0F1B2E; font-weight: bold; font-size: 14px; }");
	
	//entry itself
	GtkWidget *entry_field = gtk_entry_new();
	gtk_widget_set_size_request(entry_field, 300, -1);
	gtk_widget_set_hexpand(entry_field, FALSE);

	//emptry error label for error handling in validation.c
	GtkWidget *error_lbl = gtk_label_new("");
	gtk_widget_set_halign(error_lbl, GTK_ALIGN_END);
	apply_css(error_lbl, "label { color: red; font-size: 10px; }");

	gtk_box_pack_start(GTK_BOX(content), label, FALSE, FALSE, 2);
	gtk_box_pack_start(GTK_BOX(content), entry_field, FALSE, FALSE, 2);
	gtk_box_pack_start(GTK_BOX(content), error_lbl, FALSE, FALSE, 2);

	if (entry) *entry = entry_field;
	if (error_label) *error_label = error_lbl;

	return entry_field;
}

GtkWidget *create_sign_in_interface(GtkWidget *stack) {
	(void)stack;

	//basic layout
	GtkWidget *grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 1);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 1);

	//header area with logo above
	GtkWidget *header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_set_size_request(header, -1, 80);
	gtk_widget_set_hexpand(header, TRUE);
	apply_css(header,
		"* { "
		"  background-color: #192943; "
		"  background-image: url('assets/pics/logo.png'); "
		"  background-repeat: no-repeat; "
		"  background-position: center; "
		"  background-size: contain; "
		"}");
	gtk_grid_attach(GTK_GRID(grid), header, 0, 0, 1, 1);

	//footer area
	GtkWidget *footer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	apply_css(footer, "* { background-color: #192943; }");
	gtk_widget_set_size_request(footer, -1, 80);
	gtk_widget_set_hexpand(footer, TRUE);
	gtk_grid_attach(GTK_GRID(grid), footer, 0, 2, 1, 1);

	GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_NEVER, GTK_POLICY_NEVER);
	gtk_widget_set_vexpand(scrolled_window, TRUE);
	gtk_widget_set_hexpand(scrolled_window, TRUE);
	apply_css(scrolled_window, "* { background-color: #E9E4D1; }");
	gtk_grid_attach(GTK_GRID(grid), scrolled_window, 0, 1, 1, 1);

	//box in the center for entries and buttons
	GtkWidget *content_wrapper = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_halign(content_wrapper, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(content_wrapper, GTK_ALIGN_CENTER);
	gtk_widget_set_size_request(content_wrapper, 300, -1);
	//main content box
	GtkWidget *content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	apply_css(content, "* { background-color: #E9E4D1; }");
	gtk_box_pack_start(GTK_BOX(content_wrapper), content, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(scrolled_window), content_wrapper);

	//username entry
	GtkWidget *name_entry, *error_username_label;
	create_entry_field(content, "Username:", &name_entry, &error_username_label);

	//email entry
	GtkWidget *mail_entry, *error_email_label;
	create_entry_field(content, "E-mail address:", &mail_entry, &error_email_label);

	//password entry
	GtkWidget *password_entry, *error_password_label;
	create_entry_field(content, "Password:", &password_entry, &error_password_label);
	gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);

	//repeat password entry
	GtkWidget *password_entry2, *error_password_label2;
	create_entry_field(content, "Repeat Password:", &password_entry2, &error_password_label2);
	gtk_entry_set_visibility(GTK_ENTRY(password_entry2), FALSE);

	//layout for two bottom buttons
	GtkWidget *button_grid = gtk_grid_new();
	gtk_widget_set_halign(button_grid, GTK_ALIGN_FILL);
	gtk_widget_set_hexpand(button_grid, TRUE);

	//log in button and label
	GtkWidget *goback_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_widget_set_halign(goback_box, GTK_ALIGN_START);

	GtkWidget *goback_label = gtk_label_new("Return to Log In?");
	apply_css(goback_label, "label { color: #0F1B2E; font-weight: bold; }");

	GtkWidget *login_button = gtk_button_new_with_label("Log in");
	apply_css(login_button, 
		"button { "
		"  background: none; "
		"  border: none; "
		"  color: #0056b3; "
		"  font-weight: bold; "
		"} "
		"button:hover { "
		"  text-decoration: underline; "
		"}");

	gtk_box_pack_start(GTK_BOX(goback_box), goback_label, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(goback_box), login_button, FALSE, FALSE, 5);

	gtk_grid_attach(GTK_GRID(button_grid), goback_box, 0, 0, 1, 1);
	gtk_widget_set_halign(goback_box, GTK_ALIGN_START);
	gtk_widget_set_margin_start(goback_box, 20);

	//sign in button
	GtkWidget *signup_button = gtk_button_new_with_label("Sign In");
	gtk_widget_set_size_request(signup_button, 300, 40);
	apply_css(signup_button,
		"button { "
		"  background-color: #007bff; "
		"  color: #ffffff; "
		"  font-weight: bold; "
		"  border-radius: 5px; "
		"}"
		"button:hover { "
		"  background-color: #0056b3; "
		"}");

	gtk_grid_attach(GTK_GRID(button_grid), signup_button, 1, 0, 1, 1);
	gtk_widget_set_halign(signup_button, GTK_ALIGN_END);
	gtk_widget_set_margin_end(signup_button, 20);

	//add button grid to the content box
	gtk_box_pack_start(GTK_BOX(content), button_grid, FALSE, FALSE, 10);


	//assign everything to a sign_up_data structure
	t_sign_up_data *sign_up_data = g_malloc(sizeof(t_sign_up_data));
	sign_up_data->username = name_entry;
	sign_up_data->email = mail_entry;
	sign_up_data->password = password_entry;
	sign_up_data->password_repeat = password_entry2;
	sign_up_data->error_username_label = error_username_label;
	sign_up_data->error_email_label = error_email_label;
	sign_up_data->error_password_label = error_password_label;
	sign_up_data->error_password_label2 = error_password_label2;
	sign_up_data->stack = stack;
	
	//change to login screen when the login button is pressed
	g_signal_connect(login_button, "clicked", G_CALLBACK(switch_to_login), stack);
	//validate all of the fields when the sign in button is pressed
	g_signal_connect(signup_button, "clicked", G_CALLBACK(validate_sign_up), sign_up_data);

    return grid;
}

void on_signup_button_clicked(GtkButton *button, gpointer user_data) {
    (void)button;

    //extract user data
    t_sign_up_data *data = (t_sign_up_data *)user_data;

    //free memory
    g_free(data->username);
    g_free(data->email);
    g_free(data->password);
    g_free(data->password_repeat);
    g_free(data);
}

