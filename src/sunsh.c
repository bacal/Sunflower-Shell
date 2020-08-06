#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#ifdef READLINE
#include <readline/readline.h>
#endif
#include "sunsh.h"
int restart = 0;

void bsh_sigHandler(int sig_num);
int main(int argc, const char **argv){

	bsh_loop();//runs infinite loop

	return 0;
}

void bsh_loop(){
	int condition=1;
	char *command;
	char **bsplt;

	while(condition){
		signal(SIGINT,bsh_sigHandler);
		char *userinfo = bsh_getuserinfo();
		command = bsh_getline(userinfo);	
		bsplt = bsh_split(command);
		condition = bsh_process(bsplt);
		free(command);
		free(bsplt);
		free(userinfo);
	}

}
void bsh_sigHandler(int sig_num){
	if(sig_num == SIGINT){
		signal(SIGINT,bsh_sigHandler);
#ifdef READLINE
		rl_clear_history();
#endif
	}

}
