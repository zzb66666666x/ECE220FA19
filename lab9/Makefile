CC=gcc
CFLAGS=-g -Wall -Werror -std=c99 -m32

all: records

records: fileio.o
	$(CC) $(CFLAGS) fileio.o -o records
     
records.o: fileio.c
	$(CC) $(CFLAGS) -c fileio.c

clean:
	rm -f records
