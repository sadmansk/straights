#ifndef PLAYER_GUI_H_
#define PLAYER_GUI_H_

#include <gtkmm.h>
#include <array>
#include <vector>
#include <utility>
#include "GameController.h"

class HandGui : public Gtk::Frame {
public:
    HandGui(GameController*);                   // constructor
    virtual ~HandGui();                         // destructor
    void update(const std::vector< std::pair<Card*, bool> >&);     // update the hand display with new cards
    void onCardClicked(Card&);            // manages clicked cards
private:
    std::array <Gtk::Image*, 13> nothing_;      // TODO: should be able to get away with using just one image
    Gtk::Table hand_;
    std::array < Gtk::Button*, 13 > cards_;
    GameController* controller_;
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
