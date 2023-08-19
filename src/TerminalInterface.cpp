#include "TerminalInterface.h"

TerminalInterface::TerminalInterface(unsigned int height, unsigned int width, bool db) 
        : Game(height, width), debug(db)  {    }


void TerminalInterface::run() {
    Input input = Input::Nothing;
    while (input != Input::Quit) {
        if (debug) {
            debug_print();
        } else {
            print();
        }
        
        string in;
        cin >> in;
        if (in.empty())
            continue;
        else
            input = get_input(in[0]);
        
        if (input == Input::Error)
            continue;
        else if (input == Input::Quit)
            break;

        size_t count = 1;
        if (in.size() > 1) {
            string number = in.substr(1);
            try {
                count = stoi(in.substr(1));
            } catch (invalid_argument err) {
                cout << "Invalid argument: " << number << endl;
            } catch (out_of_range err) {
                cout << "Out of range: " << number << endl;
            }
        }
        
        tick(input, count);
    }
}

Input TerminalInterface::get_input(char c) {
    switch (c) {
    case 'w':
        return Input::Up;
    case 's':
        return Input::Down;
    case 'a':
        return Input::Left;
    case 'd':
        return Input::Right;
    case 'q':
        return Input::Quit;
    default:
        return Input::Nothing;
    }
}