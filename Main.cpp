#include "Engine.hpp"
#include "Game.hpp"

#include <string>
#include <iostream>
#include <curses.h>
#include <ctime>

int main( int argc, char *argv[] )
{
    bool quit = false;
    Engine engine(1024, 1024, 32, 32, &quit);

    while(!quit)
    {
        engine.update();
    }

    return 0;
}
