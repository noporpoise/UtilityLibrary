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

void _test_mkpath_sub(const char *path, mode_t mode)
{
  printf("mkpath('%s',%i)\n", path, mode);
  printf("  return %i\n", mkpath(path, mode));
}

void _test_mkpath()
{
  _test_mkpath_sub(".", 0777);
  _test_mkpath_sub("./", 0777);
  _test_mkpath_sub("..", 0777);
  _test_mkpath_sub("../", 0777);
  _test_mkpath_sub("../utility_lib", 0777);
  _test_mkpath_sub("../utility_lib/", 0777);
  _test_mkpath_sub("../utility_lib/tests/first", 0777);
  _test_mkpath_sub("../utility_lib/tests/first/", 0777);
  
  _test_mkpath_sub("/", 0777);
  _test_mkpath_sub("/Users/isaac/c/libs/utility_lib/tests/second", 0777);
  _test_mkpath_sub("/Users/isaac/c/libs/utility_lib/tests/second", 0777);
}

int sort_r_cmp(const void *aa, const void *bb, void *arg)
{
  const int *a = aa;
  const int *b = bb;
  const int *p = arg;

  int cmp = *a - *b;

  return (*a <= *p || *b <= *p) ? cmp : -cmp;
}

void _test_sort_r()
{
  int i;
  #define LEN 18
  int arr[LEN] = {1, 5, 28, 4, 3, 2, 10, 20, 18, 25, 21, 29, 34, 35, 14, 100, 27, 19};

  printf("%i", arr[0]);
  for(i = 0; i < LEN; i++)
    printf(", %i", arr[i]);
  printf("\n");

  int p = 20;

  sort_r(arr, LEN, sizeof(int), sort_r_cmp, &p);

  printf("%i", arr[0]);
  for(i = 0; i < LEN; i++)
    printf(", %i", arr[i]);
  printf("\n");
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

  // Test mkpath
  //_test_mkpath();

  // Test sort_r
  _test_sort_r();

  printf("Done.\n");

  return EXIT_SUCCESS;
}
