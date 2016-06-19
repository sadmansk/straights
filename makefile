CXX = g++
CXXFLAGS = -std=c++11 -g -Wall
OBJECTS = main.o Deck.o GameView.o Game.o GameController.o Card.o Player.o Subject.o Command.o
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

main.o : main.cpp
GameView.o : GameView.h GameView.cpp Game.o Observer.h GameController.o Command.o
GameController.o : GameController.h GameController.cpp Game.o
Game.o : Game.h Game.cpp Subject.o Deck.o Player.o
Deck.o : Deck.cpp Deck.h Card.o
Card.o : Card.cpp Card.h
Player.o : Player.h Player.cpp
Subject.o : Subject.h Subject.cpp
Command.o: Command.h Command.cpp

clean :
	rm -rf ${OBJECTS} ${EXEC}
