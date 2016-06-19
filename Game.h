#ifndef GAME_H_
#define GAME_H_

#include <set>
#include "Subject.h"

// declare states of the game
enum GameState {

    NUM_GAME_STATES
};

// Model class
class Game : class Subject{
public:
    Game();             // contructor
    ~Game();            // destructor
    
private:
    typedef std::set< Player* > players;
    Players players_;
    Deck *deck_;
    GameState state_;
};

#endif // GAME_H_
