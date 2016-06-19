#include "Player.h"
#include <iostream>
#include <cassert>

Player::Player(){}

void Player::addCard(const Card* card) {
    hand_.insert(card);
}

void Player::playCard(const Card* card){
    hand_.erase(card);

    std::cerr << "Playing Card Not In Hand" << std::endl;       // Fail on playing card not in hand, can also check for legality
}

void Player::discardCard(const Card* card){
    playCard(card);                                             // if play changes to check for legality, then must change implementation
    discard_.push_back(card);                                   // Same as play except add to discard pile
}

const Card** Player::legalMoves(const Card* card){
}

void Player::updateScore(){
    score_ += discard_.size();
    discard_.clear();
}

void Player::endRound(){
    assert( hand_.size() == 0);                                 // Shouldn't end round if still has cards
    updateScore();
}

int Player::getScore(){
    return score_;
}

