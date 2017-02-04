CC=gcc
LD=gcc
ifdef DEBUG
CFLAGS= -std=c99 -ggdb -Wall
else
CFLAGS= -std=c99 -O3
endif
LIBS= -lm

testArraysStrings: testArraysStrings.o arraysStrings.o vectors.o
	$(LD) -o testArraysStrings testArraysStrings.o arraysStrings.o vectors.o $(LIBS)

arraysStrings.o: arraysStrings.c arraysStrings.h
	$(CC) $(CFLAGS) -o arraysStrings.o -c arraysStrings.c

testArraysStrings.o: testArraysStrings.c
	$(CC) $(CFLAGS) -o testArraysStrings.o -c testArraysStrings.c

vectors.o: vectors.c vectors.h
	$(CC) -o vectors.o -c vectors.c	

clean:
	rm *.o
	rm testArraysStrings


