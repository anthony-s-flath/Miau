#ifndef TERMINALINTERFACE_H
#define TERMINALINTERFACE_H

#include "Identifier.h"
#include "Game.h"

using namespace std;


class TerminalInterface : public Game {
private:
    const bool debug;

public:
    TerminalInterface(unsigned int height, unsigned int width, bool db);
    void run();

private:
    Input get_input(char c);
};

#endif