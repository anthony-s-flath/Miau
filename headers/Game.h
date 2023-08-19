#ifndef GAME_H
#define GAME_H

#include "Screen.h"
#include "World.h"
#include "Identifier.h"

using namespace std;


const unsigned int TILES = 80;

class Game {
protected:
    unsigned int tiles;
    Dimension dimension;
    Screen screen;
    World world;

public:
    Game(unsigned int height, unsigned int width);
    Game(Dimension window);
    void tick(Input input, int count);
    void print();
    void debug_print();

private:
    unsigned int calc_dim(unsigned int a, unsigned int b);

};

#endif