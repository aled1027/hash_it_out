
# CFLAGS = -g -O0 -Wall -Wextra -pedantic -Werror -std=gnu11
CFLAGS = -g -O0 -std=gnu11
LIBS = 

default:
	gcc $(CFLAGS) cache.c main.c  $(LIBS)

test_dbLL:
	gcc $(CFLAGS) node.c dbLL.c dbLL_tests.c  $(LIBS) -o dbll.o

run:
	./a.out

gdb:
	gdb --args ./a.out

valg:
	valgrind --leak-check=full ./a.out
