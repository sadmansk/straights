#ifndef DECK_H_
#define DECK_H_

#include "Card.h"
#include <gtkmm/table.h>

#define CARD_COUNT 52

class Deck : public Gtk::Table {
public:
    Deck();                     // default constructor
    ~Deck();                    // destructor
    void shuffle();             // public function fot shuffling the deck
    Card* getCardAt(int) const; // accessor for individual cards
    static int rng_seed;        // global static seed for rng
    void on(Card*);
    void off(Card*);
private:
    Card* cards_[CARD_COUNT]; // array of cards
};

// stream operators
std::ostream &operator<<(std::ostream &, const Deck&);

#endif // DECK_H_
