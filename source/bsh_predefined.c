#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/wait.h>
#define SYS 512

void bsh_cd(char **dire){
	struct passwd *p;
	char *name;
	//printf("%s",dire[0]);
	char *home = malloc(40*sizeof(char));
	if ((p = getpwuid(getuid())) != NULL)
		name = p->pw_name;
	strcpy(home,"/home/");
	strcat(home,name);
	if(dire[1]!=NULL){
		if(strcmp(dire[1],"~")==0){
			if(chdir(home)==0);
		}
		else if(strcmp(dire[1]," ")==0){
			if(chdir(home)==0);
		}

		else
			if(chdir(dire[1])!=0)
			printf("bsh: cd: %s: Error, no such directory\n",dire[1]);
	}
	else{
		if(chdir(home)==0);
	}
	free(home);
}

int bsh_cat(char **command){
	int i=1,count=0, opened = 0;
	if(command[1]==NULL){
		printf("Usage: cat <filename>\n");
		return 1;
	}
	while(command[i]!=NULL){
		count++;
		i++;
	}


	FILE** files = malloc(count*sizeof(FILE));
	for(i=0;i<count;i++){

		files[i] = fopen(command[i+1],"r");
		if(files[i]!=NULL)
			opened++;
		else{
			files[i]=NULL;
			printf("cat: %s: Invalid Filename\n",command[i+1]);
		}
	}
	if(opened>0){
		for(i=0;i<count;i++){
			char text;
			if(files[i]!=NULL){
				while((text = fgetc(files[i]))!=EOF)
					printf("%c",text);
				fclose(files[i]);
			}
		}
	}
	return 0;
}
void bsh_create(char **command){
	int i=1;
	while(command[i]!=NULL){
		FILE* fp = fopen(command[i],"w+");
		fprintf(fp," ");
		fclose(fp);
		i++;
	}
}
void bsh_systemrun(char **command){
	int pid = fork();
	if(pid==0){
		if(execvp(command[0],command)<0){
			printf("bsh: %s: command not found\n",command[0]);
			exit(0);
		}
	}
	wait(NULL);
}
