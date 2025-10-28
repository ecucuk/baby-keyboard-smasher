//
//  main.cpp
//  BabySmasherGame
//
//  Created by Ergün CÜCÜK on 29.10.2025.
//

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <ctime>
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
