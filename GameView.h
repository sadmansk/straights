#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include <iostream>

#include "Observer.h"
#include "GameController.h"
#include "Game.h"

// View class
class GameView : public Observer {
public:
    GameView(GameController*, Game*);   // contructor
    virtual ~GameView();                // destructor
    virtual void start();               // start the view

private:
	// Observer Pattern: to access model accessors without having to downcast subject
	Game *game_;
	
	// Strategy Pattern member (plus signal handlers)
	GameController *controller_;

    // helper functions
    virtual void invitePlayers();       // invite and add the players
    virtual void startRound();          // start a new round
    virtual void run();                 // run the game loop
    virtual void update();              // Observer pattern: concrete update method
};

#endif // GAME_VIEW_H_
