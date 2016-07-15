#ifndef PLAYER_GUI_H_
#define PLAYER_GUI_H_

#include <gtkmm.h>
#include <array>
#include "GameController.h"

class HandGui : public Gtk::Frame {
public:
    HandGui();
    virtual ~HandGui();
private:
    std::array <Gtk::Image*, 13> nothing_;
    Gtk::Table hand_;
    std::array < Gtk::Button*, 13 > cards_;
};

class PlayerGui : public Gtk::Frame {
public:
    PlayerGui(GameController*);                 // constructor
    void setPlayer(unsigned int);               // sets the player associated with the frame
    void updateScore(int);                      // update the score display
    void updateDiscard(int);                    // update the discard count display
    unsigned int getIndex() const;              // accessor for index
    void disableRage();                         // can't rage when it's not your turn
    void enableRage();                          // enable rage button
    void onRageClicked();                       // event handler for rage button
private:
    Gtk::VBox container_;                       // contains all the GUI elements
    Gtk::Button rage_button_;                   // button for RQ
    Gtk::Label score_label_;                    // label for score
    Gtk::Label discards_label_;                 // label for # of discards
    unsigned int index_;                        // index indicating the player this is atached to
    GameController* controller_;
};

#endif // PLAYER_GUI_H_
