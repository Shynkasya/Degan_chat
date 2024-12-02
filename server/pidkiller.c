#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

#define PID_FILE "/tmp/pid_file"

int main() {
      FILE *fp = fopen(PID_FILE, "r");
      if (!fp) {perror("fopen"); exit(1);}

	pid_t pid;
	fscanf(fp, "%d", &pid);
	fclose(fp);
	if (kill(pid, SIGTERM) == 0){
		printf("Daemon killed\n");
	} else {
		perror("kill"); exit(1);
	}
}

