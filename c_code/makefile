
CFLAGS = -g -O0 -Wall -Wextra -pedantic -Werror -std=gnu11
#CFLAGS = -g -O0 -std=gnu11

LIBS = 
default:
	gcc $(CFLAGS) cache.c main.c  $(LIBS)

test_dbLL:
	gcc $(CFLAGS) linked_list/node.c linked_list/dbLL.c linked_list/dbLL_tests.c  $(LIBS) -o linked_list/dbll.o

run:
	./a.out --cache-tests --dbll-tests

gdb:
	gdb --args ./a.out

valg:
	valgrind --leak-check=full ./a.out
