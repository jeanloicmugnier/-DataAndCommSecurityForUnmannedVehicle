OBJS = main.o
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall -L../../C++/ -lnacl


test: main.o
	$(CC)  $(OBJS) -o test $(LFLAGS) 

main.o: crypto_stream.h
	$(CC) $(CFLAGS) main.c

clean:
	/bin/rm -f test $(OBJS)