#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "bsh.h"

#define HOSTSIZE 1024
#define BSH_PREDEFS 3
#define BUFFERSIZE 256
#define BUFFER 64
#define PATH_MAX 4096




char *predefined[]={"cd","cat","create"};

char* bsh_getuserinfo(){
	struct passwd *p;
	int i=0;
	char *name = calloc(40,sizeof(char));
	char *userinfo=calloc(60,sizeof(char));
	char *hostname=calloc(HOSTSIZE,sizeof(char));//allocates hostsize characters to hostname array
	char *cwd = calloc(PATH_MAX,sizeof(char)); //allocates PATH_MAX bytes to the cwd array
	char **wd_split = calloc(PATH_MAX,sizeof(char));
	char delim[] = "/";

	*name = '\0';
	*cwd = '\0';
	*hostname = '\0';
	*userinfo = '\0';

	if ((p = getpwuid(getuid())) != NULL){ //getpwuid returns a pointer to a struct passwd
		strcpy(name,p->pw_name);
	}

	gethostname(hostname,HOSTSIZE);//gets hostname
	getcwd(cwd,PATH_MAX);//copies the string getcwd to cwd


	wd_split[i] = strtok(cwd,delim);
	while(wd_split[i]!=NULL){
		i++;
		wd_split[i] = strtok(NULL,delim);
	}
	if(i>1){
		if(!strcmp(wd_split[0],"home")&& !strcmp(wd_split[1],name)){
			strcpy(cwd,"~");
		}
		for(int j=2; j<i;j++){
			strcat(cwd,"/");
			strcat(cwd,wd_split[j]);
		}
	}

	sprintf(userinfo,"[%s@%s]:%s$ ",name,hostname,cwd);
	free(name);
	free(hostname);
	free(cwd);
	free(wd_split);
	return userinfo;
}

char* bsh_getline(char *userinfo){
	
	char *command = readline(userinfo);
	
	if(command!=NULL){
		add_history(command);
		append_history(strlen(command),"~/.bsh_history");	
	}
	return command;
}


int bsh_process(char **command){
	int i=0;
	bool bsh_ran=false;
	
	if(command[0]==NULL){
		return 1;
	}
	for(i=0; i< BSH_PREDEFS; i++){
		if(strcmp(command[0],predefined[i])==0){
			bsh_execute(command); // executes the predefined arguement if it exists
			bsh_ran=true;
		}
		else if (!strcmp(command[0],"exit"))
			return 0;
	}

	if(bsh_ran == false){
		bsh_systemrun(command);
	}
	return 1;
}

void bsh_execute(char **command){
	if(strcmp(command[0],"cd")==0)
		bsh_cd(command);
	else if (strcmp(command[0],"cat")==0)
		bsh_cat(command);
	else if (strcmp(command[0],"create")==0)
		bsh_create(command);
}


char** bsh_split(char *str){
	int i =0,size=0;
	char delim[] = " \t\r\n\v";
	char **bsplt = calloc(PATH_MAX,sizeof(char));

	if(str==NULL){
		printf("exit\n");
		exit(0);
	}
	if(!strcmp(str," ")){
		bsplt[0] = NULL;
		return bsplt;
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
