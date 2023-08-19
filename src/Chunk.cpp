#include <iostream>
#include "Chunk.h"


Chunk::Chunk()
    : tiles(DIMENSION, vector<Base>(DIMENSION)) {
    for (int h = 0; h < DIMENSION; h++) {
        for (int w = 0; w < DIMENSION; w++) {
            if (h % 2 == 0) {
                tiles[h][w] = Base::Tree;
            } else if (h == 1 || h == 18) {
                tiles[h][w] = Base::Water;
            } else {
                tiles[h][w] = Base::Dirt;
            }
        }
    }
}

Base Chunk::get(int y, int x) {
    return tiles[y][x];
}

const char Chunk::base_char(Base base) {
    switch(base) {
    case Base::Dirt:
        return '.';
    case Base::Tree:
        return '*';
    case Base::Water:
        return '~';
    case Base::Center:
        return 'X';
    default:
        return ' ';
    }
}

void Chunk::print() {
    for (int h = 0; h < DIMENSION; h++) {
        for (int w = 0; w < DIMENSION; w++) {
            cout << base_char(tiles[h][w]) << " ";
        }
        cout << endl;
    }
}