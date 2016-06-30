#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Card.h"
#include "Player.h"
#include "ComputerPlayer.h"
#include <vector>
#include <string>

class HumanPlayer: public Player{
public:
    virtual std::pair<Card*, std::string> autoPlay(std::vector<Card*> &);
    const std::vector<Card*> getHand() const;
    const std::vector<Card*> getMoves(const std::vector<Card*>) const;
    GameState getTurnState() const;
};

#endif // HUMANPLAYER_H_
