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

    if(players.size() != game_->NUM_PLAYERS)
        return;

    std::string seedText = seed_buffer_->get_text();
    int seedValue = 0;
    try{
        seedValue = atoi(seedText.c_str());
    }
    catch(...){
        seed_buffer_->set_text("0");
        seedValue = 0;
    }
    game_->reset(players, player_gui_, seedValue); // TODO: BAD, this is not MVC

    // update the player cards
    assert(player_gui_.size() == game_->NUM_PLAYERS);

    startGame();
}

void GameView::endGameButtonClicked() {
    hide();
}

int GameView::startRound() {
    return controller_->onStartRound();
    nextTurn();
}

void GameView::startGame() {
    player_index_ = startRound() - 1;
    nextTurn();
}

void GameView::nextTurn() {
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
        startRound();
    }
    else if (state_ == GameState::GAME_OVER) {
        //TODO: winner screen goes here
        std::vector<int> winners = game_->winners();
        for(unsigned int i = 0; i < winners.size(); i++){
            std::cout << "Player " << winners[i] << " wins!" << std::endl;
        }
    } // prints nothing if the state was GAME_QUIT
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
    std::cout << player_index_ << std::endl;
    // enable rage
    player_gui_[player_index_]->enableRage();
    // update hand
    player_hand_.update(controller_->getHand());
    // update discard count
    player_gui_[player_index_]->updateDiscard(controller_->getDiscards(player_index_));
}

void GameView::disableRage() {
    // disable rage of the current player
    player_gui_[player_index_]->disableRage();
}
