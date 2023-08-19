#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>


enum Base {
    Empty = 0,
    Dirt,
    Water,
    Tree,
    Center
};


enum Input {
    Nothing = 0,
    Up,
    Down,
    Left,
    Right,
    Quit,
    Error
};

enum FileType {
    PNG = 0,
    TTF
};


struct Dimension {
    const int height;
    const int width;

    Dimension(int h, int w)
        : height(h), width(w) {     }
};

struct Coordinate {
    int y;
    int x;

    Coordinate()
        : y(0), x(0) {    }

    Coordinate(int y_, int x_)
        : y(y_), x(x_) {    }

    void operator=(Coordinate coordinate) {
        y = coordinate.y;
        x = coordinate.x;
    }
};

struct Path {
    FileType type;
    std::string path;

    Path(FileType type_, std::string path_)
        : type(type_), path(path_) {    }
    Path()
        : type(FileType::PNG), path("") {     }
};

#endif