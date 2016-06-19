#include <cassert>

#include "GameView.h"

// Contructor
GameView::GameView(GameController* controller, Game* game) : Observer(), game_(game), controller_(controller) {}

// Destructor
GameView::~GameView() {
    delete game_;
    delete controller_;
}

void GameView::start() {
    // first we invite all the players
    invitePlayers();
    
    startRound();
}

void GameView::startRound() {
    int first_player = controller_->onStartRound();

    std::cout << "A new round begins. It's player " << first_player << "'s turn to play." << std::endl;
}

void GameView::update() {
}

void GameView::invitePlayers() {
    for (unsigned int i = 0; i < Game::NUM_PLAYERS; i++) {
        std::cout << "Is player " << i+1 << " a human(h) or a computer(c)?\n>";
        char cmd;
        std::cin >> cmd;
        if (cmd == 'h') {
            controller_->onPlayerAdded(cmd/*human*/);
        }
        else if (cmd == 'c') {
            controller_->onPlayerAdded(cmd/*computer*/);
        }
        else {
            assert(cmd); // TODO: gotta change how failure or invalidity is handled
        }
    }
}
