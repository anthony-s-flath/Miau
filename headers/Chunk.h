#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <Identifier.h>

using namespace std;

class Chunk {
public:
    static const int DIMENSION = 10;

private:
    vector<vector<Base>> tiles;

public:
    static const char base_char(Base base);

    Chunk();
    Base get(int y, int x);
    void print();

private:

};

#endif