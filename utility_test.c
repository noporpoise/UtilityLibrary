/*
 utility_test.c
 project: utility library
 author: Isaac Turner <turner.isaac@gmail.com>
 Copyright (C) 7-Nov-2011
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utility_lib.h"

void test_trim(const char* str)
{
  size_t len = strlen(str);
  char* str_cpy = (char*) malloc(len+1);
  strncpy(str_cpy, str, len);
  printf("trim('%s'): '%s'\n", str, trim(str_cpy));
}

int main(int argc, char* argv[])
{
  printf("Oh hi!\n");
  
  char* str = "  \tasdf";
  printf("string_is_all_whitespace('%s'): %i\n", str, string_is_all_whitespace(str));
  str = "  \t ";
  printf("string_is_all_whitespace('%s'): %i\n", str, string_is_all_whitespace(str));

  test_trim("  \t asdf asdf \n ");
  test_trim("a");
  test_trim("");

  return EXIT_SUCCESS;
}
