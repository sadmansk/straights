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
    virtual void showDeck();            // handles the deck command from the view
    virtual void quit();                // handles the quit command from the view
    virtual void rageQuit();            // handles the ragequit command from the view
    virtual void play(const std::string);// handles the play command from the view
    virtual void discard(const std::string);//handles the discard command from the view
};

#endif // GAME_VIEW_H_
