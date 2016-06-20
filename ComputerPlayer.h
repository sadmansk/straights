#ifndef COMPUTERPLAYER_H_
#define COMPUTERPLAYER_H_

#include "Card.h"
#include "Player.h"
#include <vector>
#include <string>

class ComputerPlayer: public Player{
public:
    std::pair<Card*, std::string> autoPlay(std::vector<Card*>);           // Automatically takes its turn
    GameState getTurnState() const;
};


#endif // COMPUTERPLAYER_H_
