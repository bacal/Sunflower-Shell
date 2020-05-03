#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#define HOSTSIZE 1024
#define BSH_PREDEFS 4
#define BUFFERSIZE 256
#define BUFFER 64
void bsh_execute(char**);
void bsh_systemrun(char**);
void bsh_create(char**);//create new files with the name inputted by the user
void bsh_cd(char**);//changes the directory
void bsh_clear();//clears screen
int bsh_cat(char**);//prints out the contents of a file

char *predefined[]={"cd","clear","cat","create"};

char* bsh_getuserinfo(){
	struct passwd *p;
	char *name;
	char *home = malloc(40*sizeof(char));
	char *userinfo=malloc(60*sizeof(char));
	char *hostname=malloc(HOSTSIZE+80*sizeof(char));//allocates hostsize characters to hostname array
	char *cwd = malloc(HOSTSIZE*sizeof(char)); //allocates 40 bytes to the
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
	free(name);
	free(home);
	free(hostname);
	free(cwd);
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

	char delim[] = " \t\r\n\v";
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
