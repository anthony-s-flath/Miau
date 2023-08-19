#include <iostream>
#include <getopt.h>
#include "TerminalInterface.h"
#include "SDLInterface.h"

using std::cout;
using std::cerr;
using std::endl;

static const unsigned int MAX = 1000;

enum Interface {
    Terminal = 0,
    SDL
};

int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "ERROR: not enough args" << endl;
        cerr << "Format: ./miau.exe [height] [width] (flags)" << endl;
        return -1;
    }

    // before getopt because getopt changes argv order
    unsigned int y;
    unsigned int x;
    try {
        y = atoi(argv[1]);
        x = atoi(argv[2]);
    } catch (std::invalid_argument e) {
        cerr << "ERROR: invalid dimensions" << endl;
        return -1;
    }


    option long_options[] = {
        {"interface", required_argument, nullptr, 'i'},
        {"debug", no_argument, nullptr, 'd'},
        { nullptr, 0, nullptr, '\0' }
    };
    
    Interface interface;
    bool debug = false;
    int c = 0;
    int option_index = 0;
    while ((c = getopt_long (argc, argv, "i:d", 
                    long_options, &option_index)) != -1) {
        switch (c) {
        case 'i':
            if (strcmp(optarg, "terminal") == 0) {
                interface = Interface::Terminal;
            } else if (strcmp(optarg, "sdl") == 0) {
                interface = Interface::SDL;
            } else {
                cerr << "ERROR: incorrect interface option: " << optarg << endl;
                cerr << "Format: -i [terminal|sdl]" << endl;
                return -1;
            }
            break;
        case 'd':
            debug = true;
            break;
        default:
            cerr << "ERROR: Incorrect flag used: " << (unsigned char) c << endl;
            return -1;
        }
    }

    bool y_err = y > MAX;
    bool x_err = x > MAX ;
    if (y_err || x_err) {
        if (y_err)
            cout << "ERROR: height > " << MAX << endl;
        if (x_err)
            cout << "ERROR: width > " << MAX << endl;

        return -1;
    }

    switch(interface) {
    case Interface::Terminal: {
        TerminalInterface ti(y, x, debug);
        ti.run();
        break;
    }
    case Interface::SDL: {
        SDLInterface sdl(y, x, debug);
        if (!sdl.run())
            return -1;
        break;
    }
    // TODO:
    // add a ton of ports(:<
    }


    return 0;
}

