OBJS = main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall -L. -lnacl


test: main.o
	$(CC)  $(OBJS) -o test $(LFLAGS) 

main.o: crypto_stream_cpp.h
	$(CC) $(CFLAGS) main.cpp

clean:
	/bin/rm -f test $(OBJS)