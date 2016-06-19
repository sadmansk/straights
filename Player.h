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
    void playCard(const Card*, std::vector<const Card*> played_cards);                     // play a legal card
    void discardCard(const Card*, const std::vector<const Card*> );                  // discard a card if no plays can be made
    std::vector<const Card*>  legalMoves(const std::vector<const Card*> ) const;            // return a set of legal moves
    const Card* find(int suit, int rank) const;     // find a pointer to a card given a suit and rank
    int endRound();                                // ends the round
    int getScore();                                // gets current score of player
protected:
    std::set <const Card*> hand_;                   // players hand
    std::vector<const Card*> discard_;              // discarded cards
    int updateScore();                             // updates score at end of round, clears discard pile
private:
    int score_;                                     // score of player
};

#endif // PLAYER_H_
