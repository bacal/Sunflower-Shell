/* sunsh_functions.c
 *
 * Copyright 2020 Bacal Mesfin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "sunsh.h"

#define HOSTSIZE 1024
#define sunsh_PREDEFS 3
#define BUFFERSIZE 256
#define BUFFER 64
#define PATH_MAX 4096




char *predefined[]={"cd","cat","create"};

void sunsh_create(char **command){
	int i=1;
	while(command[i]!=NULL){
		FILE* fp = fopen(command[i],"w+");
		fprintf(fp," ");
		fclose(fp);
		i++;
	}
}

void sunsh_systemrun(char **command){
	int pid = fork();
	if(pid==0){
		if(execvp(command[0],command)<0){
			printf("sunsh: %s: command not found\n",command[0]);
			exit(0);
		}
	}
	wait(NULL);
}

char* sunsh_getuserinfo(){
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
	if(getcwd(cwd,PATH_MAX)==NULL){
		strcat(" ",cwd);
	}


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


#ifdef READLINE 
char* sunsh_getline(char *userinfo){

	char *command = readline(userinfo);

	if(command!=NULL){
		add_history(command);
		append_history(strlen(command),"~/.sunsh_history");
	}
	return command;
}
#endif

#ifndef READLINE
char* sunsh_getline(char* userinfo){
	char *command =NULL;
	size_t size =0;
	printf("%s",userinfo);
	if(getline(&command,&size,stdin)<0){ //gets a line from standard input
		free(command);
		command = calloc(6,sizeof(char));
		command[0] = '\0';
		printf("exit\n");
		strcat(command,"exit");
	}
	return command;
}
#endif
int sunsh_process(char **command){
	int i=0;
	bool sunsh_ran=false;

	if(command[0]==NULL){
		return 1;
	}
	for(i=0; i< sunsh_PREDEFS; i++){
		if(strcmp(command[0],predefined[i])==0){
			sunsh_built_in_execute(command); // executes the predefined arguement if it exists
			sunsh_ran=true;
		}
		else if (!strcmp(command[0],"exit"))
			return 0;
	}

	if(sunsh_ran == false){
		sunsh_systemrun(command);
	}
	return 1;
}

void sunsh_built_in_execute(char **command){
	if(strcmp(command[0],"cd")==0)
		sunsh_cd(command);
	else if (strcmp(command[0],"cat")==0)
		sunsh_cat(command);
	else if (strcmp(command[0],"create")==0)
		sunsh_create(command);
}


char** sunsh_split(char *str){
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
