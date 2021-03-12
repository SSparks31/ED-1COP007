CC = gcc
CFLAGS = -std=c99 -fstack-protector-all

SRC = .
OBJ = ../obj

MAINDEPS = $(OBJ)/progrData.o $(OBJ)/svg.o $(OBJ)/rect.o $(OBJ)/geo.o $(OBJ)/qry.o $(OBJ)/argHelp.o $(OBJ)/mathHelp.o $(OBJ)/pathHelp.o $(OBJ)/stringHelp.o

progr: progrest progrdin

progrest: $(SRC)/main.c $(MAINDEPS) $(OBJ)/staticList.o
	$(CC) $(CFLAGS) -o $@ $^

progrdin: $(SRC)/main.c $(MAINDEPS) $(OBJ)/dynamicList.o
	$(CC) $(CFLAGS) -o $@ $^



$(OBJ):
	mkdir $(OBJ)



$(OBJ)/progrData.o: $(SRC)/progrData/progrData.c $(SRC)/progrData/progrData.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<



$(OBJ)/svg.o: $(SRC)/svg/svg.c $(SRC)/svg/svg.h $(SRC)/svg/rect.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/rect.o: $(SRC)/svg/rect.c $(SRC)/svg/rect.h $(SRC)/svg/svg.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<



$(OBJ)/geo.o: $(SRC)/geo/geo.c $(SRC)/geo/geo.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/qry.o: $(SRC)/qry/qry.c $(SRC)/qry/qry.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<



$(OBJ)/dynamicList.o: $(SRC)/list/dynamicList.c $(SRC)/list/list.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/staticList.o: $(SRC)/list/staticList.c $(SRC)/list/list.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<



$(OBJ)/argHelp.o: $(SRC)/helper/argHelp.c $(SRC)/helper/argHelp.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/stringHelp.o: $(SRC)/helper/stringHelp.c $(SRC)/helper/stringHelp.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/mathHelp.o: $(SRC)/helper/mathHelp.c $(SRC)/helper/mathHelp.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/pathHelp.o: $(SRC)/helper/pathHelp.c $(SRC)/helper/pathHelp.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

PHONY: clean

clean:
	rm -rf $(OBJ)
	rm -f $(SRC)/progrest
	rm -f $(SRC)/progrdin