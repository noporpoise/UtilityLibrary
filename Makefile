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
	CFLAGS := $(CFLAGS) -DCAN_USE_NESTED_FUNCTIONS=1

	ifeq ($(shell uname),Darwin)
		CFLAGS := $(CFLAGS) -fnested-functions
	endif
endif

CFLAGS := $(CFLAGS) -Wall -Wextra -Winit-self -Wmissing-include-dirs \
          -Wstrict-aliasing -Wstrict-overflow -Wno-div-by-zero -Wcast-qual \
          -Wcast-align -Wwrite-strings -Wstack-protector

all: clean
	$(CC) $(CFLAGS) -o utility_lib.o -c utility_lib.c
	$(CC) $(CFLAGS) -o mem_size.o -c mem_size.c
	ar -csru libutil.a utility_lib.o mem_size.o
	$(CC) $(CFLAGS) -o utility_test utility_test.c utility_lib.o mem_size.o

clean:
	rm -rf utility_lib.o libutil.a utility_test utility_test.dSYM utility_test.greg
	rm -rf tests
