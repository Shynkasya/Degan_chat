#include "../inc/client.h"
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
	char buffer[256] = {0};
	if (connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
		perror("Connection failed");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	printf("Connection established!\n");
    int operation = 1;
   // int network_order = htonl(operation);
    send(sockfd, &operation, sizeof(operation), 0);
    printf("Sending request...\n");
    json_t *root = json_object();//создаешь пустой объект джсон
    json_object_set_new(root, "login", json_string("Vlad"));//добавляешь поля чар, только через json_object_set
    json_object_set_new(root, "passhash", json_string("fetewyghdfr"));//если нужно инт значение вставить то используй вместо
    															//sjon_string используй json_integer()
    char *json_str = json_dumps(root, JSON_COMPACT);  //вставляешь json формат в строку(char *)

    char *str_new = (char *)json_string_value(json_object_get(root, "login"));//так достаёшь из json формата значеннию по ключу "login"
     																	//если значение по ключу в формате числа то вместо json_string_value используй json_integer_value
    printf("Login: %s\n", str_new);
    printf("%s\n", json_str);
    json_object_clear(root);//удаляешь данные из json, но вроде нужно почитать про json_decref
    printf("Sending json...\n");
    send(sockfd, json_str, strlen(json_str), 0);
    json_decref(root); //опасная хрень, надо с ней разбиратся
    recv(sockfd, buffer, 256, 0);
    if (strcmp(buffer, "false") == 0 ) { printf("Authorization was denied...\n"); }
    if (strcmp(buffer, "true") == 0 ) { printf("Authorizing user...\n"); }
	//calling for a window initialization
	//interface_init(argc, argv);
    
	//printf("Disconect\n");
	close(sockfd);
    return 0;
}

