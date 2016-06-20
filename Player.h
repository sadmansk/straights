#ifndef PLAYER_H_
#define PLAYER_H_

#include "Card.h"
#include <array>
#include <vector>
#include <set>

enum class GameState: unsigned int;

class Player {
public:
    Player();                                       // Default Constructor
    ~Player();
    void addCard(Card*);                      // adds a card to the hand
    GameState playCard(const Card&, std::vector<Card*>&);                     // play a legal card
    GameState discardCard(const Card&, const std::vector<Card*>& );                  // discard a card if no plays can be made
    std::vector<Card*>  legalMoves(const std::vector<Card*>& ) const;            // return a set of legal moves
    Card* find(const Card&) const;     // find a pointer to a card given a suit and rank
    int endRound();                                // ends the round
    int getScore();                                // gets current score of player
    std::vector<Card*> getDiscards() const;        // return the discarded cards
    virtual GameState getTurnState() const = 0;           // returns the turn state type
protected:
    std::set <Card*> hand_;                   // players hand
    std::vector<Card*> discard_;              // discarded cards
    int updateScore();                             // updates score at end of round, clears discard pile
private:
    int score_;                                     // score of player
};

#endif // PLAYER_H_
