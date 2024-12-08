#include "client.h"

//sent json to server
void send_json_request(int sockfd, t_request operation, json_t *json_data) {
	//convert operation number to network bytes and send operation type to server
	
	send(sockfd, &operation, sizeof(operation), 0);

	printf("Operation %d sent to server...\n", operation);
	
	//parse json to string and send it to the server
	char *json_str = json_dumps(json_data, JSON_COMPACT);
	send(sockfd, json_str, strlen(json_str), 0);
	printf("JSON sent: %s\n", json_str);

	free(json_str);
	json_decref(json_data);
}

//login handler to put everything in json
void login(int sockfd, const char *username, const char *password) {
	//create json
	json_t *root = json_object();
	json_object_set(root, "Username", json_string(username));
	json_object_set(root, "Password_Hash", json_string(password));
	
	//send operation with data
	send_json_request(sockfd, LOGIN, root);
}

//sign in handler
void register_user(int sockfd, const char *username, const char *email, const char *password) {
	//create json
	json_t *root = json_object();
	json_object_set(root, "Username", json_string(username));
	json_object_set(root, "Email", json_string(email));
	json_object_set(root, "Password_Hash", json_string(password));

	//send operation with data
	send_json_request(sockfd, REGISTRATION, root);
}

//receive server response
void receive_response(int sockfd) {
	char buffer[256] = {0};
	recv(sockfd, buffer, sizeof(buffer) - 1, 0);
	printf("Server response: %s\n", buffer);
}

