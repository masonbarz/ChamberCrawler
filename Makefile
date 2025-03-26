CXX=g++-14.2.0
CXXFLAGS=-std=c++20 -Wall -O -g -MMD -Werror=vla
SOURCES=$(wildcard *.cc)
#OBJECTS = character.o coord.o dragon.o dwarf.o elf.o enemies.o goblin.o grid.o human.o main.o merchant.o orc.o phoenix.o 
#player.o potion.o textdisplay.o tile.o treasure.o troll.o vampire.o werewolf.o
#DEPENDS = ${OBJECTS:.o=.d}
OBJECTS=${SOURCES:.cc=.o}	# .o files depend upon .cc files with same names
DEPENDS=${OBJECTS:.o=.d}	# .d file is list of dependencies for corresponding .cc file
EXEC = cc3k

$(EXEC): ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS)

-include ${DEPENDS} # reads the .d files and reruns dependencies

.PHONY: clean
clean:
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
