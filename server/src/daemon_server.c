#include "../inc/server.h"

static void signal_handler(int sig) {
  if (sig == SIGTERM) {
    printf("SIGTERM received\n");
    remove(PID_FILE);
    exit(0);
  }
}

void daemon_server() {
	pid = fork();
	if (pid == -1) { perror("fork"); exit(1); }
	else if (pid == 0) {
		setsid();
		freopen("log.txt", "a", stderr);
		freopen("log.txt", "a", stdout); //всё выводится в log.txt
		setbuf(stdout, NULL);
		setbuf(stderr, NULL);
		printf("==========NEW_SESSION==========\n");
		signal(SIGTERM, signal_handler);
	}
	else {
		exit(0);
	}
}
