#include <iostream>
#include <cstdlib>

#include "Deck.h"

int main (int argc, char* argv[]) {
    // Check if the user provided a seed to work with
    if (argc > 1) {
        Deck::rng_seed = atoi(argv[1]);
        std::cout << seed << std::endl;
    }
    return 0;
}
