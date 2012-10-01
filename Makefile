ifdef DEBUG
	CFLAGS := -DDEBUG=1 --debug -g
else
	CFLAGS := -O3
endif

CFLAGS := $(CFLAGS) -Wall -Wextra

all:
	gcc $(CFLAGS) -o utility_lib.o -c utility_lib.c
	ar -csru libutil.a utility_lib.o
	gcc $(CFLAGS) -o utility_test utility_test.c utility_lib.o

clean:
	rm -rf utility_lib.o libutil.a utility_test utility_test.dSYM utility_test.greg
	rm -rf tests
