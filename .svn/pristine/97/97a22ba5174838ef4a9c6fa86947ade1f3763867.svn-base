CC=gcc
CFLAGS=-g -Wall -Werror -std=c99 -m32

all: BTREE

BTREE: pgm.o binarytree.o
	$(CC) $(CFLAGS) pgm.o binarytree.o -o BTREE
     
binarytree.o: binarytree.c
	$(CC) $(CFLAGS) -c binarytree.c
pgm.o: pgm.c
	$(CC) $(CFLAGS) -c pgm.c

clean:
	rm -f BTREE binarytree.o pgm.o
