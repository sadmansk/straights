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
    std::string listClubs() const;
    std::string listDiamonds() const;
    std::string listHearts() const;
    std::string listSpades() const;
    void onAITurn();                // computer player's turn
    std::string getHand() const;    // returns the hand of the current player
    std::string getLegalPlays() const;//returns the legal plays of the current player
    std::string getDiscards(int) const;//returns the discarded cards of the specified player
    // TODO: need some way to get the score of the players

private:
    Game* game_;
};

#endif // GAME_CONTROLLER_H_
