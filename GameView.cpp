#include <cassert>

#include "Command.h"
#include "GameView.h"

// Contructor
GameView::GameView(GameController* controller, Game* game) : Observer(), game_(game), controller_(controller) {
    game_->subscribe(this);
}

// Destructor
GameView::~GameView() {
    game_->unsubscribe(this);
    delete game_;
    delete controller_;
}

void GameView::start() {
    // first we invite all the players
    invitePlayers();

    // run the game
    run();
}

void GameView::run() {
    // game loop
    while (state_ != GameState::GAME_OVER || state_ != GameState::GAME_QUIT) {
        startRound();
        while (state_ != GameState::ROUND_ENDED) {
            if (state_ == GameState::COMPUTER_PLAYER_TURN) {
                controller_->onAITurn();
                controller_->endTurn();
            }
            else if (state_ == GameState::HUMAN_PLAYER_TURN) {
                // do action for the current state
                std::cout << "Cards on the table:" << std::endl;
                std::cout << "Clubs: " << controller_->listClubs() << std::endl;
                std::cout << "Diamonds: " << controller_->listDiamonds() << std::endl;
                std::cout << "Hearts: " << controller_->listHearts() << std::endl;
                std::cout << "Spades: " << controller_->listSpades() << std::endl;

                std::cout << "Your hand: " << controller_->getHand() << std::endl;
                std::cout << "Legal Plays: " << controller_->getLegalPlays() << std::endl;
                while (state_ != GameState::NEXT_TURN) {
                    if (state_ == GameState::ILLEGAL_PLAY) {
                        std::cout << "This is not a legal play." << std::endl;
                    }
                    std::cout << ">";
                    Command instr;
                    // get a command if applicable
                    std::cin >> instr;

                    // act on that instruction
                    switch (instr.type) {
                        case PLAY:
                            controller_->onPlay(instr.card);
                            break;
                        case DISCARD:
                            controller_->onDiscard(instr.card);
                            break;
                        case DECK:
                            std::cout << controller_->onShowDeck() << std::endl;
                            break;
                        case QUIT:
                            controller_->onQuit();
                            break;
                        case RAGEQUIT:
                            controller_->onRageQuit();
                            break;
                        default:
                            break;
                    }
                }
                // go to the next player
                controller_->endTurn();
            }
        }
        // After each round ends:
        for (int i = 0; i < Game::NUM_PLAYERS; i++) {
            std::cout << "Player " << i + 1 << "'s discards: " << controller_->getDiscards(i) << std::endl;
            std::cout << "Player " << i + 1 << "'s score: " << controller_->updateScore(i) << std::endl;
        }
    }
    if (state_ == GameState::GAME_OVER) {
        std::cout << "Player " << game_->winner() << " wins!";
    } // prints nothing if the state was GAME_QUIT
}


void GameView::startRound() {
    int first_player = controller_->onStartRound();

    std::cout << "A new round begins. It's player " << first_player << "'s turn to play." << std::endl;
}

void GameView::update() {
    state_ = game_->getState();
}

void GameView::invitePlayers() {
    for (unsigned int i = 0; i < Game::NUM_PLAYERS; i++) {
        std::cout << "Is player " << i+1 << " a human(h) or a computer(c)?\n>";
        char cmd;
        std::cin >> cmd;
        if (cmd == 'h') {
            controller_->onPlayerAdded(cmd);
        }
        else if (cmd == 'c') {
            controller_->onPlayerAdded(cmd);
        }
        else {
            assert(cmd); // TODO: gotta change how failure or invalidity is handled
        }
    }
}
