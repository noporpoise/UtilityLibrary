ifndef CC
	CC = gcc
endif

ifdef DEBUG
	CFLAGS := -DDEBUG=1 --debug -g
else
	CFLAGS := -O3
endif

# Check if using gcc on a mac
ifeq ($(shell $(CC) -v 2>&1 | grep -o gcc | head -1),gcc)
	ifeq ($(shell uname),Darwin)
		CFLAGS := $(CFLAGS) -fnested-functions
	endif
endif

CFLAGS := $(CFLAGS) -Wall -Wextra -Winit-self -Wmissing-include-dirs \
          -Wstrict-aliasing -Wno-div-by-zero -Wcast-qual \
          -Wcast-align -Wwrite-strings -Wstack-protector

all: libutil.a utility_test

libutil.a: utility_lib.o mem_size.o
	ar -csru libutil.a utility_lib.o mem_size.o

utility_test: utility_lib.o mem_size.o
	$(CC) $(CFLAGS) -o utility_test utility_test.c utility_lib.o mem_size.o

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf utility_lib.o libutil.a utility_test utility_test.dSYM utility_test.greg
	rm -rf tests

.PHONY: all clean
