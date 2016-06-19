#include "GameController.h"

// constructor
GameController::GameController (Game* game) : game_(game) { }

void GameController::onPlayerAdded(const char player_type) {
    game_->addPlayer(player_type); // TODO: implement factory pattern here
}

int GameController::onStartRound() {
    return game_->startRound();
}

void GameController::onShowDeck() {
    game_->showDeck();
}

void GameController::onRageQuit() {
    game_->rageQuit();
}

void GameController::onQuit() {
    game_->quit();
}

void GameController::onPlay(const std::string& card) {
    game_->playCard(card);
}

void GameController::onDiscard(const std::string& card) {
    game_->discard(card);
}
