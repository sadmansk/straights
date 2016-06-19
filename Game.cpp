#include <cassert>

#include "Game.h"

// initialize static variables
int Game::player_count_ = 0;

// constructor
Game::Game() : Subject() {
    // initialize the deck of cards
    deck_ = new Deck();
    state_ = GameState::GAME_START;
}

Game::~Game() {
   Players::iterator iter;
   for (iter = players_.begin(); iter != players_.end(); ++iter) {
        delete *iter;
   }
   delete deck_;
}

void Game::addPlayer(const char type) {
    // TODO: fix contructor calls after adding Player class children
    player_count_++;
    if (type == 'h') {
        players_[player_count_] = new HumanPlayer();
    }
    else if (type == 'c') {
        players_[player_count_] = new ComputerPlayer();
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

    current_player_ = 0;
    
    // after shuffling, we have to deal the cards to all the players
    int i = 0;
    for (Players::iterator iter = players_.begin(); iter != players_.end(); ++iter) {
        // distribute the cards uniformly
        for (int j = 0; j < CARD_COUNT/NUM_PLAYERS; ++j) {
            const Card* cur_card = deck_->getCardAt((j + (i* RANK_COUNT)));
            (*iter)->addCard(cur_card);
            // check if the current card is the seven of spades
            if (cur_card->getSuit() == SPADE && cur_card->getRank() == SEVEN)
                current_player_ = i+1;
        }
        i++;
    }
    return current_player_;
}

GameState Game::getState() {
    return state_;
}

void Game::endTurn() {
    current_player_ = (current_player_+1)%4;
    state_ = players_[current_player_]->getTurnState();
    notify();
}

void Game::play(const Card& card) {
    state_ = players_[current_player_]->playCard(card, played_cards_);

    notify();
}

void Game::discard(const Card& card) {
    state_ = players_[current_player_]->discardCard(card, played_cards_);
    notify();
}

Deck* Game::deck() const {
    return deck_;
}

void Game::quit() {
    state_ = GameState::GAME_QUIT;
    notify();

    delete this;
}

void Game::rageQuit() {
}
