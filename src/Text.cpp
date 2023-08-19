#include "Text.h"
#include "Globals.h"


bool Text::load(SDL_Renderer* renderer, const string &path) {
    type = FileType::TTF;

    font = TTF_OpenFont(path.c_str(), Globals::BACKGROUND_FONT_SIZE);
    if (font == NULL) {
        cout << "ERROR: Font \"" << path.c_str() << "\" could not be loaded:\n";
        cout << TTF_GetError() << endl;
        error = true;
        return false;
    }

    return set(renderer, path.c_str());
}


void Text::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, sprite, NULL, &arrange);
}

void Text::render(SDL_Renderer* renderer, string text) {
    set(renderer, text.c_str());
    SDL_RenderCopy(renderer, sprite, NULL, &arrange);
}

void Text::render(SDL_Renderer* renderer, char text) {
    set(renderer, &text);
    SDL_RenderCopy(renderer, sprite, NULL, &arrange);
}

bool Text::set(SDL_Renderer* renderer, const char* text) {
    SDL_Surface* loaded = TTF_RenderText_Solid(font, text, Globals::BACKGROUND_FONT_COLOR);
    if (loaded == NULL) {
        cout << "ERROR: Text \"" << text << "\" could not be loaded:\n";
        cout << TTF_GetError() << endl;
        error = true;
        return false;
    }

    sprite = SDL_CreateTextureFromSurface(renderer, loaded);
    if (sprite == NULL) {
        cout << "ERROR: Text \"" << text << "\" could not be created:\n";
        cout << SDL_GetError() << endl;
        error = true;
        return false;
    }

    SDL_FreeSurface(loaded);
    return true;
}