#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include "Game.h"

// MVC controller class
class GameController {
public:
    GameController (Game*);         // contructor
    // adapter functions from view to model goes here
    void onPlayerAdded(const char); // adds the type of player specified
    void onShowDeck();
    void onQuit();
    void onRageQuit();

private:
    Game* game_;
};

#endif // GAME_CONTROLLER_H_
