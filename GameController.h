#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include "Game.h"

#include <ostream>

// MVC controller class
class GameController {
public:
    GameController (Game*);         // contructor
    // adapter functions from view to model goes here
    void onPlayerAdded(const char); // adds the type of player specified
    int onStartRound();             // starts the round and returns the first player
    Deck* onShowDeck();              // shows the deck
    void onQuit();
    void onRageQuit();
    void onPlay(const Card&);
    void onDiscard(const Card&);

private:
    Game* game_;
};

#endif // GAME_CONTROLLER_H_
