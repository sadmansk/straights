#include "GameController.h"

// constructor
GameController::GameController (Game* game) : game_(game) { }

void GameController::onPlayerAdded(const char player_type) {
    game_->addPlayer(player_type); // TODO: implement factory pattern here
}

int GameController::onStartRound() {
    return game_->startRound();
}
