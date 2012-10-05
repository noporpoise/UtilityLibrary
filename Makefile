ifndef CC
	CC = gcc
endif

ifdef DEBUG
	CFLAGS := -DDEBUG=1 --debug -g
else
	CFLAGS := -O3
endif

# Check if using gcc
ifeq ($(shell $(CC) -v 2>&1 | grep -o gcc | head -1),gcc)
	CFLAGS := $(CFLAGS) -DCAN_USE_NESTED_FUNCTIONS=1 -fnested-functions
endif

CFLAGS := $(CFLAGS) -Wall -Wextra

all:
	$(CC) $(CFLAGS) -o utility_lib.o -c utility_lib.c
	ar -csru libutil.a utility_lib.o
	$(CC) $(CFLAGS) -o utility_test utility_test.c utility_lib.o

clean:
	rm -rf utility_lib.o libutil.a utility_test utility_test.dSYM utility_test.greg
	rm -rf tests
