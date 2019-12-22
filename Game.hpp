#ifndef GAMECLASS
#define GAMECLASS

#include <iostream>
#include <vector>
#include <cstdlib>

#include "Main.hpp"

class Game
{
public:
    Game(int, int, int, bool *);
    std::vector<Pixel> getChangedPixels();
    void passInput(std::string);
    void update();
private:
    typedef struct
    {
        int x;
        int y;
    } Location;

    int MapSizeX;
    int MapSizeY;

    std::string Direction = "left";

    std::vector<Location> Body;
    std::vector<Location> PastBody;
    Location Target;
    bool * quit;
};

#endif
