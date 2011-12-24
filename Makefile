ifdef DEBUG
	FLAGS=-DDEBUG=1 --debug
endif

all:
	gcc -o utility_test $(FLAGS) -Wall utility_test.c utility_lib.c

clean:
	if test -e utility_test; then rm utility_test; fi
	for file in $(wildcard *.dSYM); do rm -r $$file; done
	for file in $(wildcard *.greg); do rm $$file; done
