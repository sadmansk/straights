#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include "Game.h"

// MVC controller class
class GameController {
public:
    GameController (Game*);         // contructor
    ~GameController();              // destructor

private:
    Game* game_;
    // adapter functions from view to model goes here
};

#endif // GAME_CONTROLLER_H_
