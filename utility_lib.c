/*
 utility_lib.c
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h> // isspace
#include <limits.h> // UINT_MAX etc.
#include <errno.h>
#include <sys/stat.h>
#include <sys/select.h> // used in stdin_is_ready()

#include "utility_lib.h"

/* Utility functions */
long parse_int(char* value, const char* err)
{
  // atoi less dependable than newer strtol (it has no error response!)
  char* strtol_last_char_ptr = value;
  long num = strtol(value, &strtol_last_char_ptr, 10);
  
  // If pointer to end of number string hasn't moved -> error
  if(strtol_last_char_ptr == value)
  {
    fprintf(stderr, err, value);
    exit(-1);
  }
  
  return num;
}

/* parse entire integer */

char parse_entire_int(const char *str, int *result)
{
  size_t len = strlen(str);

  char *strtol_last_char_ptr = (char*)str;
  long tmp = strtol(str, &strtol_last_char_ptr, 10);

  if(tmp > INT_MAX || tmp < INT_MIN || strtol_last_char_ptr != str+len)
  {
    return 0;
  }
  else
  {
    *result = (int)tmp;
    return 1;
  }
}

char parse_entire_uint(const char *str, unsigned int *result)
{
  size_t len = strlen(str);

  char *strtol_last_char_ptr = (char*)str;
  unsigned long tmp = strtoul(str, &strtol_last_char_ptr, 10);

  if(tmp > UINT_MAX || strtol_last_char_ptr != str+len)
  {
    return 0;
  }
  else
  {
    *result = (unsigned int)tmp;
    return 1;
  }
}

char parse_entire_long(const char *str, long *result)
{
  size_t len = strlen(str);

  char *strtol_last_char_ptr = (char*)str;
  long tmp = strtol(str, &strtol_last_char_ptr, 10);

  if(strtol_last_char_ptr == str+len)
  {
    *result = tmp;
    return 1;
  }
  else
  {
    return 0;
  }
}

char parse_entire_ulong(const char *str, unsigned long *result)
{
  size_t len = strlen(str);

  char *strtol_last_char_ptr = (char*)str;
  unsigned long tmp = strtoul(str, &strtol_last_char_ptr, 10);

  if(strtol_last_char_ptr == str+len)
  {
    *result = tmp;
    return 1;
  }
  else
  {
    return 0;
  }
}

char parse_entire_longlong(const char *str, long long *result)
{
  size_t len = strlen(str);

  char *strtol_last_char_ptr = (char*)str;
  long long tmp = strtoll(str, &strtol_last_char_ptr, 10);

  if(strtol_last_char_ptr == str+len)
  {
    *result = tmp;
    return 1;
  }
  else
  {
    return 0;
  }
}

char parse_entire_ulonglong(const char *str, unsigned long long *result)
{
  size_t len = strlen(str);

  char *strtol_last_char_ptr = (char*)str;
  unsigned long long tmp = strtoull(str, &strtol_last_char_ptr, 10);

  if(strtol_last_char_ptr == str+len)
  {
    *result = tmp;
    return 1;
  }
  else
  {
    return 0;
  }
}

/* qsort comparison methods */

int cmp_int(const void *aa, const void *bb)
{
  const int *a = aa, *b = bb;
  return (*a < *b) ? -1 : (*a > *b);
}

int cmp_uint(const void *aa, const void *bb)
{
  const unsigned int *a = aa, *b = bb;
  return (*a < *b) ? -1 : (*a > *b);
}

int cmp_long(const void *aa, const void *bb)
{
  const long *a = aa, *b = bb;
  return (*a < *b) ? -1 : (*a > *b);
}

int cmp_ulong(const void *aa, const void *bb)
{
  const unsigned long *a = aa, *b = bb;
  return (*a < *b) ? -1 : (*a > *b);
}

/* rounding */

#define roundup(type,name) type name(type num, type nearest) \
{\
  return nearest * ((num + nearest - 1) / nearest);\
}

roundup(int,          round_up_int)
roundup(unsigned int, round_up_uint)
roundup(long,         round_up_long)
roundup(unsigned long,round_up_ulong)


