#include "Deck.h"
#include <random>

// initialize static seed
int Deck::rng_seed = 0;

Deck::Deck() {
    // we initialize the ordered deck here
    for (int i = 0; i < CARD_COUNT; i++) {
        cards_[i] = new Card(Suit(i/13), Rank(i%13));
    }
}

Deck::~Deck(){
    for( int i = 0; i < CARD_COUNT; i++){
        delete cards_[i];
    }
}

void Deck::shuffle() {
    static std::random_device rng;

	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

Card* Deck::getCardAt(int pos) const {
    return cards_[pos];
}

std::ostream &operator<<(std::ostream& os, const Deck& d) {
    for (int i = 0; i < CARD_COUNT; i++) {
        os << d.getCardAt(i) << " ";
        if (i % 13 == 12) os << std::endl;
    }

    return os;
}
