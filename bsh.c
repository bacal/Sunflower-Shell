#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUFFERSIZE 256
#define BUFFER 64

void bsh_loop(); //prints out the current user's name and hostname
char* bsh_getline();//gets a line from stdin and returns a string
char** bsh_split(char*);//reads in a string from bsh_getline, and returns an array of strings
int bsh_process(char**);//parses and process arguements provided from the bsh_split function

void bsh_cd(char **str);



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
	char **bsplt;

	while(condition){
	printf("[%s@%s]:%s$ ",name,hostname,cwd);//prints the user's name, hostname, and current directory
		args = bsh_getline();
		bsplt = bsh_split(args);
		condition = bsh_process(bsplt);
		printf("looped");
		free(args);
		free(bsplt);

	}
}

char* bsh_getline(){
	//fflush(stdin);
	char *args =NULL;
	size_t size =0;	
	getline(&args,&size,stdin);
	printf("%s\n",args);
	return args;
}
int bsh_process(char **args){

}

char** bsh_split(char *str){
	int strpos=0;
	int len=0;
	int i=0;
	char** split=malloc(BUFFER*sizeof(char));
	//printf("%d",2*strlen(str)*sizeof(char));
	for(i=0; i<strlen(str); i++){
		if((int)str[i]==32){
			split[len][strpos]='\0';
			len++;
			strpos=0;
		}
		else{
			split[len][strpos]=str[i];
			strpos++;
		}

	}
	printf("len: %d\n",len);
	len++;
	return split;
}
