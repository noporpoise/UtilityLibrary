ifdef DEBUG
	CFLAGS := -DDEBUG=1 --debug
else
	CFLAGS := -O3
endif

CFLAGS := $(CFLAGS) -Wall -Wextra

all:
	gcc $(CFLAGS) -o utility_lib.o -c utility_lib.c
	ar -csru libutil.a utility_lib.o
	gcc  $(CFLAGS) -o utility_test utility_test.c utility_lib.o

clean:
	if test -e utility_lib.o; then rm utility_lib.o; fi
	if test -e libutil.a; then rm libutil.a; fi
	if test -e utility_test; then rm utility_test; fi
	for file in $(wildcard *.dSYM); do rm -r $$file; done
	for file in $(wildcard *.greg); do rm $$file; done
