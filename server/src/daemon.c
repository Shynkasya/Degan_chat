#include"../inc/server.h"



void deamonization(){
	pid_t demonitsa;
	demonitsa = fork();
	if(demonitsa < 0) exit(EXIT_FAILURE);
	if(demonitsa > 0) exit(EXIT_SUCCESS);
	
	if(setsid() < 0) exit(EXIT_FAILURE);
	//umask(0);
	
}
