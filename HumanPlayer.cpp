#include "HumanPlayer.h"
#include "Game.h"
#include <sstream>

const std::vector<Card *> HumanPlayer::getHand() const{
    return hand_;
}

const std::vector<Card *> HumanPlayer::getMoves(const std::vector<Card*> played_cards) const{
    return legalMoves(played_cards);
}

GameState HumanPlayer::getTurnState() const {
    // return round ended if the hand is empty
    if (hand_.size() == 0) {
        return GameState::ROUND_ENDED;
    }
    return GameState::HUMAN_PLAYER_TURN;
}

std::pair<Card*, std::string> HumanPlayer::autoPlay(std::vector<Card*> & played_cards) {
    throw "HumanPlayer has not been taken over by an AI yet!";
    return {0, 0};
}
