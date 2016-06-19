#ifndef GAME_H_
#define GAME_H_

#include <array>
#include <vector>
#include <ostream>
#include "Subject.h"
#include "Player.h"
#include "Deck.h"

// declare states of the game
enum GameState {
    GAME_START,
    NEXT_TURN,
    ILLEGAL_PLAY,
    HUMAN_PLAYER_TURN,
    COMPUTER_PLAYER_TURN,
    ROUND_ENDED,
    GAME_OVER,

    NUM_GAME_STATES
};

// Model class
class Game : public Subject{
public:
    Game();                         // contructor
    ~Game();                        // destructor
    int startRound();               // called at the beginning of every round
    void addPlayer(const char);     // adds a new player to the game
    GameState getState();           // accessor for the game state
    Deck* deck() const;             // accessor for the deck
    void play(const Card&);         // play the given card of the current player
    void discard(const Card&);      // discard the given card of the current player
    void quit();                    // quit the game
    void rageQuit();                // rage quit the current player
    void endTurn();                 // end turn of the current player
    std::string listClubs() const;  // list all the clubs on the table
    std::string listDiamonds() const;// list all diamonds on the table
    std::string listHearts() const; // list all hearts on the table
    std::string listSpades() const; // list all the spades on the table
    std::string getHand() const;    // show the hand of the current player
    std::string getLegalPlays() const;//show the legal plays of the current player

    // consts
    const static int NUM_PLAYERS = 4;
    
private:
    typedef std::array< Player*, NUM_PLAYERS > Players;
    Players players_;                   // list of the current players
    unsigned int current_player_;       // keep track of the current player
    Deck *deck_;                        // stores the main deck
    std::vector<Card> played_cards_;    // we store the values of the cards already played
    GameState state_;
    static int player_count_;
};

#endif // GAME_H_
