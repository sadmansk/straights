#include "Deck.h"
#include <cassert>
#include <random>
#include <algorithm>
#include <iostream>

// initialize static seed
int Deck::rng_seed = 0;

Deck::Deck() : Gtk::Table(Suit::SUIT_COUNT, Rank::RANK_COUNT) {
    // we initialize the ordered deck here
    for (int i = 0; i < CARD_COUNT; i++) {
        cards_[i] = new Card(Suit(i/13), Rank(i%13));
        attach(*cards_[i], i%13, i%13 + 1, i/13, i/13 +1, Gtk::EXPAND, Gtk::EXPAND, 5, 5);
    }
}

Deck::~Deck(){
    for( int i = 0; i < CARD_COUNT; i++){
        delete cards_[i];
    }
}

void Deck::reset(int seed) {
    rng_seed = seed;
}

void Deck::shuffle() {
    static std::mt19937 rng(rng_seed);
    std::cout << std::endl << rng_seed << std::endl;

	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (rng() % n);
        //std::cout << k << std::endl;
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

void Deck::on( Card* card ) {
    card->show();
}

void Deck::off( Card* card ) {
    card->hide();
}

Card* Deck::getCardAt(int pos) const {
    assert(pos < CARD_COUNT);
    return cards_[pos];
}

std::ostream &operator<<(std::ostream& os, const Deck& d) {
    for (int i = 0; i < CARD_COUNT; i++) {
        os << *d.getCardAt(i) << " ";
        if (i % 13 == 12) os << std::endl;
    }

    return os;
}
