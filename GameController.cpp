#include "GameController.h"

// constructor
GameController::GameController (Game* game) : game_(game) { }

void onPlayerAdded(const char player_type) {
    game_->addPlayer(player_type); // TODO: implement factory pattern here
}
