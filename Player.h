#ifndef PLAYER_H_
#define PLAYER_H_

#include "Card.h"
#include <array>
#include <vector>
#include <unordered_set>
#include <utility>

enum class GameState: unsigned int;

class HumanPlayer;
class Player {
public:
    Player();                                       // Default Constructor
    virtual ~Player();
    Player(Player &);
    void addCard(Card*);                      // adds a card to the hand
    virtual std::pair<Card*, std::string> autoPlay(std::vector<Card*> &) = 0;           // Automatically takes its turn
    GameState playCard(const Card&, std::vector<Card*>&);                     // play a legal card
    GameState discardCard(const Card&, const std::vector<Card*>& );                  // discard a card if no plays can be made
    std::vector<Card*> legalMoves(const std::vector<Card*>& ) const;            // return a set of legal moves
    std::vector< std::pair<Card*,bool> > markedCards(const std::vector<Card*>& ) const;            // return a set of legal moves
    Card* removeFromHand(const Card&);     // find a pointer to a card given a suit and rank
    int getScore();                                // gets current score of player
    std::vector<Card*> getDiscards() const;        // return the discarded cards
    virtual GameState getTurnState() const = 0;           // returns the turn state type
    virtual int updateScore();                             // updates score at end of round, clears discard pile
    //ComputerPlayer* rageQuit();
protected:
    std::vector<Card*> hand_;                   // players hand
    std::vector<Card*> discard_;                // discarded cards
private:
    int score_;                                     // score of player
    bool checkLegality(const Card&, const std::vector<Card*>&) const;   //heloper function to check for legal moves
};

#endif // PLAYER_H_
