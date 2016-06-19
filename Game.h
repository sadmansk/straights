#ifndef GAME_H_
#define GAME_H_

#include <set>
#include <vector>
#include "Subject.h"
#include "Player.h"
#include "Deck.h"

// declare states of the game
enum GameState {
    MAIN_MENU,
    GAME_START,
    PLAYER_TURN,
    ROUND_ENDED,

    NUM_GAME_STATES
};

// Model class
class Game : public Subject{
public:
    Game();             // contructor
    ~Game();            // destructor
    void startRound();  // called at the beginning of every round
    void addPlayer(const char);   // adds a new player to the game

    // consts
    const static int NUM_PLAYERS = 4;
    
private:
    typedef std::set< Player* > Players;
    Players players_;                   // list of the current players
    Player* current_player_;            // keep track of the current player
    Deck *deck_;                        // stores the main deck
    std::vector<Card> played_cards_;    // we store the values of the cards already played
    GameState state_;
};

#endif // GAME_H_
