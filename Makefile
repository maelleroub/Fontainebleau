CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2

SRC = list.c queue.c bintree.c bst.c avl.c btree.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

testbintree: ${OBJ}

testbst: ${OBJ}

testavl: ${OBJ}

testbtree: ${OBJ}

-include ${DEP}

clean:
	rm -f *.o *.d testbintree testbst testavl testbtree
