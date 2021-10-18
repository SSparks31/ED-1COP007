CC = gcc
CFLAGS = -std=c99 -fstack-protector-all

siguel: main.c circle.o line.o rectangle.o text.o list.o queue.o stack.o geo.o qry.o stringHelp.o pathHelp.o
	$(CC) $(CFLAGS) -g -o $@ $^

circle.o: svg/circle.c svg/circle.h
	$(CC) $(CFLAGS) -c $<
 	
line.o: svg/line.c svg/line.h
	$(CC) $(CFLAGS) -c $<

rectangle.o: svg/rectangle.c svg/rectangle.h
	$(CC) $(CFLAGS) -c $<

text.o: svg/text.c svg/text.h
	$(CC) $(CFLAGS) -c $<

list.o: list/list.c list/list.h 
	$(CC) $(CFLAGS) -c $< 

stack.o: stack/stack.c stack/stack.h
	$(CC) $(CFLAGS) -c $<

queue.o: queue/queue.c queue/queue.h
	$(CC) $(CFLAGS) -c $<

geo.o: siguel_data/geo.c siguel_data/geo.h
	$(CC) $(CFLAGS) -c $<

qry.o: siguel_data/qry.c siguel_data/qry.h
	$(CC) $(CFLAGS) -c $<

stringHelp.o: helper/stringHelp.c helper/stringHelp.h
	$(CC) $(CFLAGS) -c $<

pathHelp.o: helper/pathHelp.c helper/pathHelp.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	-rm -rf *.o
	-rm siguel
