CXX = g++
CXXFLAGS = -std=c++11 -Wall -O -g `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJECTS = main.o Deck.o GameView.o Game.o GameController.o PlayerSelections.o Card.o Player.o Subject.o ComputerPlayer.o HumanPlayer.o PlayerGui.o HandGui.o
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

main.o : main.cpp
GameView.o : GameView.h GameView.cpp Game.o Observer.h GameController.o PlayerGui.o PlayerSelections.o
GameController.o : GameController.h GameController.cpp Game.o
Game.o : Game.h Game.cpp Subject.o Deck.o Player.o
PlayerSelections.o : PlayerSelections.cpp PlayerSelections.h
Deck.o : Deck.cpp Deck.h Card.o
Card.o : Card.cpp Card.h
ComputerPlayer.o : ComputerPlayer.cpp ComputerPlayer.h Player.o
HumanPlayer.o : HumanPlayer.cpp HumanPlayer.h Player.o
Player.o : Player.h Player.cpp Game.h
PlayerGui.o : PlayerGui.h PlayerGui.cpp
HandGui.o : HandGui.h HandGui.cpp
Subject.o : Subject.h Subject.cpp

clean :
	rm -rf ${OBJECTS} ${EXEC}
