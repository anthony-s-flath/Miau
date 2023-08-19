#include <cmath>
#include "Screen.h"

Screen::Screen(Dimension* dim)
    : dimension(dim), window(0,0), tile_dimension(0,0) {
    char_screen = vector<vector<char>>(dimension->height, vector<char>(dimension->width));
}

Screen::Screen(Dimension* dim, Dimension window)
    : dimension(dim), 
        window(window.height, window.width), 
        // slightly off screen, but can fit the amount of square tiles
        tile_dimension(5 * std::ceil((double)window.height / dimension->height), 
                        5 * std::ceil((double)window.width / dimension->width)) {
    if (tile_dimension.height != tile_dimension.width) {
        cout << "TILE HEIGHT != TILE WIDTH" << endl;
        cout << "window.height: " << window.height << endl;
        cout << "window.width: " << window.width << endl;
        cout << "dimension.height: " << dimension->height << endl;
        cout << "dimension.width: " << dimension->width << endl;
        cout << "tile_dimension.height: " << tile_dimension.height << endl;
        cout << "tile_dimension.width: " << tile_dimension.width << endl;
    }
}

Screen::~Screen() {
    for_each(sprites.begin(), sprites.end(), [] (auto &itr) {
        delete itr.second;
    });
    SDL_RenderClear(renderer);
    IMG_Quit();
}

bool Screen::init(SDL_Window* window, const vector<std::pair<string, Path>> &files) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        cout << "ERROR: Renderer could not be created:\n" << SDL_GetError() << endl;
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    if (TTF_Init() == -1) {
        cout << "SDL_ttf could not be initialized:\n" << TTF_GetError() << endl;
        return false;
    }
    
    
    int img_flags = IMG_INIT_PNG;
    // IMG_init will send back IMG_INIT_XXX ints
    if (!(IMG_Init(img_flags) & img_flags)) {
        cout << "ERROR: Images could not be initialized:\n" << IMG_GetError() << endl;
        return false;
    }

    // TODO: TTF HEADER
    for (size_t i = 0; i < files.size(); ++i) {
        switch(files[i].second.type) {
        case FileType::PNG:
            sprites[files[i].first] = new Image();
            break;
        case FileType::TTF:
            sprites[files[i].first] = new Text();
            break;
        default:
            cout << "ERROR: " << files[i].first << " type not recognized" << endl;
        }

        if (!sprites[files[i].first]->load(renderer, files[i].second.path)) {
            return false;
        }
    }

    return true;
}

void Screen::render(vector<vector<Base>> current) {
    SDL_RenderClear(renderer);

    for (size_t y = 0; y < dimension->height; ++y) {
        for (size_t x = 0; x < dimension->width; ++x) {
            render_tile(current[y][x], y, x);
        }
    }

    SDL_RenderPresent(renderer);
}

void Screen::render_tile(Base base, size_t y, size_t x) {
// TODO: for all world.current Base, render
    char c;
    switch(base) {
    case Base::Dirt:

        break;
    case Base::Water:

        break;
    case Base::Tree:

        break;
    case Base::Center:

        break;
    case Base::Empty:
        c = ' ';
        break;
    }

    for (auto &[key, sprite] : sprites) {
        sprite->manipulate(position(y, x), tile_dimension);
        switch(sprite->get_type()) {
        case FileType::PNG:
            sprite->render(renderer);
            break;
        case FileType::TTF:
            ((Text*) sprite)->render(renderer, c);
            break;
        }
    }
}

// TODO: make member vars, more efficient
Coordinate Screen::position(unsigned int y, unsigned int x) {
    y *= tile_dimension.height;
    y -= (tile_dimension.height * dimension->height) - window.height;
    x *= tile_dimension.width;
    x -= (tile_dimension.width * dimension->width) - window.width;
    return Coordinate(y, x);
}


void Screen::print(ostream &stream, Base &base) {
    stream << Chunk::base_char(base);
}

void Screen::print(ostream &stream, Coordinate &coordinate) {
    stream << coordinate.y << "," << coordinate.x;
}
