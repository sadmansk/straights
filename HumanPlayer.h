#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Card.h"
#include "Player.h"
#include "ComputerPlayer.h"
#include <vector>
#include <string>


class HumanPlayer: public Player{
public:
    ComputerPlayer* rageQuit();
    const std::set<const Card*> getHand() const;
    const std::vector<const Card*> getMoves(const std::vector<const Card*>) const;
    GameState getTurnState() const;
};



#endif // HUMANPLAYER_H_
