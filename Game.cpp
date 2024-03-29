#include <cassert>
#include "Game.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "PlayerGui.h"
#include <sstream>
#include <iostream>
// initialize static variables
unsigned int Game::player_count_ = 0;

// constructor
Game::Game() : Subject() {
    // initialize the deck of cards
    deck_ = new Deck();
    state_ = GameState::GAME_START;
    output_.open("GameRecord.txt");
    notify();
}

Game::~Game() {
   for (unsigned int i = 0; i < player_count_; i++) {
       delete players_[i];
   }
   output_.close();
   delete deck_;
}

void Game::addPlayer(const char type) {
    // TODO: fix contructor calls after adding Player class children
    if (type == 'h') {
        players_[player_count_] = new HumanPlayer();
    }
    else if (type == 'c') {
        players_[player_count_] = new ComputerPlayer();
    }
    else {
        assert(type); // TODO: again, better type validation
    }
    player_count_++;

    // make sure our player numbers are in check
    assert(player_count_ <= NUM_PLAYERS);
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
            Card* cur_card = deck_->getCardAt((j + (i* Rank::RANK_COUNT)));
            deck_->off(cur_card);
            (*iter)->addCard(cur_card);
            // check if the current card is the seven of spades
            if (cur_card->getSuit() == SPADE && cur_card->getRank() == SEVEN)
                current_player_ = i+1;
        }
        i++;
    }

    if(state_ == GameState::GAME_START){
        output_ << std::endl << "New Game Has Begun" << std::endl << std:: endl;
    }

    output_ << "New Round Has Begun" << std::endl;
    output_ << std::endl << "Deck:" << std::endl << *deck_ << std::endl;

    state_ = players_[current_player_ - 1]->getTurnState();
    return current_player_;
}

GameState Game::getState() {
    return state_;
}

void Game::endTurn() {
    current_player_ = (current_player_)%4 + 1;
    state_ = players_[current_player_-1]->getTurnState();
    notify();
}

std::string Game::play(Card& card) {
    state_ = players_[current_player_-1]->playCard(card, played_cards_);
    std::stringstream ss;
    if (state_ != GameState::ILLEGAL_PLAY) {
        ss << "Player " << current_player_ << " plays " << card << "." << std::endl;
        deck_->on( &card );
    }
    output_ << ss.str();
    notify();
    return ss.str();
}

std::vector<int> Game::winners() {
    int lowScore = players_[0] -> getScore();
    for(unsigned int i = 1; i < player_count_; i++){
        if( lowScore > players_[i]->getScore()){
            lowScore = players_[i]->getScore();
        }
    }

    std::vector<int> lowPlayers;

    for(unsigned int i = 0; i < player_count_; i++){
        if( lowScore == players_[i]->getScore()){
            lowPlayers.push_back(i+1);
        }
    }

    std::stringstream ss;
    ss << std::endl;
    ss << "Game Has Ended:" << std::endl;
    if(lowPlayers.size() == 1){
        ss << "Player " << lowPlayers[0] << " wins!";
    } else {
        ss << "Players";
        ss << " " << lowPlayers[0];
        for(unsigned int i = 1; i < lowPlayers.size(); i++){
            ss << " and " << lowPlayers[i];
        }
        ss << " wins!";
    }

    output_ << ss.str();
    return lowPlayers;
}

std::string Game::discard(const Card& card) {
    state_ = players_[current_player_-1]->discardCard(card, played_cards_);
    std::stringstream ss;
    if (state_ != GameState::ILLEGAL_DISCARD) {
        ss << "Player " << current_player_ << " discards " << card << "." << std::endl;
    }

    output_ << ss.str();
    notify();
    return ss.str();
}

Deck* Game::deck() const {
    return deck_;
}

void Game::quit() {
    state_ = GameState::GAME_QUIT;
    notify();
}

int Game::rageQuit() {
    Player* temp = players_[current_player_-1];
    players_[current_player_-1] = new ComputerPlayer(*players_[current_player_-1]);
    delete temp;
    state_ = GameState::COMPUTER_PLAYER_TURN;
    notify();
    return current_player_;
}

std::string Game::aiTurn() {
    std::pair<Card*, std::string>  play = ((ComputerPlayer*) players_[current_player_-1]) -> autoPlay(played_cards_);
    std::stringstream ss;
    ss << "Player " << current_player_ << " " << play.second << " " << *play.first << "." << std::endl;
    if(play.second == "plays"){
        deck_->on(play.first);
    }
    notify();
    output_ << ss.str();
    return ss.str();
}

std::vector< std::pair<Card*, bool> > Game::getHand() const{
    std::vector<Card*> hand = ((HumanPlayer*) players_[current_player_-1])->getHand();

    return ((HumanPlayer*) players_[current_player_-1])->markedCards(played_cards_);
}

std::string Game::getLegalPlays() const{
    std::stringstream ss;

    std::vector<Card*> legalPlays = players_[current_player_-1]->legalMoves(played_cards_);

    for(unsigned int i = 0; i < legalPlays.size(); i++){
        ss << " " << *legalPlays[i];
    }
    return ss.str();
}

int Game::getDiscards(int player) const{
    const std::vector<Card*> discards = players_[player]->getDiscards();
    return discards.size();
}

std::string Game::listBySuit( const std::vector<Card*> cards, Suit suit ) const {
    std::stringstream ss;
    std::string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
    int count[RANK_COUNT] = {0};

    for( unsigned int i = 0; i < cards.size(); i++){
        if(cards[i]->getSuit() == suit){
            count[cards[i]->getRank()]++;
        }
    }
    for (unsigned int i = 0; i < RANK_COUNT; i++) {
        for (int j = 0; j < count[i]; j++) {
            ss << " " << ranks[i];
        }
    }
    return ss.str();
}

std::string Game::listClubs() const {  // list all the played clubs
    return listBySuit(played_cards_, CLUB);
}
std::string Game::listDiamonds() const { // list all the played diamonds
    return listBySuit(played_cards_, DIAMOND);
}

std::string Game::listHearts() const { // list all the played hearts
    return listBySuit(played_cards_, HEART);
}

std::string Game::listSpades() const { // list all the played spades
    return listBySuit(played_cards_, SPADE);
}

void Game::reset(const std::vector<char>& players, std::array<PlayerGui*, 4>& player_gui, int seed){
    assert(players.size() == NUM_PLAYERS);

    //clear old players / board
    for (unsigned int i = 0; i < player_count_; i++) {
        if(i < player_count_){
            players_[i]->clearDiscards();
        }
        delete players_[i];
    }

    Deck::rng_seed = seed;
    player_count_ = 0;
    current_player_ = 0;

    played_cards_.clear();

    std::vector<char>::const_iterator player;
    for(player = players.begin();  player != players.end(); player++){
        addPlayer(*player);
        player_gui[player_count_-1]->setPlayer(player_count_);
    }
    state_ = GameState::GAME_START;
    notify();
}

int Game::getScore(int player) const{
    assert(player < NUM_PLAYERS && player >= 0);

    return players_[player]->getScore();
}

int Game::updateScore(int player) {
    std::stringstream ss;
    int oldScore = players_[player]->getScore();
    ss << "Player " << (player + 1) << " : " << oldScore;

    players_[player]->updateScore();
    int newScore = players_[player]->getScore();
    if (newScore >= 80) {
        state_ = GameState::GAME_OVER;
    }
    ss << " + " << (newScore - oldScore) << " = " << newScore << std::endl;
    output_ << ss.str();
    return newScore;
}

void Game::endRound() {
    output_ << "Round Has Ended" << std::endl ;
    played_cards_.clear();
    notify();
}
