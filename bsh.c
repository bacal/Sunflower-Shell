#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define ARGS 2
#define BUFFERSIZE 1024

void bsh_loop(); //prints out the current user's name and hostname
char* bsh_getline();//gets a line from stdin and returns a string
int bsh_process(char *args);//parses and process arguements provided from getline

char *knownArgs[ARGS] = {"cd","exit"};// a "list" of known arguements.

int main(int argc, const char **argv){

	bsh_loop();//runs infinite loop

	return 0;
}

void bsh_loop(){
	char *name = getlogin();//gets the current user's login name
	char *hostname=malloc(25*sizeof(char));//allocates 25 characters to hostname array
	char *cwd = malloc(40*sizeof(char));
	gethostname(hostname,sizeof(hostname));//gets hostname
	getcwd(cwd,4000);

	int condition=1;
	char *args;

	while(condition){
		printf("[%s@%s]:%s> ",name,hostname,cwd);//prints the user's name, hostname, and current directory
		args = bsh_getline();
		condition = bsh_process(args);
		
	}
}

char* bsh_getline(){

	char *args = malloc(BUFFERSIZE*sizeof(char));
	char input;
	while(1){
		input = getchar();

			if(input==NULL || input=='\n' || input==EOF){
				return &input;
			}
		return args;
	}
}
int bsh_process(char *args){
	for(int i=0; i<ARGS; i++){
		if(strcmp(args,"exit")==0)
			return 0;
			
	}

}
