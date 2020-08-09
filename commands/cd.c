/* cd.c
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
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>

void sunsh_cd(char **dir){
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
				printf("sunsh: cd: %s: Error, no such directory\n",dir[1]);
			}
		}
		else if(strcmp(dir[1]," ")==0){
			if(!chdir(home)==0){
				printf("sunsh: cd: %s: Error, no such directory\n",dir[1]);
			}
		}
		else
			if(chdir(dir[1])!=0){
				printf("sunsh: cd: %s: Error, no such directory\n",dir[1]);
		}
	}
	else{
		if(chdir(home)==0);
	}
	free(home);
}
