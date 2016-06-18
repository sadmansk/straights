#include "Player.h"
#include <iostream>
#include <cassert>

Player::Player(){}

void Player::playCard(const Card* card){
    //TODO signed unsigned int comparison??
    for( int i = 0; i < _hand.size(); i++){
        if (_hand[i] == card){
            _hand.erase(_hand.begin() + i);
            return;
        }
    }

    std::cerr << "Playing Card Not In Hand" << std::endl;       // Fail on playing card not in hand, can also check for legality
}

void Player::discardCard(const Card* card){
    playCard(card);                                             // if play changes to check for legality, then must change implementation
    _discard.push_back(card);                                   // Same as play except add to discard pile
}

const Card** Player::legalMoves(const Card* card){
    //TODO I have no idea how to do this rn
}

void Player::updateScore(){
    _score += _discard.size();
    _discard.clear();
    return;
}

void Player::endRound(){
    assert( _hand.size() == 0);                                 // Shouldn't end round if still has cards
    updateScore();
}

int Player::getScore(){
    return _score;
}
