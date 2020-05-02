#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define HOSTSIZE 1024
#define BSH_PREDEFS 4
#define BUFFERSIZE 256
#define BUFFER 64

void bsh_loop(); //prints out the current user's name and hostname
char* bsh_getuserinfo();//gets the user's name, hostname and current dir
char* bsh_getline();//gets a line from stdin and returns a string
char** bsh_split(char*);//reads in a string from bsh_getline, and returns an array of strings
int bsh_process(char**);//parses and process arguements provided from the bsh_split function
void bsh_execute(char**);
void bsh_systemrun(char**);
void bsh_create(char**);//create new files with the name inputted by the user
void bsh_cd(char**);//changes the directory
void bsh_clear();//clears screen
int bsh_cat(char**);//prints out the contents of a file


char *predefined[]={"cd","clear","cat","create"};

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
	struct passwd *p;
	char *name;
	char *home = malloc(40*sizeof(char));
	char *userinfo=malloc(60*sizeof(char));
	char *hostname=malloc(HOSTSIZE*sizeof(char));//allocates hostsize characters to hostname array
	char *cwd = malloc(40*sizeof(char)); //allocates 40 bytes to the
	if ((p = getpwuid(getuid())) != NULL)
			 name = p->pw_name;
	gethostname(hostname,HOSTSIZE);//gets hostname
	getcwd(cwd,4000);
	strcpy(home,"/home/");
	strcat(home,name);
	if(strcmp(cwd,home)==0)
		strcpy(cwd,"~");
	//bsh_disphome(cwd);

	sprintf(userinfo,"[%s@%s]:%s$ ",name,hostname,cwd);
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
	if(args[0]==NULL){
		return 1;
	}
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
	else if (strcmp(args[0],"cat")==0)
		bsh_cat(args);
	else if (strcmp(args[0],"create")==0)
		bsh_create(args);
}


char** bsh_split(char *str){
	int i =0;

	char delim[] = " \t\r\t\n\v";
	char **bsplt = malloc(10*BUFFERSIZE*sizeof(char));
	if(strcmp(str," ")){
		bsplt[0] = NULL;
	}
	bsplt[i] = strtok(str,delim);
	while(bsplt[i]!=NULL){
			i++;
			bsplt[i] = strtok(NULL,delim);

	}
	return bsplt;
}
