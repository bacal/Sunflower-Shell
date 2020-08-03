#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>

void bsh_cd(char **dir){
	struct passwd *p;
	char *name;
	//printf("%s",dir[0]);
	char *home = calloc(40,sizeof(char));
	*home = '\0';

	if ((p = getpwuid(getuid())) != NULL){ //gets the uid of the current user and sends it to a struct
		name = p->pw_name;
	}
	else{
		name = calloc(1,sizeof(char));
		name[0]='\0';
	}
	strcat(home,"/home/");
	strcat(home,name);
  
	if(dir[1]!=NULL){
		if(strcmp(dir[1],"~")==0){
			if(!chdir(home)==0){
				printf("bsh: cd: %s: Error, no such directory\n",dir[1]);
			}
		}
		else if(strcmp(dir[1]," ")==0){
			if(!chdir(home)==0){
				printf("bsh: cd: %s: Error, no such directory\n",dir[1]);
			}
		}
		else
			if(chdir(dir[1])!=0){
				printf("bsh: cd: %s: Error, no such directory\n",dir[1]);
		}
	}
	else{
		if(chdir(home)==0);
	}
	free(home);
}
