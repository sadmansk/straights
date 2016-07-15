/*
 *  MyDialogBox.cc
 *
 *  Created by Caroline Kierstead on 28/05/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */
#include "PlayerSelections.h"
#include <gtkmm/stock.h>
#include <iostream>
#include <cassert>

using std::string;
using std::vector;

// Specifies the parent window of the dialog box and the title of the dialog box.
PlayerSelections::PlayerSelections( Gtk::Window & parentWindow, string title, int players) : Dialog( title, parentWindow, true, true ) {
    // Obtain the dialog box's vertical alignment box.
    Gtk::VBox* contentArea = this->get_vbox();

    assert(players > 0);
    // Set up a group of radio buttons
      for ( int i = 0; i < players ; i++ ) {
          choices.push_back( new Gtk::ComboBoxText);
          choices[i]->append("Human Player");
          choices[i]->append("Computer Player");
          choices[i]->set_active(0);
          contentArea->add( *choices[i] );
      }


    // Add a standard "ok" button with the appropriate responses when clicked.
    add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
    show_all_children();
}

std::vector<char> PlayerSelections::query(){
    // Wait for a response from the dialog box.
    int result = run();
    switch (result) {
    case Gtk::RESPONSE_OK:{
        std::vector<char> response;

        for ( unsigned int i = 0; i < choices.size(); i++ ) {
            if(choices[i]->get_active_row_number() == 0){
                response.push_back('h');
            }
            else{
                response.push_back('c');
            }
        }

        return response;
        } break;
    default:
        std::vector<char> empty;
        return empty;
    }
}

PlayerSelections::~PlayerSelections() {
	for ( unsigned int i = 0; i < choices.size(); i++ ) delete choices[i];
	choices.clear();
}
