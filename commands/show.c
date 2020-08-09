/* show.c
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

void sunsh_show(char **command){

if(!strcmp(command[1],"c")){
  printf("\n\tSunflower Shell (sunsh)  Copyright (C) 2020  Bacal Mesfin \n\
\tThis program comes with ABSOLUTELY NO WARRANTY; for details type `show w'. \n\
\tThis is free software, and you are welcome to redistribute it \n\
\tunder certain conditions; type `show c' for details.\n\n");
}
}
