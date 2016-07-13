#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include <iostream>
#include <gtkmm.h>

#include "Observer.h"
#include "GameController.h"
#include "Game.h"

// View class
class GameView : public Gtk::Window, public Observer {
public:
    GameView(GameController*, Game*);   // contructor
    virtual void update();              // Observer pattern: concrete update method

private:
	// Observer Pattern: to access model accessors without having to downcast subject
	Game *game_;
    GameState state_;
	
	// Strategy Pattern member (plus signal handlers)
	GameController *controller_;

    // Member widgets
    Gtk::VBox panels_;                  // Main window divided into four horizontal panels
    Gtk::HBox menu_buttons_;            // Top panel containing new and end game options and seed value
    Gtk::Frame table_;                  // Shows the cards on the table
    Gtk::HBox cards_;                   // container for card mages
    /*Gtk::HBox player_panel;             // Panel showing the status of the players
    Gtk::HBox player_hand;              // Panel containing the hand of the current player
    */
    Gtk::Button new_game_;
    Gtk::Button end_game_;
    Gtk::TextView rng_seed_;             // Text box holding the current seed
    Glib::RefPtr<Gtk::TextBuffer> seed_buffer_;

    // helper functions
    /*
    virtual void invitePlayers();       // invite and add the players
    virtual void startRound();          // start a new round
    virtual void run();                 // run the game loop
    */

    // signal handlers
    void newGameButtonClicked();
    void endGameButtonClicked();
};

#endif // GAME_VIEW_H_
