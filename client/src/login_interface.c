#include "client.h"

//function to switch to the chat screen after pressing the log in/sign in button
void switch_to_chat(GtkButton *button, gpointer stack) {
	(void)button;
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "chat");
}

GtkWidget *create_login_interface(GtkWidget *stack) {
	//creating basic layout
	GtkWidget *grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 1);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 1);

	//blue header area with logo
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

	//attaching  header to the layout
	gtk_grid_attach(GTK_GRID(grid), header, 0, 0, 1, 1);

	//blue footer area
	GtkWidget *footer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	apply_css(footer, "* { background-color: #192943; }");
	gtk_widget_set_size_request(footer, -1, 80);
	gtk_widget_set_hexpand(footer, TRUE);
	gtk_grid_attach(GTK_GRID(grid), footer, 0, 2, 1, 1);

	//central area for all of the content
	GtkWidget *content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	apply_css(content, "* { background-color: #E9E4D1; }");
	gtk_widget_set_hexpand(content, TRUE);
	gtk_widget_set_vexpand(content, TRUE);
	gtk_grid_attach(GTK_GRID(grid), content, 0, 1, 1, 1);

	//center box as horizontal box
	GtkWidget *center_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
	gtk_widget_set_halign(center_box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(center_box, GTK_ALIGN_CENTER);
	gtk_box_pack_start(GTK_BOX(content), center_box, TRUE, TRUE, 0);

	//box for an image
	GtkWidget *image_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_widget_set_halign(image_box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(image_box, GTK_ALIGN_CENTER);
	gtk_widget_set_margin_start(image_box, 10);

	//adding image via pixbuf
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("assets/pics/login.png", NULL);
		if (!pixbuf) {
			g_print("Failed to load image: assets/pics/login.png\n");
		}
	      	else {
			GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);
			gtk_box_pack_start(GTK_BOX(image_box), image, FALSE, FALSE, 0);
			g_object_unref(pixbuf); 
		}

	//box for the log in form
	GtkWidget *form_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_widget_set_halign(form_box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(form_box, GTK_ALIGN_CENTER);

	//adding "Username:" label
	GtkWidget *username_label = gtk_label_new("Username:");
	apply_css(username_label, "label { color: #0F1B2E; font-weight: bold; }");

	//adding text field for the username
	GtkWidget *username_entry = gtk_entry_new();
	gtk_widget_set_size_request(username_entry, 300, -1);

	//adding "Password:" label
	GtkWidget *password_label = gtk_label_new("Password:");
	apply_css(password_label, "label { color: #0F1B2E; font-weight: bold; }");
	
	//adding text field for the hidden password
	GtkWidget *password_entry = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
	gtk_widget_set_size_request(password_entry, 300, -1);

	//adding login button
	GtkWidget *login_button = gtk_button_new_with_label("Login");
	
	//adding everything to the form_box
	gtk_box_pack_start(GTK_BOX(form_box), username_label, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(form_box), username_entry, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(form_box), password_label, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(form_box), password_entry, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(form_box), login_button, FALSE, FALSE, 10);

	//adding image_box and form_box to devide the center box in half
	gtk_box_pack_start(GTK_BOX(center_box), image_box, TRUE, TRUE, 10); // Left half
	gtk_box_pack_start(GTK_BOX(center_box), form_box, TRUE, TRUE, 10); // Right half

	//connect login button to the screen switch
	g_signal_connect(login_button, "clicked", G_CALLBACK(switch_to_chat), stack);

	return grid;
}
