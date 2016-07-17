#include "PlayerGui.h"
#include "GameView.h"


PlayerGui::PlayerGui(GameView* parent, GameController* controller) : container_(false, 5), rage_button_("RAGE!"), score_label_("Score: 0"), discards_label_("Discards: 0"), controller_(controller), parent_(parent) {
    index_ = 0;
    set_label("Player 0");
    set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

    set_size_request(150, 100);

    add(container_);
    container_.pack_start(rage_button_, Gtk::PACK_EXPAND_WIDGET);
    container_.pack_start(score_label_, Gtk::PACK_EXPAND_WIDGET);
    container_.pack_start(discards_label_, Gtk::PACK_EXPAND_WIDGET);

    rage_button_.set_sensitive(false);
    rage_button_.signal_clicked().connect(sigc::mem_fun(*this, &PlayerGui::onRageClicked) );

}

void PlayerGui::setPlayer(unsigned int index) {
    // set the index
    index_ = index;
    std::stringstream ss;
    ss << "Player " << index;
    set_label(ss.str());
}

unsigned int PlayerGui::getIndex() const {
    return index_;
}

void PlayerGui::updateScore(int score) {
    std::stringstream ss;
    ss << "Score: " << score;
    score_label_.set_text(ss.str());
}

void PlayerGui::updateDiscard(int count) { std::stringstream ss;
    ss << "Discards: " << count;
    discards_label_.set_text(ss.str());
}

void PlayerGui::disableRage() {
    rage_button_.set_sensitive(false);
}

void PlayerGui::enableRage() {
    rage_button_.set_sensitive(true);
}

void PlayerGui::onRageClicked() {
    controller_->onRageQuit();
    controller_->onAITurn();
}
