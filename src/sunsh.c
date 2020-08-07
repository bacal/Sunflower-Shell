#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#ifdef READLINE
#include <readline/readline.h>
#endif
#include "sunsh.h"
int restart = 0;

void sunsh_sigHandler(int sig_num);
int main(int argc, const char **argv){

	sunsh_loop();//runs infinite loop

	return 0;
}

void sunsh_loop(){
	int condition=1;
	char *command;
	char **bsplt;

	while(condition){
		signal(SIGINT,sunsh_sigHandler);

    char *userinfo = sunsh_getuserinfo(); //gets user's info and returns as a string
		command = sunsh_getline(userinfo); //gets a line from STDIN
		bsplt = sunsh_split(command); //tokenizes and splits the line from STDIN
		condition = sunsh_process(bsplt); //processes the input, executes whenever necessary


    free(command);
		free(bsplt);
		free(userinfo);
	}

}
void sunsh_sigHandler(int sig_num){
	if(sig_num == SIGINT){
		signal(SIGINT,sunsh_sigHandler);
#ifdef READLINE
		rl_clear_history();
#endif
	}

}
