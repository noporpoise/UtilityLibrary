/*
 utility_lib.h
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

#ifndef UTILITY_HEADER_SEEN
#define UTILITY_HEADER_SEEN

#include <stdlib.h>
#include <stdio.h>

//
// Sorting
//

// Sort comparison function on int
int cmp_int(const void *aa, const void *bb);
int cmp_uint(const void *aa, const void *bb);
int cmp_long(const void *aa, const void *bb);
int cmp_ulong(const void *aa, const void *bb);

// Wrapper for qsort_r (GNU/BSD) and qsort_s (Windows)
void sort_r(void *base, size_t nel, size_t width,
            int (*compar)(const void *, const void *, void *), void *arg);

//
// Parsing Integers
//

// parse an int value - exit with some error message if invalid value
long parse_int(char* value, const char* err);

// Returns 1 if whole string is int, 0 otherwise
char parse_entire_int(const char *str, int *result);
char parse_entire_uint(const char *str, unsigned int *result);
char parse_entire_long(const char *str, long *result);
char parse_entire_ulong(const char *str, unsigned long *result);
char parse_entire_longlong(const char *str, long long *result);
char parse_entire_ulonglong(const char *str, unsigned long long *result);

//
// Rounding integers
//

int           round_up_int(int num, int nearest);
unsigned int  round_up_uint(unsigned int num, unsigned int nearest);
long          round_up_long(long num, long nearest);
unsigned long round_up_ulong(unsigned long num, unsigned long nearest);

//
// Formating numbers
//

unsigned int num_of_digits(unsigned long num);

// result must be long enough for result + 1 ('\0'). Max length required is:
// strlen('18,446,744,073,709,551,615')+1 = 27 bytes
// returns pointer to result
char* ulong_to_str(unsigned long num, char* result);

// result must be long enough for result + 1 ('\0'). Max length required is:
// strlen('-9,223,372,036,854,775,808')+1 = 27 bytes
char* long_to_str(long num, char* result);

// result must be long enough for result + 1 ('\0').
// Max length required is: 26+1+decimals+1 = 28+decimals bytes
//   strlen('-9,223,372,036,854,775,808') = 27
//   strlen('.') = 1
//   +1 for \0
char* double_to_str(double num, int decimals, char* str);

// str must be 26 + 3 + 1 + num decimals + 1 = 31+decimals bytes
// breakdown:
//   strlen('18,446,744,073,709,551,615') = 26
//   strlen(' GB') = 3
//   strlen('.') = 1
//   +1 for '\0'
char* bytes_to_str(unsigned long num, int decimals, char* str);

//
// Binary
//

// Convert an int to a string of 0 or 1 characters
// b must be at least 33 characters long
// int_to_binary terminates the string with '\0'
void int_to_binary(int x, char *b);

// Convert a long to a string of 0 or 1 characters
// b must be at least 65 characters long
// long_to_binary terminates the string with '\0'
void long_to_binary(long x, char *b);

//
// Input
//

// Checks if anything is piping in
int stdin_is_ready();

// Make a path same as mkdir -p $dir_path
char mkpath(const char *path, mode_t mode);

/**
 * Returns the size of physical memory (RAM) in bytes.
 * Author:  David Robert Nadeau
 * Site:    http://NadeauSoftware.com/
 * License: Creative Commons Attribution 3.0 Unported License
 *          http://creativecommons.org/licenses/by/3.0/deed.en_US
 */
size_t getMemorySize();


// String methods moved to string_buffer

#endif
