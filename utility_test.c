/*
 utility_test.c
 project: utility library
 author: Isaac Turner <turner.isaac@gmail.com>
 Copyright (C) 1-Oct-2012
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h> // EXIT_SUCCESS
#include <stdio.h> // printf

#include "utility_lib.h"

void _test_mkpath(const char *path, mode_t mode)
{
  printf("mkpath('%s',%i)\n", path, mode);
  printf("  return %i\n", mkpath(path, mode));
}

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

  /*
  _test_mkpath(".", 0777);
  _test_mkpath("./", 0777);
  _test_mkpath("..", 0777);
  _test_mkpath("../", 0777);
  _test_mkpath("../utility_lib", 0777);
  _test_mkpath("../utility_lib/", 0777);
  _test_mkpath("../utility_lib/tests/first", 0777);
  _test_mkpath("../utility_lib/tests/first/", 0777);
  
  _test_mkpath("/", 0777);
  _test_mkpath("/Users/isaac/c/libs/utility_lib/tests/second", 0777);
  _test_mkpath("/Users/isaac/c/libs/utility_lib/tests/second", 0777);
  */

  return EXIT_SUCCESS;
}
