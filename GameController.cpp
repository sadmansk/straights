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

void GameController::onRageQuit() {
    game_->rageQuit();
}

void GameController::onQuit() {
    game_->quit();
}

void GameController::onPlay(const Card& card) {
    game_->play(card);
}

void GameController::onDiscard(const Card& card) {
    game_->discard(card);
}
