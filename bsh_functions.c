#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

void bsh_cd(char **dir){
	char *name = getlogin();
	char *home = malloc(40*sizeof(char));
	strcpy(home,"/home/");
	strcat(home,name);
	if(dir[1]!=NULL){
		if(strcmp(dir[1],"~")==0){
			chdir(home);

		}
    else
      chdir(dir[1]);
	}
  else{
    chdir(home);
  }
  	free(home);
}

void bsh_clear(){
  system("clear");
}

void bsh_systemrun(char **command){
  char *string = malloc(50*sizeof(char));
  strcpy(string,command[0]);
  if(command[1]!=NULL){
    strcat(string," ");
    strcat(string,command[1]);
  }
  system(string);
}
