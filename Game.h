#ifndef GAME_H_
#define GAME_H_

#include <array>
#include <utility>
#include <vector>
#include <ostream>
#include "Subject.h"
#include "Deck.h"
#include <fstream>


// declare states of the game
enum class GameState: unsigned int {
    GAME_START,
    NEXT_TURN,
    ILLEGAL_PLAY,
    HUMAN_PLAYER_TURN,
    COMPUTER_PLAYER_TURN,
    ROUND_ENDED,
    GAME_OVER,
    GAME_QUIT,
    ILLEGAL_DISCARD,

    NUM_GAME_STATES
};

class Player;
class PlayerGui;

// Model class
class Game : public Subject{
public:
    Game();                         // contructor
    ~Game();                        // destructor
    int startRound();               // called at the beginning of every round
    void addPlayer(const char);     // adds a new player to the game
    GameState getState();           // accessor for the game state
    Deck* deck() const;             // accessor for the deck
    std::string play(Card&);         // play the given card of the current player
    std::string discard(const Card&);      // discard the given card of the current player
    void quit();                    // quit the game
    int rageQuit();                // rage quit the current player
    void endTurn();                 // end turn of the current player
    void endRound();                // end the round
    std::vector<int> winners();             // declares winner
    std::string aiTurn();     // ai play
    std::string listClubs() const;  // list all the clubs on the table
    std::string listDiamonds() const;// list all diamonds on the table
    std::string listHearts() const; // list all hearts on the table
    std::string listSpades() const; // list all the spades on the table
    int getDiscards(int) const; //gets all the discarded cards of a player
    int updateScore(int);       //updates and returns score of player
    std::vector< std::pair<Card*, bool> > getHand() const;   // show the hand of the current player
    std::string getLegalPlays() const;//show the legal plays of the current player
    void reset(const std::vector<char>, std::array<PlayerGui*, 4>&, int); //resets game to group of players

    // consts
    const static int NUM_PLAYERS = 4;

private:
    typedef std::array< Player*, NUM_PLAYERS > Players;
    Players players_;                   // list of the current players
    unsigned int current_player_;       // keep track of the current player
    Deck *deck_;                        // stores the main deck
    std::vector<Card*> played_cards_;    // we store the values of the cards already played
    GameState state_;
    std::string listBySuit(const std::vector<Card*>, Suit) const;
    std::ofstream output_;
    static unsigned int player_count_;
};

#endif // GAME_H_
