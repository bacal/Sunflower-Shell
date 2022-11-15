/* sunsh.h
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

#pragma once
#ifndef _SUNSH_H_
#define _SUNSH_H_

void sunsh_loop(); //prints out the current user's name and hostname
char* sunsh_getuserinfo();//gets the user's name, hostname and current dir
char* sunsh_getline(char*);//gets a line from stdin and returns a string
char** sunsh_split(char*);//reads in a string from sunsh_getline, and returns an array of strings
int sunsh_process(char**);//parses and process arguements provided from the sunsh_split function
void sunsh_built_in_execute(char**);
void sunsh_systemrun(char**);
void sunsh_create(char**);//create new files with the name inputted by the user
void sunsh_cd(char**);//changes the directory
int sunsh_cat(char**);//prints out the contents of a file
void sunsh_sigHandler(int);
void sunsh_show(char**); //shows copyright or warranty

#endif /* _SUNSH_H_ */