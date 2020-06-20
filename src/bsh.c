#include <stdio.h>
#include <stdlib.h>
#include "bsh.h"

int main(int argc, const char **argv){

	bsh_loop();//runs infinite loop

	return 0;
}

void bsh_loop(){
	int condition=1;
	char *command;
	char **bsplt;

	while(condition){
		char *userinfo = bsh_getuserinfo();
		command = bsh_getline(userinfo);
		bsplt = bsh_split(command);
		condition = bsh_process(bsplt);
		free(command);
		free(bsplt);
		free(userinfo);
	}
}
