CC = gcc
CFLAGS = -std=c99 -fstack-protector-all

SRC = .
OBJ = ../obj

MAINDEPS = $(OBJ)/svg.o $(OBJ)/rect.o $(OBJ)/geo.o $(OBJ)/stringHelp.o $(OBJ)/mathHelp.o

progr: progrest progrdin

progrest: $(SRC)/main.c $(MAINDEPS) $(OBJ)/staticList.o
	$(CC) $(CFLAGS) -o $@ $^

progrdin: $(SRC)/main.c $(MAINDEPS) $(OBJ)/dynamicList.o
	$(CC) $(CFLAGS) -o $@ $^



$(OBJ)/svg.o: $(SRC)/svg/svg.c $(SRC)/svg/svg.h $(SRC)/svg/rect.h
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/svg/svg.c

$(OBJ)/rect.o: $(SRC)/svg/rect.c $(SRC)/svg/rect.h $(SRC)/svg/svg.h
	$(CC) $(CFLAGS) -c -o $@ $<



$(OBJ)/geo.o: $(SRC)/geo/geo.c $(SRC)/geo/geo.h
	$(CC) $(CFLAGS) -c -o $@ $<



$(OBJ)/dynamicList.o: $(SRC)/list/dynamicList.c $(SRC)/list/list.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/staticList.o: $(SRC)/list/staticList.c $(SRC)/list/list.h
	$(CC) $(CFLAGS) -c -o $@ $<



$(OBJ)/stringHelp.o: $(SRC)/helper/stringHelp.c $(SRC)/helper/stringHelp.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/mathHelp.o: $(SRC)/helper/mathHelp.c $(SRC)/helper/mathHelp.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/pathHelp.o: $(SRC)/helper/pathHelp.c $(SRC)/helper/pathHelp.h
	$(CC) $(CFLAGS) -c -o $@ $<

PHONY: clean

clean:
	rm -r $(OBJ)
	rm $(SRC)/progr*

$(shell mkdir -p $(OBJ))