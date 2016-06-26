#include "HumanPlayer.h"
#include "Game.h"
#include <sstream>

ComputerPlayer* HumanPlayer::rageQuit(){
    return (ComputerPlayer*)(this);
}

const std::vector<Card *> HumanPlayer::getHand() const{
    return hand_;
}

const std::vector<Card *> HumanPlayer::getMoves(const std::vector<Card*> played_cards) const{
    return legalMoves(played_cards);
}

GameState HumanPlayer::getTurnState() const {
    return GameState::HUMAN_PLAYER_TURN;
}
