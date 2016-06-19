#include "Player.h"
#include <iostream>
#include <cassert>

bool checkLegality(const Card& first, const Card& second){
    if(first.getRank() == second.getRank()){
        return true;
    }

    if(first.getRank()+ 1 == second.getRank() || first.getRank() - 1 == second.getRank()){
        if(first.getSuit() == second.getSuit()){
            return true;
        }
    }
}
Player::Player(){}

void Player::addCard(const Card* card) {
    hand_.insert(card);
}

void Player::playCard(const Card* card, std::vector<const Card*> played_cards){
    std::vector<const Card*> legalPlays = legalMoves(played_cards);
    //assert(std::find(legalPlays.begin(), legalPlays.end(), card) != legalMoves.end()); TODO, I have no idea why this pass failed

    hand_.erase(card);
    played_cards.push_back(card);
}

void Player::discardCard(const Card* card, const std::vector<const Card*> played_cards){
    assert(legalMoves(played_cards).size() == 0);
    hand_.erase(card);
    discard_.push_back(card);                                   // Same as play except add to discard pile
}

std::vector<const Card*> Player::legalMoves(const std::vector<const Card*> played_cards){
    std::vector<const Card*> legalPlays;

    std::set<const Card*>::iterator card;
    for(card = hand_.begin(); card != hand_.end(); ++card){
        for(int j = 0; j < played_cards.size(); j++){
            if(checkLegality(**card, *played_cards[j]))
            {
                legalPlays.push_back(*card);
                break;
            }
        }
    }

    return legalPlays;
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
