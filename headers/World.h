#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>
#include <map>

#include "Chunk.h"
#include "Player.h"
#include "Identifier.h"

using namespace std;


struct ChunkMover {
    int jump;
    int position;

    ChunkMover()
        : jump(0), position(0) {    }
    ChunkMover(int j, int p)
        : jump(j), position(p) {    }
};

class World {
private:
    static const int BUFFER_SIZE = 30;
    static const int HALF_BUFFER_SIZE = 15;

    const Dimension* dimension;
    unordered_map<long int, Chunk> chunks;
    Player player;

public:
    World()
        : dimension(nullptr) {      }
    World(Dimension* dim)
        : dimension(dim) {      }
    vector<vector<Base>> current();
    vector<vector<Coordinate>> coordinate_current();
    unsigned int chunk_size()
        {   return chunks.size();   }

    // meant for player
    void move(Input input, int amount = 1);

private:
    Chunk get_Chunk(int y, int x);
    Base get_Base(int h, int w);
    Coordinate get_chunk_coords(int h, int w);
    ChunkMover get_ChunkMover(int move, int current);

};

#endif