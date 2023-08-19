#include "World.h"
#include <bitset>



vector<vector<Base>> World::current() {
    vector<vector<Base>> map(dimension->height, vector<Base>(dimension->width));
    const int h_half = dimension->height / 2;
    const int w_half = dimension->width / 2;
    for (int h = -h_half; h <= h_half; ++h) {
        for (int w = -w_half; w <= w_half; ++w) {
                map[h + h_half][w + w_half] = get_Base(h, w);
        }
    }

    map[h_half][w_half] = Base::Center;

    return map;
}


Chunk World::get_Chunk(int y, int x) {
    unsigned int uliy = y;
    unsigned int ulix = x;
    unsigned long int pos = ulix | ((long)uliy << 32);
    return chunks[pos];
}

Base World::get_Base(int h, int w) {
    ChunkMover h_axis = get_ChunkMover(h, player.y);
    ChunkMover w_axis = get_ChunkMover(w, player.x);

    return get_Chunk(h_axis.jump, w_axis.jump)
            .get(h_axis.position, w_axis.position);
}


void World::move(Input input, int amount) {
    switch(input) {
    case Input::Up:
        player.y -= amount;
        return;
    case Input::Down:
        player.y += amount;
        return;
    case Input::Left:
        player.x -= amount;
        return;
    case Input::Right:
        player.x += amount;
        return;
    default:
        return;
    }
}

vector<vector<Coordinate>> World::coordinate_current() {
    vector<vector<Coordinate>> map(dimension->height, vector<Coordinate>(dimension->width));
    const int h_half = dimension->height / 2;
    const int w_half = dimension->width / 2;
    for (int h = -h_half; h <= h_half; ++h) {
        for (int w = -w_half; w <= w_half; ++w) {
                map[h + h_half][w + w_half] = get_chunk_coords(h, w);
        }
    }

    return map;
}

Coordinate World::get_chunk_coords(int h, int w) {
    int h_pos = get_ChunkMover(h, player.y).position;
    int w_pos = get_ChunkMover(w, player.x).position;
    return Coordinate(h_pos, w_pos);
}


ChunkMover World::get_ChunkMover(int move, int current) {
    // position if world was one chunk
    int pos = move + current;
    // how many chunks away is this position?
    int jump = pos / Chunk::DIMENSION;
    if (pos < 0) {
        // round down
        jump -= 1;
        // only need positive for jumped chunk
        pos *= -1;
    }
    // position in jumped chunk
    pos %= Chunk::DIMENSION;
    // inverse position
    if (pos < 0) {
        // if h != 0 then h_pos = (1, 10) where 10 should be 0
        pos = (Chunk::DIMENSION - pos) % Chunk::DIMENSION;
    }

    return ChunkMover(jump, pos);
}