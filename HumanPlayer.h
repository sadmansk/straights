#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Card.h"
#include "Player.h"
#include "ComputerPlayer.h"
#include <vector>
#include <string>

class HumanPlayer: public Player{
public:
    virtual std::pair<Card*, std::string> autoPlay(std::vector<Card*> &);   // auto play (does nothing for human players)
    const std::vector<Card*> getHand() const;                               // get the cards in the hand
    const std::vector<Card*> getMoves(const std::vector<Card*>) const;      // get the moves available
    GameState getTurnState() const;                                         // get the type of turn state
};

#endif // HUMANPLAYER_H_
