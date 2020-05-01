#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#define BSH_PREDEFS 2
#define BUFFERSIZE 256
#define BUFFER 64

void bsh_loop(); //prints out the current user's name and hostname
char* bsh_getuserinfo();//gets the user's name, hostname and current dir
char* bsh_getline();//gets a line from stdin and returns a string
char** bsh_split(char*);//reads in a string from bsh_getline, and returns an array of strings
int bsh_process(char**);//parses and process arguements provided from the bsh_split function
void bsh_execute(char**);
void bsh_systemrun(char**);
void bsh_cd(char**);//changes the directory
void bsh_clear();//clears screen


char *predefined[]={"cd","clear"};

int main(int argc, const char **argv){

	bsh_loop();//runs infinite loop

	return 0;
}

void bsh_loop(){

	int condition=1;
	char *args;
	char **bsplt;

	while(condition){
		printf("%s",bsh_getuserinfo());
		args = bsh_getline();
		bsplt = bsh_split(args);
		condition = bsh_process(bsplt);
		free(args);
		free(bsplt);

	}
}

char* bsh_getuserinfo(){
	char *userinfo=malloc(60*sizeof(char));
	char *name = getlogin();//gets the current user's login name
	char *hostname=malloc(25*sizeof(char));//allocates 25 characters to hostname array
	char *cwd = malloc(40*sizeof(char)); //allocates 40 bytes to the
	gethostname(hostname,sizeof(hostname));//gets hostname
	getcwd(cwd,4000);
	sprintf(userinfo,"[%s@%s]:%s$ ",name,hostname,cwd);//prints the user's name, hostname, and current directory
	return userinfo;
}

char* bsh_getline(){
	char *args =NULL;
	size_t size =0;
	getline(&args,&size,stdin); //gets a line from standard input
	return args;
}

int bsh_process(char **args){
	int i=0;
	bool bsh_ran=false;
	for(i=0; i< BSH_PREDEFS; i++){
		if(strcmp(args[0],predefined[i])==0){
				bsh_execute(args); // executes the predefined arguement if it exists
				bsh_ran=true;
			}
		else if (strcmp(args[0],"logoff")==0)
			return 0;
		}

		if(bsh_ran == false){
			bsh_systemrun(args);
		}
	return 1;
}

void bsh_execute(char **args){
	if(strcmp(args[0],"cd")==0)
		bsh_cd(args);
	else if (strcmp(args[0],"clear")==0)
		bsh_clear();
}


char** bsh_split(char *str){
	int i =0;
	char delim[] = " \t\r\t\n\v";
	char **bsplt = malloc(2*BUFFERSIZE*sizeof(char));
	bsplt[i] = strtok(str,delim);
	while(bsplt[i]!=NULL){
			i++;
			bsplt[i] = strtok(NULL,delim);
	}
	return bsplt;
}
