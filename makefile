CXX = g++
CXXFLAGS = -std=c++11 -g -Wall
OBJECTS = main.o Deck.o Card.o
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

main.o : main.cpp
Deck.o : Deck.cpp Deck.h Card.o
Card.o : Card.cpp Card.h

clean :
	rm -rf ${OBJECTS} ${EXEC}
