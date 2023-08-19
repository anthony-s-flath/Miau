#ifndef IMAGE_H
#define IMAGE_H


#include <string>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Identifier.h"
#include "Sprite.h"

using std::string;
using std::cout;
using std::endl;

class Image : public Sprite {
public:
    Image()
        : Sprite() {     }
    bool load(SDL_Renderer* renderer, const string &path) override;
    void render(SDL_Renderer* renderer) override;
};

    

#endif