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

#ifdef CAN_USE_NESTED_FUNCTIONS

void sort_r(void *base, size_t nel, size_t width,
            int (*compar)(const void *, const void *, void *), void *arg)
{
  int my_cmp(const void *a, const void *b)
  {
    return compar(a, b, arg);
  }

  qsort(base, nel, width, my_cmp);
}

#else

typedef struct
{
  void *arg;
  int (*compar)(const void *, const void *, void *);
} SortStruct;

int cmp_switch(void *s, const void *aa, const void *bb)
{
  SortStruct *ss = (SortStruct*)s;
  return (ss->compar)(aa, bb, ss->arg);
}

void sort_r(void *base, size_t nel, size_t width,
            int (*compar)(const void *, const void *, void *), void *arg)
{
  #if (defined _GNU_SOURCE || defined __GNU__ || defined __linux__)

    qsort_r(base, nel, width, compar, arg);

  #elif (defined __APPLE__ || defined __MACH__ || defined __DARWIN__ || \
         defined __FREEBSD__ || defined __BSD__ || \
         defined OpenBSD3_1 || defined OpenBSD3_9)
  
    SortStruct tmp = {arg, compar};
    qsort_r(base, nel, width, &tmp, &cmp_switch);
  
  #elif (defined _WIN32 || defined _WIN64 || defined __WINDOWS__)
  
    SortStruct tmp = {arg, compar};
    qsort_s(*base, nel, width, &cmp_switch, &tmp);

  #else
    #error Cannot detect operating system
  #endif
}

#endif

/* Parsing Integers */

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

// parse entire integer

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

/* Rounding Integers */

#define roundup(type,name) type name(type num, type nearest) \
{\
  return nearest * ((num + nearest - 1) / nearest);\
}

roundup(int,          round_up_int)
roundup(unsigned int, round_up_uint)
roundup(long,         round_up_long)
roundup(unsigned long,round_up_ulong)


/* Formating Numbers */

unsigned int num_of_digits(unsigned long num)
{
  unsigned int digits;

  for(digits = 1; num >= 10; digits++)
    num /= 10;

  return digits;
}

// result must be long enough for result + 1 ('\0'). Max length required is:
// strlen('18,446,744,073,709,551,615')+1 = 27
// returns pointer to result
char* ulong_to_str(unsigned long num, char* result)
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

  return result;
}

// result must be long enough for result + 1 ('\0'). Max length required is:
// strlen('-9,223,372,036,854,775,808')+1 = 27
char* long_to_str(long num, char* result)
{
  if(num < 0)
  {
    result[0] = '-';
    ulong_to_str(-num, result+1);
  }
  else
  {
    ulong_to_str(num, result);
  }

  return result;
}

// result must be long enough for result + 1 ('\0').
// Max length required is: 26+1+decimals+1 = 28+decimals bytes
//   strlen('-9,223,372,036,854,775,808') = 27
//   strlen('.') = 1
//   +1 for \0
char* double_to_str(double num, int decimals, char* str)
{
  unsigned long whole_units = (unsigned long)num;
  num -= whole_units;

  ulong_to_str(whole_units, str);

  if(decimals > 0)
  {
    // Horrible hack to save character being overwritten with a leading zero
    // e.g. 12.121 written as '12' then '0.121', giving '10.121', put back '2'
    // '12.121'
    size_t offset = strlen(str);
    char c = str[offset-1];
    sprintf(str+offset-1, "%.*lf", decimals, num);
    str[offset-1] = c;
  }

  return str;
}

// str must be 26 + 3 + 1 + num decimals + 1 = 31+decimals bytes
// breakdown:
//   strlen('18,446,744,073,709,551,615') = 26
//   strlen(' GB') = 3
//   strlen('.') = 1
//   +1 for '\0'
char* bytes_to_str(unsigned long num, int decimals, char* str)
{
  const unsigned int num_unit_sizes = 7;
  char *units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB"};

  unsigned long unit;
  unsigned long num_cpy = num;

  for(unit = 0; num_cpy >= 1024 && unit < num_unit_sizes; unit++)
    num_cpy /= 1024;

  unsigned long bytes_in_unit = 0x1UL << (10 * unit);
  double num_of_units = (double)num / bytes_in_unit;

  double_to_str(num_of_units, decimals, str);
  size_t offset = strlen(str);
  sprintf(str+offset, " %s", units[unit]);

  return str;
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

// Returns -1 on failure
off_t get_file_size(char* filepath)
{
  struct stat st;

  if (stat(filepath, &st) == 0)
      return st.st_size;

  fprintf(stderr, "Error: Cannot determine size of %s: %s\n",
          filepath, strerror(errno));

  return -1;
}