unsigned int num_of_digits(unsigned long num)
{
  unsigned long digits;

  for(digits = 1; num > 10; digits++)
    num /= 10;

  return num;
}

void format_ulong(unsigned long num, char* result)
{
  int digits = num_of_digits(num);
  int num_commas = (digits-1) / 3;

  int i;
  char *p = result + digits + num_commas;

  *p = '\0';
  p--;

  for(i = 0; i < digits; i++)
  {
    if(i > 0 && i % 3 == 0)
    {
      *p = ',';
      p--;
    }

    *p = '0' + (num % 10);
    p--;
    num /= 10;
  }
}

void print_formatted_ulong(FILE *stream, unsigned long num)
{
  char str[20];
  format_ulong(num, str);
  fprintf(stream, "%s", str);
}

/* Data size units */

// result should be at least 8 chars long (including '\0')
// bytes_to_str adds \0 at end of string
// ulong_max bytes is 16 EB (Exabytes)
void bytes_to_str(unsigned long num, char* result)
{
  #define UNITS_LEN 7
  char *units[UNITS_LEN] = {"B", "KB", "MB", "GB", "TB", "PB", "EB"};

  unsigned long unit;
  unsigned long num_cpy = num;

  for(unit = 0; num_cpy >= 1024 && unit < UNITS_LEN; unit++)
    num_cpy /= 1024;

  unsigned long bytes_in_unit = 0x1UL << (10 * unit);
  long double num_double = (long double)num / bytes_in_unit;

  sprintf(result, "%.1Lf %s", num_double, units[unit]);
}

/* binary */

// Convert an int to a string of 0 or 1 characters
// b must be at least 33 characters long
// int_to_binary terminates the string with '\0'
void int_to_binary(int x, char *b)
{
  char *p = b;

  unsigned int z;

  for(z = (1 << 31); z > 0; z >>= 1)
  {
    *p++ = (x & z) ? '1' : '0';
  }

  *p = '\0';
}

// Convert a long to a string of 0 or 1 characters
// b must be at least 65 characters long
// long_to_binary terminates the string with '\0'
void long_to_binary(long x, char *b)
{
  char *p = b;

  unsigned long z;

  for(z = (1l << 63); z > 0; z >>= 1)
  {
    *p++ = (x & z) ? '1' : '0';
  }

  *p = '\0';
}

/* Input */

// Checks if anything is piping in
int stdin_is_ready()
{
  fd_set fdset;
  struct timeval timeout;

  FD_ZERO(&fdset);
  FD_SET(fileno(stdin), &fdset);
  timeout.tv_sec = 0;
  timeout.tv_usec = 1; // was 0
    
  return select(1, &fdset, NULL, NULL, &timeout) == 1 ? 1 : 0;
}

// Returns 1 on success, 0 on failure
// Sets errno to ENOTDIR if already exists but is not directory
// Adapted from Jonathan Leffler http://stackoverflow.com/a/675193/431087
char _ensure_dir_exists(const char *path, mode_t mode)
{
  struct stat st;

  if(stat(path, &st) != 0)
  {
    // Directory does not exist   
    return mkdir(path, mode) == 0 ? 1 : 0;
  }
  else if(!S_ISDIR(st.st_mode))
  {
    errno = ENOTDIR;
    return 0;
  }

  return 1;
}

// mkpath - ensure all directories in path exist
// Returns 1 on success, 0 on failure
// Adapted from Jonathan Leffler http://stackoverflow.com/a/675193/431087
char mkpath(const char *path, mode_t mode)
{
  char *copypath = strdup(path);

  size_t i = 0, j = 0;
  char status = 1;

  while(1)
  {
    while(path[i] == '.' || path[i] == '/')
      i++;

    j = i;

    while(path[j] != '.' && path[j] != '/' && path[j] != '\0')
      j++;

    if(i == j)
      break;

    char tmp = copypath[j];

    copypath[j] = '\0';

    if(!(status = _ensure_dir_exists(copypath, mode)))
      break;

    if(tmp == '\0')
      break;

    copypath[j] = tmp;
    i = j + 1;
  }

  free(copypath);

  return status;
}
