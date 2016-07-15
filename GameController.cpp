#include "GameController.h"

// constructor
GameController::GameController (Game* game) : game_(game) { }

void GameController::onPlayerAdded(const char player_type) {
    game_->addPlayer(player_type); // TODO: implement factory pattern here
}

int GameController::onStartRound() {
    return game_->startRound();
}

Deck* GameController::onShowDeck() {
    return game_->deck();
}

int GameController::onRageQuit() {
    return game_->rageQuit();
}

void GameController::onQuit() {
    game_->quit();
}

std::string GameController::onPlay(Card& card) {
    return game_->play(card);
}

std::string GameController::onDiscard(const Card& card) {
    return game_->discard(card);
}

std::string GameController::onAITurn(){
    return game_->aiTurn();
}

std::string GameController::getHand() const{
    return game_->getHand();
}

std::string GameController::getLegalPlays() const{
    return game_->getLegalPlays();
}

std::string GameController::getDiscards(int player) const{
    return game_->getDiscards(player);
}

std::string GameController::updateScore(int player) {
    return game_->updateScore(player);
}

std::string GameController::listClubs() const {
    return game_->listClubs();
}
std::string GameController::listDiamonds() const {
    return game_->listDiamonds();
}

std::string GameController::listHearts() const {
    return game_->listHearts();
}

std::string GameController::listSpades() const {
    return game_->listSpades();
}

void GameController::endTurn() {
    game_->endTurn();
}

void GameController::endRound() {
    game_->endRound();
}
