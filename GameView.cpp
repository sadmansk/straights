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
        player_hand_(controller_),
        new_game_("Start new game with seed:"),
        end_game_("End current game") {
        

    set_title("Straights UI");
    set_border_width(10);

    // Add the mai1n panel to the window
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

    new_game_.signal_clicked().connect(sigc::mem_fun(*this, &GameView::newGameButtonClicked) );
    end_game_.signal_clicked().connect(sigc::mem_fun(*this, &GameView::endGameButtonClicked) );

    // add the player panel
    panels_.add(player_panel_);
    for (unsigned int i = 0; i < 4; i++) {
        player_gui_[i] = new PlayerGui(controller_);
        player_panel_.attach(*(player_gui_[i]), i, i+1, 0, 1, Gtk::EXPAND, Gtk::EXPAND, 2, 2);
    }

    panels_.add(player_hand_);

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

void GameView::newGameButtonClicked() {
    PlayerSelections selections(*this, "Human or Computer Players?", game_->NUM_PLAYERS);
    std::vector<char> players;
    while( players.size() != game_->NUM_PLAYERS){
        players = selections.query();
    }

    game_->reset(players, player_gui_); // TODO: BAD, this is not MVC

    // update the player cards
    assert(player_gui_.size() == game_->NUM_PLAYERS);

    run();
}

void GameView::endGameButtonClicked() {
    gtk_main_quit();
}

void GameView::startRound() {
    int first_player = controller_->onStartRound();
    std::cout << "A new round begins. It's player " << first_player << "'s turn to play." << std::endl;
}

void GameView::run() {
    int player_index = 0;
    // game loop
    while (state_ != GameState::GAME_OVER && state_ != GameState::GAME_QUIT) { startRound(); update();
        while (state_ != GameState::ROUND_ENDED) {
            if (state_ == GameState::COMPUTER_PLAYER_TURN) {
                std::cout << controller_->onAITurn() << std::endl;
            }
            else if (state_ == GameState::HUMAN_PLAYER_TURN) {
                // do action for the current state
                // enable rage
                player_gui_[player_index]->enableRage();
                // update hand
                ///player_hand_.update(controller_->getHand());
                std::cout << "Legal plays:" << controller_->getLegalPlays() << std::endl;
                while (state_ != GameState::NEXT_TURN) {
                    if (state_ == GameState::ILLEGAL_PLAY) {
                        // TODO: Replace this with a dialog
                        std::cout << "This is not a legal play." << std::endl;
                    }
                    else if(state_ == GameState::ILLEGAL_DISCARD){
                        // TODO: Replace this with a dialog
                        std::cout << "You have a legal play. You may not discard." << std::endl;
                    }

                            //std::cout << controller_->onPlay(instr.card);
                            //std::cout << controller_->onDiscard(instr.card);

                    if(state_ == GameState::GAME_QUIT)
                        return;
                }
            }
            // update discard count
            player_gui_[player_index]->updateDiscard(controller_->getDiscards(player_index));
            // disable rage
            player_gui_[player_index]->disableRage();
            // go to the next player
            controller_->endTurn();
            player_index = (player_index+1)%4;
        }
        // After each round ends:
        for (int i = 0; i < Game::NUM_PLAYERS; i++) {
            //std::cout << "Player " << i + 1 << "'s discards:" << controller_->getDiscards(i) << std::endl;
            player_gui_[i]->updateScore(controller_->updateScore(i));
            player_gui_[i]->updateDiscard(controller_->getDiscards(i));

            //std::cout << "Player " << i + 1 << "'s score: " << controller_->updateScore(i) << std::endl;
        }
        controller_->endRound();
    }
    if (state_ == GameState::GAME_OVER) {
        std::vector<int> winners = game_->winners();
        for(unsigned int i = 0; i < winners.size(); i++){
            std::cout << "Player " << winners[i] << " wins!" << std::endl;
        }
    } // prints nothing if the state was GAME_QUIT
}
