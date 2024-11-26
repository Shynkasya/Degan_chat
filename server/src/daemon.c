#include"../inc/server.h"



void deamonisation(){
	pid_t demonitsa;
	demonitsa = fork();
	if(demonitsa < 0) exit(EXIT_FAILURE);
	if(demonitsa > 0) exit(EXIT_SUCCESS);
	
	umask(0);
	if(setsid() < 0) exit(EXIT_FAILURE);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}
