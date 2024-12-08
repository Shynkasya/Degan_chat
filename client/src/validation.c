#include "client.h"

//function that validates the entries
void validate_sign_up(GtkButton *button, gpointer user_data) {
	(void)button;
	t_sign_up_data *data = (t_sign_up_data *)user_data;

	//set error messages to empty
	gtk_label_set_text(GTK_LABEL(data->error_username_label), "");
	gtk_label_set_text(GTK_LABEL(data->error_email_label), "");
	gtk_label_set_text(GTK_LABEL(data->error_password_label), "");
	gtk_label_set_text(GTK_LABEL(data->error_password_label2), "");

	//validity flag
	bool valid = true;

	//validate username by checking if it only has underscores, letters and numbers
	const char *username = gtk_entry_get_text(GTK_ENTRY(data->username));
	for (size_t i = 0; username[i] != '\0'; i++) {
		if (!mx_isalpha(username[i]) && !mx_isdigit(username[i]) && username[i] != '_') {
			gtk_label_set_text(GTK_LABEL(data->error_username_label), "Username must contain only letters, numbers, and underscores.");
			valid = false;
			
			break;
		}
	}

	//validate email by checking the presence of @ and . symbols
	const char *email = gtk_entry_get_text(GTK_ENTRY(data->email));
	const char *at_sign = mx_strstr(email, "@");
	
	if (!at_sign || at_sign == email || mx_strstr(at_sign + 1, "@")) {
		gtk_label_set_text(GTK_LABEL(data->error_email_label), "Invalid email format.");
		valid = false;
	}
	else {
		const char *dot = mx_strrchr(at_sign + 1, '.');
		
		if (!dot || dot == at_sign + 1 || dot == email + mx_strlen(email) - 1) {
			gtk_label_set_text(GTK_LABEL(data->error_email_label), "Invalid email format.");
			valid = false;
        	}
    	}

	//validate password checking if its long enough and has all of the symbols needed
	const char *password = gtk_entry_get_text(GTK_ENTRY(data->password));
	const char *password_repeat = gtk_entry_get_text(GTK_ENTRY(data->password_repeat));
	
	if (mx_strlen(password) < 8) {
		gtk_label_set_text(GTK_LABEL(data->error_password_label), "Password must be at least 8 characters long.");
		valid = false;
	}
	else {
		int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
		
		for (size_t i = 0; password[i] != '\0'; ++i) {
			if (mx_isupper(password[i])) has_upper = 1;
			if (mx_islower(password[i])) has_lower = 1;
			if (mx_isdigit(password[i])) has_digit = 1;
			if (mx_ispunct(password[i])) has_special = 1;
		}

		if (!has_upper || !has_lower || !has_digit || !has_special) {
			gtk_label_set_text(GTK_LABEL(data->error_password_label), "Password must include uppercase, lowercase, digit, and special character.");
			valid = false;
		}
	}

	//check if password and repeat password fields are equal
	if (strcmp(password, password_repeat) != 0) {
		gtk_label_set_text(GTK_LABEL(data->error_password_label2), "Passwords do not match.");
		valid = false;
	}

	//go back to login screen if everything is valid
	if (valid) {
		printf("Sign-up data is valid. Sending to server...\n");
		
		//hashing password
		char *hashed_password = hash_password(password);
		
		//calling the register function and getting the response from server
		register_user(data->sockfd, username, email, hashed_password);
		receive_response(data->sockfd);
		//go to the login screen
		gtk_stack_set_visible_child_name(GTK_STACK(data->stack), "login");
	}
}

