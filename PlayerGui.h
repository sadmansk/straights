#ifndef PLAYER_GUI_H_
#define PLAYER_GUI_H_

#include <gtkmm.h>
#include <array>

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
    PlayerGui();
private:
    Gtk::VBox container_;                       // contains all the GUI elements
    Gtk::Button rage_button_;                   // button for RQ
    Gtk::Label score_label_;                    // label for score
    Gtk::Label discards_label_;                 // label for # of discards
};

#endif // PLAYER_GUI_H_
