#include "../inc/client.h"
#include <jansson.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int sockfd;
	struct sockaddr_in client_addr;
	
	if(argc != 3){
		fprintf(stderr, "usage: ./uchat [IP adress] [network port]\n");
		return -1;
	}

    	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        	fprintf(stderr, "Socket creation error\n");
        	return -1;
    	}

   	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(atoi(argv[2]));
	client_addr.sin_addr.s_addr = inet_addr(argv[1]);
	//char buffer[256] = {0};
	if (connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
		perror("Connection failed");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	printf("Connection established!\n");
    int operation = 1;
    int network_order = htonl(operation);
    send(sockfd, &network_order, sizeof(network_order), 0);
    printf("Sending request...\n");
    json_t *root = json_object();
    json_object_set_new(root, "login", json_string("Vlad"));
    json_object_set_new(root, "passhash", json_string("fetewyghdfr"));
    char *json_str = json_dumps(root, JSON_COMPACT);
    printf("%s\n", json_str);
    printf("Sending json...\n");
    send(sockfd, json_str, strlen(json_str), 0);
    json_decref(root);
	//calling for a window initialization
	//interface_init(argc, argv);
    
	printf("Disconect\n");
	close(sockfd);
    return 0;
}

