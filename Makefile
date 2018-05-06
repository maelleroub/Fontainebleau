CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2

SRC = list.c queue.c bintree.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

testbintree: ${OBJ}

testbst: ${OBJ} bst.c

testavl: ${OBJ} avl.c

-include ${DEP}

clean:
	rm -f *.o *.d testbintree testbst
