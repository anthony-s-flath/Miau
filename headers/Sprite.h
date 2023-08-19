#ifndef SPRITE_H
#define SPRITE_H


#include <string>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Identifier.h"

using std::string;
using std::cout;
using std::endl;

class Sprite {
protected:
    bool error;
    FileType type;
    SDL_Texture* sprite;
    SDL_Rect arrange;

public:
    Sprite()
        : error(false) {    }
    virtual ~Sprite() = default;
    virtual bool load(SDL_Renderer* renderer, const string &path) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    void manipulate(const int y, const int x, const int h, const int w)
        {   arrange = {x, y, w, h};    }


    void manipulate(const Coordinate coordinates, const Dimension dimension)
        {   manipulate(coordinates.y, coordinates.x, dimension.height, dimension.width);   }
    void move(const Coordinate coordinates)
        {   manipulate(coordinates.y, coordinates.x, 0, 0);   }
    void move(const int y, const int x)
        {   manipulate(y, x, 0, 0);   }
    void stretch(const int h, const int w)
        {   manipulate(0, 0, h, w);   }
    bool get_error() const
        {   return error;   }
    FileType get_type() const
        {   return type;    }

protected:
};
    

#endif