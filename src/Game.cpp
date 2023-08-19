#include <iostream>
#include <algorithm>

#include "Game.h"

Game::Game(unsigned int height, unsigned int width)
    : tiles(TILES), dimension(height, width),
                screen(&dimension), world(&dimension) {     }


Game::Game(Dimension window)
    : tiles(TILES), 
        dimension(calc_dim(window.height, window.width), calc_dim(window.width, window.height)),
        screen(&dimension, window),
        world(&dimension) {     }

unsigned int Game::calc_dim(unsigned int a, unsigned int b) {
    double ratio = (double) a / b;
    a = std::max((double) tiles, tiles * ratio);
    return a % 2 == 1 ? a : a + 1;
}

void Game::tick(Input input, int count) {
    // TODO:
    // if Quit, load/save

    world.move(input, count);
}

void Game::print() {
    screen.print(world.current());
}

void Game::debug_print() {
    screen.print(world.coordinate_current());
    cout << "Chunk amount: " << world.chunk_size() << endl;
}

