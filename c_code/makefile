
CFLAGS = -g -O0 -Wall -Wextra -pedantic -Werror -std=gnu11
LIBS = 

default:
	gcc $(CFLAGS) cache.c main.c  $(LIBS)

run:
	./a.out

gdb:
	gdb --args ./a.out

valg:
	valgrind --leak-check=full ./a.out
