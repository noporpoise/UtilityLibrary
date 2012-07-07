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

#include <stdlib.h> // EXIT_SUCCESS
#include <stdio.h> // printf

#include "utility_lib.h"

int main(int argc, char* argv[])
{
  if(argc != 1)
  {
    int i;
    printf("Unused arguments: %s", argv[1]);
    for(i = 2; i < argc; i++) {
      printf(", %s", argv[i]);
    }
    printf("\n");
    exit(EXIT_FAILURE);
  }

  printf("Oh hi!\n");

  return EXIT_SUCCESS;
}
