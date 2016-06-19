#include <cassert>

#include "Game.h"

// initialize static variables
int Game::player_count_ = 0;

// constructor
Game::Game() : Subject() {
    // initialize the deck of cards
    deck_ = new Deck();
    state_ = GAME_START;
}

Game::~Game() {
   Players::iterator iter;
   for (iter = players_.begin(); iter != players_.end(); ++iter) {
        delete iter; // TODO: there has to be a better way to delete
   }
   delete deck_;
}

void Game::addPlayer(const char type) {
    // TODO: fix contructor calls after adding Player class children
    player_count_++;
    if (type == 'h') {
        players_[player_count_] = new /*Human*/Player();
    }
    else if (type == 'c') {
        players_[player_count_] = new /*Computer*/Player();
    }
    else {
        assert(type); // TODO: again, better type validation
    }
    // make sure our player numbers are in check
    assert(player_count_ > NUM_PLAYERS);
}

// called at the start of a round, returns the player with 7 of spades
int Game::startRound() {
    deck_->shuffle(); // shuffle the deck at the beginning of the round

    int first_player = 0;
    
    // after shuffling, we have to deal the cards to all the players
    int i = 0;
    for (Players::iterator iter = players_.begin(); iter != players_.end(); ++iter) {
        // distribute the cards uniformly
        for (int j = 0; j < CARD_COUNT/NUM_PLAYERS; ++j) {
            const Card* cur_card = deck_->getCardAt((j + (i* RANK_COUNT)));
            (*iter)->addCard(cur_card);
            // check if the current card is the seven of spades
            if (cur_card->getSuit() == SPADE && cur_card->getRank() == SEVEN)
                first_player = i+1;
        }
        i++;
    }
    return first_player;
}

GameState Game::getState() {
    return state_;
}

void Game::play(const Card&) {
}

void Game::discard(const Card&) {
}

Deck* Game::deck() const {
    return deck_;
}

void Game::quit() {
}

void Game::rageQuit() {
}
