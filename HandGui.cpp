#include "HandGui.h"
#include "Card.h"
#include "GameView.h"
#include <sstream>
HandGui::HandGui(GameView* parent, GameController* controller) : hand_(1, 13), controller_(controller), parent_(parent) {
    //show hands
    set_label("Your Hand");
    set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    add(hand_);

    //define card images
    for (unsigned int i = 0; i < 13; i++) {
        cards_[i] = new Gtk::Button();
        nothing_[i] = new Gtk::Image("img/nothing.png");
        cards_[i]->set_image(*(nothing_[i]));
        cards_[i]->set_sensitive(false);
        hand_.attach(*(cards_[i]), i, i+1, 0, 1, Gtk::FILL, Gtk::FILL);
    }
}

HandGui::~HandGui() {
    //empty cards
    for (unsigned int i = 0; i < 13; i++) {
        delete cards_[i];
    }
}

void HandGui::update(const std::vector< std::pair<Card*, bool> >& cards, int player) {
    unsigned int i = 0;

    //check if player should play, or discard this round
    bool mustDicard= true;
    for(unsigned int j = 0; j < cards.size(); j++){
        if(cards[j].second){
            mustDicard = false;
        }
    }

    std::stringstream ss;

    //outputs whether to play or discard
    ss << "Player " << player << " to play: Choose a card to ";
    if(mustDicard){
        ss << "DISCARD.";
    } else{
        ss << "PLAY.";
    }
    set_label(ss.str());

    //set cards still in hand
    for (; i < cards.size(); i++) {
        //set image to card face if available;
        cards_[i]->set_image(*(cards[i].first->getImage()));

        //set only playable cards, or discardable cards
        cards_[i]->set_sensitive(cards[i].second || mustDicard);

        //connect and save signals
        signals_[i] = cards_[i]->signal_clicked().connect(sigc::bind<Card&>(sigc::mem_fun(*this, &HandGui::onCardClicked), *(cards[i].first),  cards[i].second) );
    }

    //fade extra card slots
    for (; i < cards_.size(); i++) {
        cards_[i]->set_image(*(nothing_[i]));
        cards_[i]->set_sensitive(false);
    }
}

void HandGui::reset() {
    for(unsigned int i = 0; i < cards_.size(); i++){
        //reset buttons to unplayable
        cards_[i]->set_sensitive(false);
        cards_[i]->set_image(*(nothing_[i]));

        //remove signals
        signals_[i].disconnect();
    }
}

void HandGui::onCardClicked(Card& card, bool playable) {
    //play or discard the card clicked
    if(playable){
        controller_->onPlay(card);
    } else{
        controller_->onDiscard(card);
    }

    //reset the hand and rage button and move on to next turn
    reset();
    controller_->endTurn();
    parent_->disableRage();
    parent_->nextTurn();
}
