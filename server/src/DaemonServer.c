#include "../inc/server.h"

#define PID_FILE "/tmp/pid_file"

void signal_handler(int sig) {
  if (sig == SIGTERM) {
    printf("SIGTERM received\n");
    remove(PID_FILE);
    exit(0);
  }
}

void DaemonServer(int port) {
  freopen("log.txt", "a", stderr);
    freopen("log.txt", "a", stdout); //всё выводится в log.txt
    signal(SIGTERM, signal_handler);
    printf("Daemon server started on port %d\n", port);

    while (1) {

    }
    exit(0);
}
