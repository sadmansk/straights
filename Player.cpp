#include "Player.h"
#include "Game.h"
#include <iostream>
#include <cassert>

bool Player::checkLegality(const Card& first, const std::vector<Card*>& played) const{
    if(played.size() == 0){ //first card must be SEVEN
        if(first.getRank() == SEVEN && first.getSuit() == SPADE){
            return true;
        }
        return false;
    }

    if(first.getRank() == SEVEN){
        return true;
    }

    for (std::vector<Card*>::const_iterator iter = played.begin(); iter != played.end(); ++iter) {
        if(first.getRank() == (*iter)->getRank() - 1 || first.getRank() == (*iter)->getRank() + 1){
            if(first.getSuit() == (*iter)->getSuit()){
                return true;
            }
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
    hand_.push_back(card);
}

Card* Player::removeFromHand(const Card& card) {
    for(std::vector<Card*>::iterator iter = hand_.begin(); iter != hand_.end(); ++iter){
        if(*(*iter) == card){
            Card* card = *iter;
            hand_.erase(iter);
            return card;
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
        if(*legalPlays[i] == card){
            Card* card_ptr = removeFromHand(card);
            if (card_ptr) {
                played_cards.push_back(card_ptr);
                return GameState::NEXT_TURN;
            }
        }
    }

    return GameState::ILLEGAL_PLAY;
}

GameState Player::discardCard(const Card& card, const std::vector<Card*>& played_cards){
    if(legalMoves(played_cards).size() > 0){
        return GameState::ILLEGAL_PLAY;
    }

    Card* card_ptr = removeFromHand(card);
    if (card_ptr) {
        discard_.push_back(card_ptr);                                   // Same as play except add to discard pile
        return GameState::NEXT_TURN;
    }
    return GameState::ILLEGAL_PLAY;
}

std::vector<Card*> Player::legalMoves(const std::vector<Card*>& played_cards) const {
    std::vector<Card*> legalPlays;

    std::vector<Card*>::const_iterator card;
    for(card = hand_.begin(); card != hand_.end(); ++card){
        if (checkLegality(**card, played_cards)) {
            legalPlays.push_back(*card);
        }
    }

    if(played_cards.size() == 0){ // assert exactly one playable card (7 of spades) if first play
        assert( legalPlays.size() == 1 );
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
