OBJS = main.o rover.o frame.o controlstation.o move.o command.o changesecurity.o sensors.o record.o hash.o sipHash_2_4.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -std=gnu++11 -c $(DEBUG)
LFLAGS = -Wall -L. -lnacl


test: main.o rover.o move.o frame.o command.o controlstation.o changesecurity.o sensors.o record.o hash.o sipHash_2_4.o
	$(CC)  $(OBJS) -o test  

main.o: controlstation.h frame.h rover.h sensors.h changesecurity.h
	$(CC) $(CFLAGS) main.cpp controlstation.cpp frame.cpp rover.cpp sensors.cpp changesecurity.cpp

rover.o: frame.h rover.h command.h move.h
	$(CC) $(CFLAGS) rover.cpp frame.cpp move.cpp command.cpp

frame.o: frame.h
	$(CC) $(CFLAGS) frame.cpp

controlstation.o: controlstation.h frame.h move.h rover.h sensors.h changesecurity.h record.h hash.h
	$(CC) $(CFLAGS) controlstation.cpp  frame.cpp move.cpp rover.cpp sensors.cpp  changesecurity.cpp record.cpp hash.cpp

hash.o: hash.h sipHash_2_4.h
	$(CC) $(CFLAGS) hash.cpp sipHash_2_4.cpp

sipHash_2_4.o:  sipHash_2_4.h
	$(CC) $(CFLAGS) sipHash_2_4.cpp

move.o: move.h command.h
	$(CC) $(CFLAGS) move.cpp command.cpp 	

command.o: command.h
	$(CC) $(CFLAGS) command.cpp 	

sensors.o: sensors.h
	$(CC) $(CFLAGS) sensors.cpp 	

changesecurity.o: changesecurity.h
	$(CC) $(CFLAGS) changesecurity.cpp 

record.o: record.h command.h
	$(CC) $(CFLAGS) record.cpp command.cpp

clean:
	/bin/rm -f test $(OBJS)# DO NOT DELETE
# DO NOT DELETE
