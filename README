UtilityLib - C Library code for general utility functions

 project: utility_lib
 url: http://github.com/noporpoise/UtilityLibrary/
 author: Isaac Turner <turner.isaac@gmail.com>
 copyright (C) 28-May-2011
 license: GPLv3


== Build ==

To build the test code:

$ make
$ ./utility_test


== How to Use ==

To use in your code, include the following arguments in your gcc command:
 -I PATH/TO/UTILDIR/ PATH/TO/UTILDIR/utility_lib.c

and include in your source code:

include "utility_lib.h"


== Functions ==

//
// Integers
//

// parse an int value - exit with some error message if invalid value
long parse_int(char* c, char* err);

// Returns 1 if whole string is int, 0 otherwise
char parse_entire_int(const char *str, int *result);
char parse_entire_uint(const char *str, unsigned int *result);
char parse_entire_long(const char *str, long *result);
char parse_entire_ulong(const char *str, unsigned long *result);
char parse_entire_longlong(const char *str, long long *result);
char parse_entire_ulonglong(const char *str, unsigned long long *result);

// Sort comparison function on int
int cmp_int(const void *aa, const void *bb);
int cmp_long(const void *aa, const void *bb);

//
// Binary
//

// Convert an int/long to a string of zeros and ones
char* int_to_binary(const int x);
char* long_to_binary(const long x);

//
// Input
//

// Checks if anything is piping in
int stdin_is_ready();
