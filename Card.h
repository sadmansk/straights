// CS247 staff please note that names following an underscore is reserved for compiler variables
#ifndef CARD_H_
#define CARD_H_

#include <ostream>
#include <istream>
#include <gtkmm/image.h>

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

class Card : public Gtk::Image{
	friend std::istream &operator>>(std::istream &, Card &);

public:
	Card(Suit, Rank);
	Suit getSuit() const;
	Rank getRank() const;
	Gtk::Image* getImage() const;
	void hide();
	void show();
private:
	Suit suit_;
	Rank rank_;
	std::string imagePath_;
	std::string nothingPath_ = "img/nothing.png";
};

bool operator==(const Card &, const Card &);
bool operator<(const Card&, const Card&);
bool operator<=(const Card &, const Card &);
bool operator>(const Card&, const Card&);
bool operator>=(const Card &, const Card &);

//output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &, const Card &);
std::istream &operator>>(std::istream &, Card &);

#endif // CARD_H_
