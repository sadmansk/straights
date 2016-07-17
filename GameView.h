#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include <iostream>
#include <gtkmm.h>

#include "Observer.h"
#include "GameController.h"
#include "Game.h"
#include "PlayerSelections.h"
#include "PlayerGui.h"
#include "HandGui.h"

// View class
class GameView : public Gtk::Window, public Observer {
public:
    GameView(GameController*, Game*);   // contructor
    virtual void update();              // Observer pattern: concrete update method
    virtual void nextTurn();            // do the magic for next turn
    virtual void disableRage();         // disable rage for the current player

private:
    void endGameDialog(std::vector<int>);
	// Observer Pattern: to access model accessors without having to downcast subject
	Game *game_;
    GameState state_;
    int player_index_;

	// Strategy Pattern member (plus signal handlers)
	GameController *controller_;

    // Member widgets
    Gtk::VBox panels_;                  // Main window divided into four horizontal panels
    Gtk::HBox menu_buttons_;            // Top panel containing new and end game options and seed value
    Gtk::Frame table_;                  // Shows the cards on the table
    Gtk::Table player_panel_;             // Panel showing the status of the players
    HandGui player_hand_;              // Panel containing the hand of the current player
    Gtk::Button new_game_;
    Gtk::Button end_game_;
    Gtk::Entry rng_seed_;             // Text box holding the current seed
    Glib::RefPtr<Gtk::EntryBuffer> seed_buffer_;
    std::array< PlayerGui*, 4 > player_gui_;

    // helper functions
    virtual void startRound();          // start a new round
    virtual void startGame();           // start a new game
    virtual void humanTurn();           // on a human player's turn
    virtual void aiTurn();              // on an AI player's turn

    // signal handlers
    void newGameButtonClicked();
    void endGameButtonClicked();
};

#endif // GAME_VIEW_H_
