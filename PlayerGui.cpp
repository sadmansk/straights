#include "PlayerGui.h"

HandGui::HandGui() : hand_(1, 13) {
    set_label("Your Hand");
    set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    add(hand_);
    for (unsigned int i = 0; i < 13; i++) {
        cards_[i] = new Gtk::Button();
        nothing_[i] = new Gtk::Image("img/nothing.png");
        cards_[i]->set_image(*(nothing_[i]));
        hand_.attach(*(cards_[i]), i, i+1, 0, 1, Gtk::FILL, Gtk::FILL);
    }
}

HandGui::~HandGui() {
    for (unsigned int i = 0; i < 13; i++) {
        delete cards_[i];
    }
}

PlayerGui::PlayerGui() : container_(false, 5), rage_button_("RAGE!"), score_label_("Score: 0"), discards_label_("Discards: 0") {
    set_label("Player ");
    set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

    set_size_request(150, 100);

    add(container_);
    container_.pack_start(rage_button_, Gtk::PACK_EXPAND_WIDGET);
    container_.pack_start(score_label_, Gtk::PACK_EXPAND_WIDGET);
    container_.pack_start(discards_label_, Gtk::PACK_EXPAND_WIDGET);

}
