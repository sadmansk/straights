#include "Player.h"
#include "Game.h"
#include <iostream>
#include <cassert>

bool checkLegality(const Card& first, const Card& second){
    std::cout << first;
    return true;

    if(first.getRank() == 6){   //7
        return true;
    }

    if(first.getRank() + 1 == second.getRank() || first.getRank() - 1 == second.getRank()){
        if(first.getSuit() == second.getSuit()){
            return true;
        }
    }

    return false;
}

Player::Player(){
}

Player::~Player() {
    hand_.clear();
}

void Player::addCard(Card* card) {
    hand_.insert(card);
}

Card* Player::find(const Card& card) const{
    std::set<Card*>::iterator iter;
    for(iter = hand_.begin(); iter != hand_.end(); ++iter){
        if((*iter)->getSuit() == card.getSuit() && (*iter)->getRank() == card.getRank()){
            return *iter;
        }
    }

    return nullptr;
}

std::vector<Card*>  Player::getDiscards() const {
    return discard_;
}

GameState Player::playCard(const Card& card, std::vector<Card*>& played_cards){
    std::vector<Card*> legalPlays = legalMoves(played_cards);
    for(unsigned int i = 0; i < legalPlays.size(); i++){
        Card* card_ptr = find(card);
        if(*legalPlays[i] == card){
            hand_.erase(card_ptr);
            played_cards.push_back(card_ptr);
            return GameState::NEXT_TURN;
        }
    }

    return GameState::ILLEGAL_PLAY;
}

GameState Player::discardCard(const Card& card, const std::vector<Card*>& played_cards){
    if(legalMoves(played_cards).size() == 0){
        return GameState::ILLEGAL_PLAY;
    }

    Card* card_ptr = find(card);
    hand_.erase(card_ptr);
    discard_.push_back(card_ptr);                                   // Same as play except add to discard pile
    return GameState::NEXT_TURN;
}

std::vector<Card*> Player::legalMoves(const std::vector<Card*>& played_cards) const {
    std::vector<Card*> legalPlays;

    std::set<Card*>::iterator card;
    for(card = hand_.begin(); card != hand_.end(); ++card){
        for(unsigned int j = 0; j < played_cards.size(); j++){
            legalPlays.push_back(*card);
            break;
        }
    }

    return legalPlays;
}

int Player::updateScore(){
    int increment = 0;
    for(unsigned int i = 0; i < discard_.size(); i++){
        increment+= discard_[i]->getRank() + 1;
    }
    score_ += increment;
    discard_.clear();
    return increment;
}

int Player::endRound(){
    assert( hand_.size() == 0);                                 // Shouldn't end round if still has cards
    return updateScore();
}

int Player::getScore(){
    return score_;
}
