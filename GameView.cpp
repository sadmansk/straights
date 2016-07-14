#include <cassert>

#include "Command.h"
#include "GameView.h"

// Contructor
GameView::GameView(GameController* controller, Game* game) :
        Observer(),
        game_(game),
        controller_(controller),
        panels_(false, 10),
        menu_buttons_(true, 10),
        new_game_("Start new game with seed:"),
        end_game_("End current game") {

    set_title("Straights UI");
    set_border_width(10);

    // Add the main panel to the window
    add(panels_);


    panels_.pack_start(menu_buttons_, Gtk::PACK_SHRINK);
    panels_.pack_start(table_, Gtk::PACK_SHRINK);
    //panels.add(player_panel);
    //panels.add(player_hand);

    // Add widgets to the top panel
    menu_buttons_.pack_start(new_game_, Gtk::PACK_EXPAND_WIDGET);
    menu_buttons_.pack_start(rng_seed_, Gtk::PACK_EXPAND_WIDGET);
    menu_buttons_.pack_start(end_game_, Gtk::PACK_EXPAND_WIDGET);

    /* Set the frames label */
    table_.set_label("Cards on the table");
    /* Align the label at the right of the frame */
    table_.set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    /* Set the style of the frame */
    table_.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);  // Add the sub panels to the main panel
    // add cards to the frame
    table_.add(*(game_->deck()));

    // add the player panel
    panels_.add(player_panel_);
    for (unsigned int i = 0; i < 4; i++) {
        player_gui[i] = new PlayerGui();
        player_panel_.attach(*(player_gui[i]), i, i+1, 0, 1, Gtk::EXPAND, Gtk::EXPAND, 2, 2);
    }

    panels_.add(player_hand_);

    //new_game.signal_clicked().connect(sigc::mem_fun(*this, &GameView::newGameButtonClicked) );
    //end_game.signal_clicked().connect(sigc::mem_fun(*this, &GameView::endGameButtonClicked) );
    seed_buffer_ = Gtk::EntryBuffer::create();
    seed_buffer_ ->set_text("0");
    rng_seed_.set_buffer(seed_buffer_);
    rng_seed_.set_alignment(Gtk::ALIGN_CENTER);

    show_all_children();

    game_->subscribe(this);
}

void GameView::update() {
    state_ = game_->getState();
}

void GameView::newGameButtonClicked() {}
void GameView::endGameButtonClicked() {}
/*
void GameView::start() {
    // first we invite all the players
    invitePlayers();

    // run the game
    run();
}

void GameView::run() {
    // game loop
    while (state_ != GameState::GAME_OVER && state_ != GameState::GAME_QUIT) {
        startRound();
        update();
        while (state_ != GameState::ROUND_ENDED) {
            if (state_ == GameState::COMPUTER_PLAYER_TURN) {
                std::cout << controller_->onAITurn() << std::endl;
                controller_->endTurn();
            }
            else if (state_ == GameState::HUMAN_PLAYER_TURN) {
                // do action for the current state
                std::cout << "Cards on the table:" << std::endl;
                std::cout << "Clubs:" << controller_->listClubs() << std::endl;
                std::cout << "Diamonds:" << controller_->listDiamonds() << std::endl;
                std::cout << "Hearts:" << controller_->listHearts() << std::endl;
                std::cout << "Spades:" << controller_->listSpades() << std::endl;

                std::cout << "Your hand:" << controller_->getHand() << std::endl;
                std::cout << "Legal plays:" << controller_->getLegalPlays() << std::endl;
                while (state_ != GameState::NEXT_TURN) {
                    if (state_ == GameState::ILLEGAL_PLAY) {
                        std::cout << "This is not a legal play." << std::endl;
                    }
                    else if(state_ == GameState::ILLEGAL_DISCARD){
                        std::cout << "You have a legal play. You may not discard." << std::endl;
                    }
                    std::cout << ">";
                    Command instr;
                    // get a command if applicable
                    std::cin >> instr;

                    // act on that instruction
                    switch (instr.type) {
                        case PLAY:
                            std::cout << controller_->onPlay(instr.card);
                            break;
                        case DISCARD:
                            std::cout << controller_->onDiscard(instr.card);
                            break;
                        case DECK:
                            std::cout << *controller_->onShowDeck();
                            break;
                        case QUIT:
                            controller_->onQuit();
                            break;
                        case RAGEQUIT:
                            std::cout << "Player " << controller_->onRageQuit() << " ragequits. A computer will now take over." << std::endl;
                            std::cout << controller_->onAITurn() << std::endl;
                            break;
                        default:
                            break;
                    }

                    if(state_ == GameState::GAME_QUIT)
                        return;
                }
                // go to the next player
                controller_->endTurn();
            }
        }
        // After each round ends:
        for (int i = 0; i < Game::NUM_PLAYERS; i++) {
            std::cout << "Player " << i + 1 << "'s discards:" << controller_->getDiscards(i) << std::endl;
            std::cout << "Player " << i + 1 << "'s score: " << controller_->updateScore(i) << std::endl;
        }
        controller_->endRound();
    }
    if (state_ == GameState::GAME_OVER) {
        std::vector<int> winners = game_->winners();
        for(int i = 0; i < winners.size(); i++){
            std::cout << "Player " << winners[i] << " wins!" << std::endl;
        }
    } // prints nothing if the state was GAME_QUIT
}


void GameView::startRound() {
    int first_player = controller_->onStartRound();

    std::cout << "A new round begins. It's player " << first_player << "'s turn to play." << std::endl;
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
}*/
