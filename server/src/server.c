#include"../inc/server.h"

#define PID_FILE "/tmp/pid_file" //временный каталог в который записуется pid демона
int main(int argc, char* argv[]) {

  pid_t pid;
  pid = fork();
  if (pid == -1) { perror("fork"); exit(1); }
  else if (pid == 0) {
    setsid();
    FILE *pid_file = fopen(PID_FILE, "w");
    if (!pid_file) { perror("fopen"); exit(1); }
    fprintf(pid_file, "%d\n", getpid());
    fclose(pid_file);
    DaemonServer(argc, argv);
  }
  else {
    exit(0);
  }
}
