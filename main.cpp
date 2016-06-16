#include <iostream>
#include <cstdlib>

int main (int argc, char* argv[]) {
    int seed;
    // Check if the user provided a seed to work with
    if (argc > 1) {
        seed = atoi(argv[1]);
        std::cout << seed << std::endl;
    }
    return 0;
}
