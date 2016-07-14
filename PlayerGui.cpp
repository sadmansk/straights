#include "PlayerGui.h"

HandGui::HandGui() : nothing_("img/nothing.png") {
    set_label("Your Hand");
    set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    for (unsigned int i = 0; i < 13; i++) {
        cards_[i] = new Gtk::Button();
        cards_[i]->set_image(nothing_);
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
