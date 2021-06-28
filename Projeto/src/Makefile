CC = gcc
CFLAGS = -std=c99 -fstack-protector-all

SRC = .
OBJ = ../obj

TREE = tree
LIST = list
PROGR = progrlib
SVG = svg
HELPER = helper

.PRECIOUS: $(OBJ)/$(TREE)/ $(OBJ)/$(LIST)/ $(OBJ)/$(PROGR)/ $(OBJ)/$(SVG)/ $(OBJ)/$(HELPER)/


TREEDEPS = $(OBJ)/$(TREE)/kdTree.o $(OBJ)/$(TREE)/binaryTree.o

LISTDEPS = $(OBJ)/$(LIST)/list.o

PROGRDEPS = $(OBJ)/$(PROGR)/progrData.o $(OBJ)/$(PROGR)/building.o $(OBJ)/$(PROGR)/person.o $(OBJ)/$(PROGR)/meteor.o $(OBJ)/$(PROGR)/shadow.o $(OBJ)/$(PROGR)/geo.o $(OBJ)/$(PROGR)/qry.o

SVGDEPS = $(OBJ)/$(SVG)/circle.o $(OBJ)/$(SVG)/inside.o $(OBJ)/$(SVG)/intersect.o $(OBJ)/$(SVG)/line.o $(OBJ)/$(SVG)/rect.o $(OBJ)/$(SVG)/svg.o

HELPERDEPS = $(OBJ)/$(HELPER)/argHelp.o $(OBJ)/$(HELPER)/mathHelp.o $(OBJ)/$(HELPER)/pathHelp.o $(OBJ)/$(HELPER)/stringHelp.o



progr: $(SRC)/main.c $(TREEDEPS) $(LISTDEPS) $(PROGRDEPS) $(SVGDEPS) $(HELPERDEPS)
	$(CC) $(CFLAGS) -g -o $@ $^


$(OBJ):
	-@mkdir $(OBJ)

$(OBJ)/%/: |$(OBJ)
	-@mkdir $@

$(OBJ)/$(TREE)/%.o: $(SRC)/$(TREE)/%.c $(SRC)/$(TREE)/%.h |$(OBJ)/$(TREE)/
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/$(LIST)/%.o: $(SRC)/$(LIST)/%.c $(SRC)/$(LIST)/%.h |$(OBJ)/$(LIST)/
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/$(PROGR)/%.o: $(SRC)/$(PROGR)/%.c $(SRC)/$(PROGR)/%.h |$(OBJ)/$(PROGR)/
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/$(SVG)/%.o: $(SRC)/$(SVG)/%.c $(SRC)/$(SVG)/%.h |$(OBJ)/$(SVG)/
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ)/$(HELPER)/%.o: $(SRC)/$(HELPER)/%.c $(SRC)/$(HELPER)/%.h |$(OBJ)/$(HELPER)/
	$(CC) $(CFLAGS) -c -o $@ $<



PHONY: clean

clean:
	-@rm -rf $(OBJ)
	-@rm -f $(SRC)/progr
