# Makefile for Assignment 1

.PHONY: all clean

all: oss user

oss: oss.o user.o
	gcc -o oss oss.o

oss.o: oss.c
	gcc -c -o oss.o oss.c

user: user.o
	gcc -o user user.o

user.o: user.c
	gcc -c -o user.o user.c

clean:
	/bin/rm -f *.o *~ oss user