#include "Game.h"

// constructor
Game::Game() : Subject() {
    // initialize the deck of cards
    deck_ = new Deck();
    state_ = GAME_START;
}

Game::~Game() {
   Players::iterator iter;
   for (iter = players_.begin(); iter != players_.end(); ++iter) {
        players_.erase(iter); // TODO: there has to be a better way to clear a set
   }
   delete deck_;
}

void Game::addPlayer(const char type) {
    if (type == 'h') {
        players_.insert(new HumanPlayer());
    }
    else if (type == 'c') {
        players_.insert(new ComputerPlayer());
    }
    else {
        assert(type); // TODO: again, better type validation
    }
}

// called at the start of a round
void Game::startRound() {
    // first we make s
    deck_->shuffle(); // shuffle the deck at the beginning of the round
    
    // after shuffling, we have to deal the cards to all the players
    for (Players::iter iter = players_.begin(), unsigned int i = 0; iter != players_.end(); ++i, ++iter) {
        // distribute the cards uniformly
        for (int j = 0; j < CARD_COUNT/NUM_PLAYERS; ++j) {
            (*i)->addCard(deck_->getCardAt(j + (i*RANK_COUNT)));
        }
    }


}
