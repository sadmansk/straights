#include <cassert>

#include "Game.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <sstream>

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
    assert(player_count_ < NUM_PLAYERS);
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

std::string Game::play(const Card& card) {
    state_ = players_[current_player_]->playCard(card, played_cards_);
    std::stringstream ss;
    ss << "Player " << current_player_ << " plays " << card;
    notify();
    return ss.str();
}

int Game::winner() const{
    int lowPlayer = 0;
    int lowScore = players_[lowPlayer] -> getScore();
    for(int i = 1; i < player_count_; i++){
        if( lowScore > players_[i]->getScore()){
            lowPlayer = i;
            lowScore = players_[i]->getScore();
        }
    }

    return lowPlayer;
}

std::string Game::discard(const Card& card) {
    state_ = players_[current_player_]->discardCard(card, played_cards_);
    std::stringstream ss;
    ss << "Player " << current_player_ << " discards " << card;
    notify();
    return ss.str();
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
    players_[current_player_] = ((HumanPlayer*) players_[current_player_])->rageQuit();
}

std::string Game::aiTurn() {
    std::pair<const Card*, std::string>  play = ((ComputerPlayer*) players_[current_player_]) -> autoPlay(played_cards_);
    std::stringstream ss;
    ss << "Player " << current_player_ << " " << play.first << " " << play.second;
    notify();
    return ss.str();
}

std::string Game::getHand() const{
    std::set<const Card*> hand = ((HumanPlayer*) players_[current_player_])->getHand();
    std::stringstream ss;
    ss << "Your Hand:";

    std::set<const Card*>::iterator card;
    for(card = hand.begin(); card != hand.end(); ++card){
       ss << " " << **card;
    }
    ss << std::endl;
    return ss.str();
}

std::string Game::getLegalPlays() const{
    std::stringstream ss;
    ss << "Legal Plays:";

    const std::vector<const Card*> legalPlays = ((HumanPlayer*) players_[current_player_])->getMoves(played_cards_);

    for(unsigned int i = 0; i < legalPlays.size(); i++){
        ss << " " << *legalPlays[i];
    }
    ss << std::endl;
    return ss.str();
}

std::string Game::getDiscards(int player) const{
    std::stringstream ss;
    ss << "Player " << player << "\'s discards:";
    const std::vector<const Card*> discards = players_[player]->getDiscards();
    for( unsigned int i = 0; i<discards.size(); i++){
        ss << " " << *discards[i];
    }
    return ss.str();
}
