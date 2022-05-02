CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -Wall

ted: main.c path.o list.o svg.o geo.o qry.o
	$(CC) $(CFLAGS) -g -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

PHONY: clean

clean:
	-rm -rf *.o
	-rm ted