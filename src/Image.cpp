#include "Image.h"


bool Image::load(SDL_Renderer* renderer, const string &path) {
    type = FileType::PNG;

    SDL_Surface* loaded = IMG_Load(path.c_str());
    if (loaded == NULL) {
        cout << "ERROR: Image \"" << path.c_str() << "\" could not be loaded:\n";
        cout << IMG_GetError() << endl;
        error = true;
        return false;
    }
    sprite = SDL_CreateTextureFromSurface(renderer, loaded);
    if (sprite == NULL) {
        cout << "ERROR: Image \"" << path.c_str() << "\" could not be created:\n";
        cout << SDL_GetError() << endl;
        error = true;
        return false;
    }

    SDL_FreeSurface(loaded);
    return true;
}


void Image::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, sprite, NULL, &arrange);
}