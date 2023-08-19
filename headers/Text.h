#ifndef TEXT_H
#define TEXT_H


#include <string>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Identifier.h"
#include "Sprite.h"

using std::string;
using std::cout;
using std::endl;

class Text : public Sprite {
private:
    TTF_Font* font;

public:
    Text()
        : Sprite() {    }
    bool load(SDL_Renderer* renderer, const string &path) override;
    void render(SDL_Renderer* renderer) override;
    void render(SDL_Renderer* renderer, string text);
    void render(SDL_Renderer* renderer, char text);

private:
    bool set(SDL_Renderer* renderer, const char* c);
};

    

#endif