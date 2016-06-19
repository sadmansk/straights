#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Card.h"
#include "Player.h"
#include <vector>
#include <string>


class HumanPlayer: public Player{
public:
    std::string printHand() const;
    std::string printMoves(const std::vector<const Card*>) const;
};



#endif // HUMANPLAYER_H_