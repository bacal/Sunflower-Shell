#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


	FILE** files = calloc(count,sizeof(FILE));
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
