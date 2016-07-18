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
    HandGui(GameView*, GameController*);        // constructor
    virtual ~HandGui();                         // destructor
    void update(const std::vector< std::pair<Card*, bool> >&, int);     // update the hand display with new cards
    void reset();                               // resets the status of the cards
    void onCardClicked(Card&, bool);            // manages clicked cards
private:
    std::array <Gtk::Image*, 13> nothing_;      // TODO: should be able to get away with using just one image
    Gtk::Table hand_;                           // layout of the hand image buttons
    std::array < Gtk::Button*, 13 > cards_;     // Hand image buttons
    std::array < sigc::connection, 13 > signals_;// signals for each button
    GameController* controller_;                // reference to the controller
    GameView* parent_;                          // reference to the parent window
};

#endif // HAND_GUI_H_
