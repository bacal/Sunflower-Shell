void bsh_loop(); //prints out the current user's name and hostname
char* bsh_getuserinfo();//gets the user's name, hostname and current dir
char* bsh_getline(char*);//gets a line from stdin and returns a string
char** bsh_split(char*);//reads in a string from bsh_getline, and returns an array of strings
int bsh_process(char**);//parses and process arguements provided from the bsh_split function
void bsh_built_in_execute(char**);
void bsh_systemrun(char**);
void bsh_create(char**);//create new files with the name inputted by the user
void bsh_cd(char**);//changes the directory
int bsh_cat(char**);//prints out the contents of a file
void bsh_sigHandler(int);
