/* sunsh.c
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
#include <signal.h>
#ifdef READLINE
#include <readline/readline.h>
#endif
#include "sunsh.h"
int restart = 0;

void sunsh_sigHandler(int sig_num);
int main(int argc, const char **argv){

	sunsh_loop();//runs infinite loop

	return 0;
}

void sunsh_loop(){
	int condition=1;
	char *command;
	char **bsplt;

	while(condition){
		signal(SIGINT,sunsh_sigHandler);

    char *userinfo = sunsh_getuserinfo(); //gets user's info and returns as a string
		command = sunsh_getline(userinfo); //gets a line from STDIN
		bsplt = sunsh_split(command); //tokenizes and splits the line from STDIN
		condition = sunsh_process(bsplt); //processes the input, executes whenever necessary


    free(command);
		free(bsplt);
		free(userinfo);
	}

}
void sunsh_sigHandler(int sig_num){
	if(sig_num == SIGINT){
		signal(SIGINT,sunsh_sigHandler);
#ifdef READLINE
		rl_clear_history();
#endif
	}

}
