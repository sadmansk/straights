#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include "Game.h"
#include "Card.h"
#include "PlayerGui.h"
#include <array>
#include <vector>
#include <utility>

#include <ostream>

// MVC controller class
class GameController {
public:
    GameController (Game*);                 // contructor
    void onPlayerAdded(const char);         // adds the type of player specified
    int onStartRound();                     // starts the round and returns the first player
    Deck* onShowDeck();                     // shows the deck
    void onQuit();                          // quits the game
    int onRageQuit();                       // rage quits the current player
    std::string onPlay(Card&);              // plays the given card
    std::string onDiscard(const Card&);     // discards the given card
    std::string listClubs() const;          // list all the played clubs
    std::string listDiamonds() const;       // list all the played diamonds
    std::string listHearts() const;         // list all the played hearts
    std::string listSpades() const;         // list all the played spades
    std::string onAITurn();                 // computer player's turn
    std::vector< std::pair<Card*, bool> > getHand() const;    // returns the hand of the current player
    std::string getLegalPlays() const;      //returns the legal plays of the current player
    void endTurn();                         // end turn of the current player
    void endRound();                        // end the current round
    int getDiscards(int) const;             // returns the discarded cards of the specified player
    int updateScore(int);                   // returns the updated score of the specified player
    void reset(const std::vector<char>&, std::array<PlayerGui*, 4>&, int);

private:
    Game* game_;                            // model reference
};

#endif // GAME_CONTROLLER_H
