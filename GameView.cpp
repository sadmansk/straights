#include <cassert>

#include "Command.h"
#include "GameView.h"
#include <sstream>
// Contructor
GameView::GameView(GameController* controller, Game* game) :
        Observer(),
        game_(game),
        controller_(controller),
        panels_(false, 10),
        menu_buttons_(true, 10),
        player_hand_(this, controller_),
        new_game_("Start new game with seed:"),
        end_game_("End current game") {

    player_index_ = 0;

    set_title("Straights UI");
    set_border_width(10);

    // Add the mai1n panel to the window
    add(panels_);

    panels_.pack_start(menu_buttons_, Gtk::PACK_SHRINK);
    panels_.pack_start(table_, Gtk::PACK_SHRINK);

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
    for (unsigned int i = 0; i < game_->NUM_PLAYERS; i++) {
        player_gui_[i] = new PlayerGui(this, controller_);
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
    players = selections.query();

    //if player cancels new game, exit with no changes
    if(players.size() != game_->NUM_PLAYERS)
        return;

    std::string seedText = seed_buffer_->get_text();
    int seedValue = 0;

    //attempt to parse input seed
    try{
        seedValue = atoi(seedText.c_str());
    }
    catch(...){
        std::cout << "Warning: Invalid seed value, setting it to 0." << std::endl;
        seed_buffer_->set_text("0");
        seedValue = 0;
    }

    for (int i = 0; i < Game::NUM_PLAYERS; i++) {
        player_gui_[i]->updateScore(0);
    }

    //disable rage buttons from previous rounds
    disableRage();

    //reset card buttons from previous rounds
    player_hand_.reset();

    //reset and reseed game
    game_->reset(players, player_gui_, seedValue);

    // update the player cards
    assert(player_gui_.size() == game_->NUM_PLAYERS);

    startGame();
}

void GameView::endGameButtonClicked() {
    hide();
}

void GameView::startRound() {
    //have controller start new round
    player_index_ = controller_->onStartRound() - 1;

    //output new round
    newRoundDialog();
    nextTurn();
}

void GameView::startGame() {
    //starts a new round
    startRound();
}

void GameView::newRoundDialog() {
    //disables current window while active
    Gtk::Dialog dialog("New Round Has Started", *this);

    //output current game state
    std::stringstream ss;
    ss << "A new round has started" << std::endl;
    for(unsigned int i = 0; i < Game::NUM_PLAYERS; i++){
        ss << "Player " << (i + 1) << " has " << game_->getScore(i) << " points." << std::endl;
    }

    //label and ok button
    Gtk::Label nameLabel(ss.str());
    Gtk::VBox* content = dialog.get_vbox();
    content->pack_start(nameLabel, true, false);
    nameLabel.show();
    dialog.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

    dialog.run();
}


void GameView::endGameDialog( std::vector<int> winners ) {
    //disables current window while active
    Gtk::Dialog dialog("Game Over", *this);

    //output game winner
    std::stringstream ss;
    if(winners.size() == 1){
        ss << "Player " << winners[0] << " wins!";
    } else {
        ss << "Players";
        ss << " " << winners[0];
        for(unsigned int i = 1; i < winners.size(); i++){
            ss << " and " << winners[i];
        }
        ss << " wins!";
    }

    //label winner, add button to close
    Gtk::Label nameLabel(ss.str());
    Gtk::VBox* content = dialog.get_vbox();
    content->pack_start(nameLabel, true, false);
    nameLabel.show();
    dialog.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

    dialog.run();
}

void GameView::nextTurn() {
    player_hand_.reset();
    update();
    if (state_ == GameState::COMPUTER_PLAYER_TURN) {
        aiTurn();
    }
    else if (state_ == GameState::HUMAN_PLAYER_TURN) {
        humanTurn();
        // go to the next player
        player_index_ = (player_index_+1)%4;
    }
    else if (state_ == GameState::ROUND_ENDED) {
        for (int i = 0; i < Game::NUM_PLAYERS; i++) {
            player_gui_[i]->updateScore(controller_->updateScore(i));
        }
        controller_->endRound();
        if(state_ == GameState::ROUND_ENDED){
            startRound();
        } else if (state_ == GameState::GAME_OVER) {
            endGameDialog(game_->winners());
        } // prints nothing if the state was GAME_QUIT)
    }
}

void GameView::aiTurn() {
    // go through computer player turns
    controller_->onAITurn();
    controller_->endTurn();

    // go to the next player
    player_index_ = (player_index_+1)%4;
    nextTurn();
}

void GameView::humanTurn() {
    // enable rage
    player_gui_[player_index_]->enableRage();
    // update hand
    player_hand_.update(controller_->getHand(), player_index_ + 1);
    // update discard count
    player_gui_[player_index_]->updateDiscard(controller_->getDiscards(player_index_));
}

void GameView::disableRage() {
    // disable rage of all player
    for(int i = 0; i < Game::NUM_PLAYERS; i++){
        player_gui_[i]->disableRage();
    }
}
