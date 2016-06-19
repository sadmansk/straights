#ifndef COMPUTERPLAYER_H_
#define COMPUTERPLAYER_H_

#include "Card.h"
#include "Player.h"
#include <vector>


class ComputerPlayer: public Player{
public:
    void autoPlay(std::vector<const Card*>);           // Automatically takes its turn
};


#endif // COMPUTERPLAYER_H_
