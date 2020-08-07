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
