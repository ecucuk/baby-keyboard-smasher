/**
 
 */

#include <cstdint>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "Game.h"

int main(int argc, char* argv[]) {
  
    game::Game game;
    
    if (!game.initialize()) {
        return -1;
    }
    
    game.run();
    return EXIT_SUCCESS;
}
