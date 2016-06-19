#ifndef PLAYER_H_
#define PLAYER_H_

#include "Card.h"
#include <array>
#include <vector>
#include <set>

class Player {
public:
    Player();                                       // Default Constructor
    void addCard(const Card*);                      // adds a card to the hand
    void playCard(const Card*);                     // play a legal card
    void discardCard(const Card*);                  // discard a card if no plays can be made
    const Card** legalMoves(const Card*);            // return a set of legal moves
    void endRound();                                // ends the round
    int getScore();                                // gets current score of player
protected:
    std::set <const Card*> hand_;                // players hand
    void updateScore();                             // updates score at end of round, clears discard pile
private:
    int score_;                                     // score of player
    std::vector<const Card*> discard_;              // discarded cards
};

#endif // PLAYER_H_
