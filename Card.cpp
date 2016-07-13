#include "Card.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>
using namespace std;

Card::Card(Suit s, Rank r){
	suit_ = s;
	rank_ = r;
	string ranks = "0123456789jqk";
    std::stringstream image_name;
    image_name << "img/" << s << "_" << ranks[r] << ".png";
    std::string image_str = image_name.str();
    
    // store both the card image as well as the upside down image
    image_.set(image_str);
    hidden_.set("img/nothing.png");
}

Suit Card::getSuit() const{
	return suit_;
}

Rank Card::getRank() const{
	return rank_;
}

Gtk::Image* Card::getImage(bool show) {
    if (show)
        return &image_;
    return &hidden_;
}

bool operator==(const Card &a, const Card &b){
	return a.getSuit() == b.getSuit() && a.getRank() == b.getRank();
}

ostream &operator<<(ostream &out, const Card &c){
	string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
		
	out << ranks[c.getRank()] << suits[c.getSuit()];
	
	return out;
}

istream &operator>>(istream &in, Card &c){
	string suits = "CDHS", ranks = "A234567891JQK";
	
	string str;
	in >> str;
	assert ( !in.fail() );
	
	//Read in the rank, make sure it's valid
	c.rank_ = (Rank)ranks.find( str.at(0) );
	assert ( c.rank_ != string::npos );
	
	//If it's a 10, make sure the 2nd character is a 0
	if ( c.rank_ == TEN ){
		assert(str.at(1) == '0');
		str.at(1) = str.at(2);
	}
	
	//Read in the suit, make sure it's valid
	c.suit_ = (Suit)suits.find( str.at(1) );
	assert ( c.suit_ != string::npos );
	
	return in;
}
