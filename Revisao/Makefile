CC = gcc
CFLAGS = -std=c99

main: main.o revisaoEx.o
	$(CC) $(CFLAGS) -o main.exe main.o revisaoEx.o

main.o: main.c revisaoEx.h
	$(CC) $(CFLAGS) -c main.c

revisaoEx.o: revisaoEx.c revisaoEx.h
	$(CC) $(CFLAGS) -c revisaoEx.c

.PHONY: clean
clean:
	rm *.o