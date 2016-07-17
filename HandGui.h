#ifndef HAND_GUI_H_
#define HAND_GUI_H_

#include <gtkmm.h>
#include <array>
#include <vector>
#include <utility>

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/image.h>
#include <gtkmm/window.h>


class GameView;
class GameController;
class Card;

class HandGui : public Gtk::Frame {
public:
    HandGui(GameView*, GameController*);                   // constructor
    virtual ~HandGui();                         // destructor
    void update(const std::vector< std::pair<Card*, bool> >&);     // update the hand display with new cards
    void onCardClicked(Card&, bool);            // manages clicked cards
private:
    std::array <Gtk::Image*, 13> nothing_;      // TODO: should be able to get away with using just one image
    Gtk::Table hand_;
    std::array < Gtk::Button*, 13 > cards_;
    std::array < sigc::connection, 13 > signals_;
    GameController* controller_;
    GameView* parent_;
};

#endif // HAND_GUI_H_
