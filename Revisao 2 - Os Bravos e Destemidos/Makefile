CC = gcc
CFLAGS = -std=c99 -Wall

SRCDIR = src
OBJDIR = obj

$(SRCDIR)/t1: $(OBJDIR)/main.o $(OBJDIR)/argparse.o $(OBJDIR)/path.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR):
	mkdir obj

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean remove
clean:
	rm -r obj

remove: clean
	rm $(SRCDIR)/t1