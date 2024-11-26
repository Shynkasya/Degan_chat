#include "../inc/server.h"

int Socket(int domain, int type, int protocol) {
	int fd = socket(domain, type, protocol);
	if (fd == -1) {
		perror("socket error");
		exit(EXIT_FAILURE);
	}
	return fd;
}

int port_checker(int argc, char* argv[]){
	if(argc != 2){
		fprintf(stderr, "usage: ./uchat_server [network port]\n");
		exit(-1);
	}
	int port = atoi(argv[1]);
	if (port == 0) exit(-1);
	return port;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
	int res = bind(sockfd, addr, addrlen);
	if (res == -1) {
		perror("bind error");
		exit(EXIT_FAILURE);
	}
	return;
}

void Listen(int sockfd, int backlog) {
	int res = listen(sockfd, backlog);
	if (res == -1) {
		perror("listen error");
		exit(EXIT_FAILURE);
	}
}
void initialise_adress(struct sockaddr_in *address, int port, int domain){
	address->sin_port = htons(port);
	address->sin_family = domain;
	address->sin_addr.s_addr = INADDR_ANY;
}

int connect_to_port(int argc, char* argv[]){
		
	int port = port_checker(argc, argv);
	int sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;
	initialise_adress(&address, port, AF_INET);
	Bind(sockfd, (struct sockaddr*)&address, sizeof(address));
	Listen(sockfd, 10);
	return sockfd;
}
