UtilityLib - C Library code for general utility functions

project: utility_lib

url: http://github.com/noporpoise/UtilityLibrary/

author: Isaac Turner <turner.isaac@gmail.com>

license: BSD

copyright (C) 1-Oct-2012


Build
=====

To build the test code:

    $ make
    $ ./utility_test

To use in your code, include the following arguments in your gcc command:

    gcc ... -I$UTIL_PATH -L$UTIL_PAH ... -libutil

and include in your source code:

    include "utility_lib.h"

Functions
=========

Integers
--------

parse an int value - exit with some error message if invalid value

    long parse_int(char* value, const char* err);

Returns 1 if whole string is int, 0 otherwise

    char parse_entire_int(const char *str, int *result);
    char parse_entire_uint(const char *str, unsigned int *result);
    char parse_entire_long(const char *str, long *result);
    char parse_entire_ulong(const char *str, unsigned long *result);
    char parse_entire_longlong(const char *str, long long *result);
    char parse_entire_ulonglong(const char *str, unsigned long long *result);

Sort comparison function on int

    int cmp_int(const void *aa, const void *bb);
    int cmp_uint(const void *aa, const void *bb);
    int cmp_long(const void *aa, const void *bb);
    int cmp_ulong(const void *aa, const void *bb);

    int           round_up_int(int num, int nearest);
    unsigned int  round_up_uint(unsigned int num, unsigned int nearest);
    long          round_up_long(long num, long nearest);
    unsigned long round_up_ulong(unsigned long num, unsigned long nearest);

    unsigned int num_of_digits(unsigned long num);

Result must be at least: digits+floor((digits-1)/3)+1
Where digits = num_of_digits(num)
The longest length needed is 27 (assuming ulong max is 2^64)

    void format_ulong(unsigned long num, char* result);

    void print_formatted_ulong(FILE *stream, unsigned long num);

Data size units
---------------

Result should be at least 8 chars long (including '\0')
`bytes_to_str` adds \0 at end of string
ulong_max bytes is 16 EB (Exabytes)

    void bytes_to_str(unsigned long num, char* result);

Binary
------

Convert an int to a string of 0 or 1 characters
`b` must be at least 33 characters long
`int_to_binary` terminates the string with '\0'

    void int_to_binary(int x, char *b);

Convert a long to a string of 0 or 1 characters
`b` must be at least 65 characters long
`long_to_binary` terminates the string with '\0'

    void long_to_binary(long x, char *b);

Input
-----

Checks if anything is piping in

    int stdin_is_ready();

Make a path same as mkdir -p $dir_path

    char mkpath(const char *path, mode_t mode);

License
=======

 Copyright (c) 2012, Isaac Turner
 All rights reserved.

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

Development
===========

Short term goals: none -- please suggest some

I like to hear about how you're using it, what bugs you've found and what
features you'd like to see!  Contact me: Isaac Turner <turner.isaac@gmail>

