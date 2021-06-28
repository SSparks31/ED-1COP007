CC = gcc
CFLAGS = -std=c99 -fstack-protector-all

SRC = .
OBJ = ../obj

MAINDEPS = $(OBJ)/progrData.o $(OBJ)/svg.o $(OBJ)/rect.o $(OBJ)/line.o $(OBJ)/circle.o $(OBJ)/intersect.o $(OBJ)/inside.o $(OBJ)/geo.o $(OBJ)/kdTree.o $(OBJ)/binaryTree.o $(OBJ)/argHelp.o $(OBJ)/mathHelp.o $(OBJ)/pathHelp.o $(OBJ)/stringHelp.o

progr: $(SRC)/main.c $(MAINDEPS)
	$(CC) $(CFLAGS) -o $@ $^


$(OBJ):
	-@mkdir $(OBJ)



$(OBJ)/progrData.o: $(SRC)/progrData/progrData.c $(SRC)/progrData/progrData.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/geo.o: $(SRC)/progrData/geo.c $(SRC)/progrData/geo.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/qry.o: $(SRC)/progrData/qry.c $(SRC)/progrData/qry.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<



$(OBJ)/kdTree.o: $(SRC)/tree/kdTree.c $(SRC)/tree/kdTree.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/binaryTree.o: $(SRC)/tree/binaryTree.c $(SRC)/tree/binaryTree.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<



$(OBJ)/svg.o: $(SRC)/svg/svg.c $(SRC)/svg/svg.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/rect.o: $(SRC)/svg/rect.c $(SRC)/svg/rect.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/line.o: $(SRC)/svg/line.c $(SRC)/svg/line.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<	

$(OBJ)/circle.o: $(SRC)/svg/circle.c $(SRC)/svg/circle.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<	

$(OBJ)/intersect.o: $(SRC)/svg/intersect.c $(SRC)/svg/intersect.h |$(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<	

$(OBJ)/inside.o: $(SRC)/svg/inside.c $(SRC)/svg/inside.h |$(OBJ)
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
	-@rm -rf $(OBJ)
	-@rm -f $(SRC)/progr
