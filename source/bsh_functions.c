#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#define HOSTSIZE 1024
#define BSH_PREDEFS 3
#define BUFFERSIZE 256
#define BUFFER 64
#define PATH_MAX 4096
void bsh_execute(char**);
void bsh_systemrun(char**);
void bsh_create(char**);//create new files with the name inputted by the user
void bsh_cd(char**);//changes the directory
int bsh_cat(char**);//prints out the contents of a file

char *predefined[]={"cd","cat","create"};

char* bsh_getuserinfo(){
	struct passwd *p;
	char *name = calloc(40,sizeof(char));
	char *home = calloc(40,sizeof(char));
	char *userinfo=calloc(60,sizeof(char));
	char *hostname=calloc(HOSTSIZE,sizeof(char));//allocates hostsize characters to hostname array
	char *cwd = calloc(PATH_MAX,sizeof(char)); //allocates PATH_MAX bytes to the cwd array
	*name = '\0';
	if ((p = getpwuid(getuid())) != NULL)
		strcpy(name,p->pw_name);
	gethostname(hostname,HOSTSIZE);//gets hostname
	cwd = getcwd(cwd,4000);
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
	if(getline(&args,&size,stdin)<0){ //gets a line from standard input
		printf("bsh: getline failure, exiting...\n");
		exit(0);
	}
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
		else if (strcmp(args[0],"exit")==0)
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
	else if (strcmp(args[0],"cat")==0)
		bsh_cat(args);
	else if (strcmp(args[0],"create")==0)
		bsh_create(args);
}


char** bsh_split(char *str){
	int i =0,size=0;

	char delim[] = " \t\r\n\v";
	char **bsplt = calloc(10*BUFFERSIZE,sizeof(char));
	if(strcmp(str," ")){
		bsplt[0] = NULL;
	}
	bsplt[i] = strtok(str,delim);
	while(bsplt[i]!=NULL){
		i++;
		bsplt[i] = strtok(NULL,delim);
	}
	while(bsplt[i]!=NULL){
		size = sizeof(bsplt[i]);
		bsplt[i][size]='\0';
		i++;
	}
	return bsplt;
}
