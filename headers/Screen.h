#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <SDL.h>

#include "World.h"
#include "Identifier.h"
#include "Image.h"
#include "Text.h"

using namespace std;

class Screen {
private:
    const Dimension* dimension;
    Dimension window;
    Dimension tile_dimension;

    vector<vector<char>> char_screen;

    SDL_Renderer* renderer;
    unordered_map<string, Sprite*> sprites;
    

public:
    Screen(Dimension* dimension);
    Screen(Dimension* dimension, Dimension window);
    ~Screen();


    // SDL
    bool init(SDL_Window* window, const vector<std::pair<string, Path>> &files);
    void render(vector<vector<Base>> current);
    int window_width() { return window.width; }
    int window_height() { return window.height; }

    template <typename T>
    void print(vector<vector<T>> current);
    void print(ostream &stream, Base &base);
    void print(ostream &stream, Coordinate &coordinate);

private:
    void render_tile(Base base, size_t y, size_t x);
    Coordinate position(unsigned int y, unsigned int x);

    static unsigned int calc_dim(unsigned int i);
};





template <typename T>
void Screen::print(vector<vector<T>> current) {
    for (int h = 0; h < dimension->height; ++h) {
        for (int w = 0; w < dimension->width; ++w) {
            cout << std::setw(3);
            print(cout, current[h][w]);
        }
        cout << endl;
    }
}

#endif