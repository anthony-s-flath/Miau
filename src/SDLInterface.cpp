#include "SDLInterface.h"


SDLInterface::SDLInterface(unsigned int height, unsigned int width, bool db)
        : Game(Dimension(height, width)),
             debug(db) {    }



SDLInterface::~SDLInterface() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool SDLInterface::init() {
    if (debug)
        cout << "am debugging lol" << endl;
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        cout << "ERROR: SDL could not initialize:\n" << SDL_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow("SDL Game", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        screen.window_width(), screen.window_height(), SDL_WINDOW_HIDDEN);
    if (window == NULL) {
        cout << "ERROR: Window could not be created:\n" << SDL_GetError() << endl;
        return false;
    }

    vector<std::pair<string, Path>> files(pngs.size() + ttfs.size());
    size_t i = 0;
    for (size_t j = 0; j < pngs.size() && i < (pngs.size() + ttfs.size()); ++i, ++j) {
        files[i].first = pngs[j];
        files[i].second = Path(FileType::PNG, path({ASSETS_PATH, pngs[j]}));
    }

    for (size_t j = 0; j < ttfs.size() && i < (pngs.size() + ttfs.size()); ++i, ++j) {
        files[i].first = ttfs[j];
        files[i].second = Path(FileType::TTF, path({TTF_PATH, ttfs[j]}));
    }

    if (!screen.init(window, files)) {
        cout << "ERROR: Screen could not get initialized" << endl;
        return false;
    }

    return true;
}

bool SDLInterface::run() {
    if (!init())
        return false;


    SDL_ShowWindow(window);

    SDL_Event event;
    int running = true;

    while(running) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                running = move_key(event.key.keysym.sym);
            }
        }
        screen.render(world.current());

        SDL_Delay(32);
    }

    return true;
}


bool SDLInterface::move_key(SDL_Keycode keycode) {
    switch(keycode) {
    case SDLK_w:
        world.move(Input::Up, 1);
        break;
    case SDLK_s:
        world.move(Input::Down, 1);
        break;
    case SDLK_a:
        world.move(Input::Left, 1);
        break;
    case SDLK_d:
        world.move(Input::Right, 1);
        break;
    case SDLK_q:
        return false;
    }

    return true;
}

string SDLInterface::path(vector<string> paths) {
    string tmp;
    for (string &s : paths) {
        tmp += s + '/';
    }
    return tmp.substr(0, tmp.size() - 1);
}





