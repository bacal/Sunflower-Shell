#include <stdio.h>
#include <stdlib.h>

void bsh_loop(); //prints out the current user's name and hostname
char* bsh_getuserinfo();//gets the user's name, hostname and current dir
char* bsh_getline();//gets a line from stdin and returns a string
char** bsh_split(char*);//reads in a string from bsh_getline, and returns an array of strings
int bsh_process(char**);//parses and process arguements provided from the bsh_split function

int main(int argc, const char **argv){

	bsh_loop();//runs infinite loop

	return 0;
}

void bsh_loop(){
	int condition=1;
	char *args;
	char **bsplt;

	while(condition){
		char *userinfo = bsh_getuserinfo();
		printf("%s",userinfo);
		args = bsh_getline();
		bsplt = bsh_split(args);
		condition = bsh_process(bsplt);
		free(args);
		free(bsplt);
		free(userinfo);
	}
}
