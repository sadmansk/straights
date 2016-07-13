#include <iostream>
#include <cstdlib>
#include <gtkmm/main.h>

#include "Deck.h"
#include "GameView.h"
#include "GameController.h"
#include "Game.h"

int main (int argc, char* argv[]) {
    // Check if the user provided a seed to work with
    if (argc > 1) {
        // update the static global RNG seed
        Deck::rng_seed = atoi(argv[1]);
    }
    Gtk::Main kit(argc, argv);

    // Create and initialize MVC components
    Game game;
    GameController controller(&game);
    GameView view(&controller, &game);


    Gtk::Main::run(view);
    
    return 0;
}
