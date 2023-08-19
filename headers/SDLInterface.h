#ifndef SDLINTERFACE_H
#define SDLINTERFACE_H

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Game.h"
#include "Identifier.h"


using std::cout;
using std::endl;
using std::string;



class SDLInterface : public Game {
private:
    const string ASSETS_PATH = "assets";
    const string TTF_PATH = "/System/Library/Fonts/Supplemental";
    const vector<string> pngs = {
        "player.png"
    };
    const vector<string> ttfs = {
        "Skia.ttf"
    };


    const bool debug;
    SDL_Window* window;
    

public:
    SDLInterface(unsigned int height, unsigned int width, bool db);
    ~SDLInterface();
    bool run();


private:
    // game loop
    bool init();
    bool move_key(const SDL_Keycode keycode);
    static string path(vector<string> paths);
};
    

#endif