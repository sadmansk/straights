#include "HandGui.h"
#include "Card.h"
#include "GameView.h"

HandGui::HandGui(GameView* parent, GameController* controller) : hand_(1, 13), controller_(controller), parent_(parent) {
    set_label("Your Hand");
    set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    add(hand_);
    for (unsigned int i = 0; i < 13; i++) {
        cards_[i] = new Gtk::Button();
        nothing_[i] = new Gtk::Image("img/nothing.png");
        cards_[i]->set_image(*(nothing_[i]));
        cards_[i]->set_sensitive(false);
        hand_.attach(*(cards_[i]), i, i+1, 0, 1, Gtk::FILL, Gtk::FILL);
    }
}

HandGui::~HandGui() {
    for (unsigned int i = 0; i < 13; i++) {
        delete cards_[i];
    }
}

void HandGui::update(const std::vector< std::pair<Card*, bool> >& cards) {
    unsigned int i = 0;
    bool mustDicard= true;
    for(unsigned int j = 0; j < cards.size(); j++){
        if(cards[j].second){
            mustDicard = false;
        }
    }

    for (; i < cards.size(); i++) {
        cards_[i]->set_image(*(cards[i].first->getImage()));
        cards_[i]->set_sensitive(cards[i].second || mustDicard);
        cards_[i]->signal_clicked().connect(sigc::bind<Card&>(sigc::mem_fun(*this, &HandGui::onCardClicked), *(cards[i].first),  cards[i].second) );
    }
    for (; i < cards_.size(); i++) {
        cards_[i]->set_image(*(nothing_[i]));
        cards_[i]->set_sensitive(false);
    }
}

void HandGui::onCardClicked(Card& card, bool playable) {
    std::cout << card << std::endl;
    if(playable){
        controller_->onPlay(card);
    } else{
        controller_->onDiscard(card);
    }

    for(unsigned int i = 0; i < cards_.size(); i++){ //TODO not working for some reason
        cards_[i]->set_sensitive(true);
    }

    controller_->endTurn();
    parent_->nextTurn();
}
