
# CFLAGS = -g -O0 -Wall -Wextra -pedantic -Werror -std=gnu11

CFLAGS = -g -O0 -std=gnu11
LIBS = 

default:
	gcc $(CFLAGS) cache.c main.c  $(LIBS)

test_dbLL:
	gcc $(CFLAGS) linked_list/node.c linked_list/dbLL.c linked_list/dbLL_tests.c  -o linked_list/dbll.o

test_cache_collision: cache_collision_tests.c cache_collision.c linked_list/dbLL.c linked_list/node.c
	gcc $(CFLAGS) cache_collision_tests.c cache_collision.c linked_list/dbLL.c linked_list/node.c -o cache_collision.o

run:
	./a.out

gdb:
	gdb --args ./a.out

valg:
	valgrind --leak-check=full ./a.out
