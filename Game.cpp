#ifndef GAME
#define GAME

#include "Game.hpp"

Game::Game(int length, int mapSizeX, int mapSizeY, bool * q) : MapSizeX(), MapSizeY(), quit()
{
    // Variables
    MapSizeX = mapSizeX;
    MapSizeY = mapSizeY;
    quit = q;
    // Variables

    for(int i = 0; i < (length - 1); i++)
    {
        PastBody.push_back({0, 0});
    }

    for(int i = 0; i < (length - 1); i++)
    {
        Body.push_back({MapSizeX/2 + i, MapSizeY/2});
    }

    Target.x = MapSizeX/2 - 1;
    Target.y = MapSizeY/2;
}

std::vector<Pixel> Game::getChangedPixels()
{
    std::vector<Pixel> changedPixels;
    // Snake
    for(int i = 0; i < Body.size(); i++)
    {
        if(!(Body[i].x == PastBody[i].x) || !(Body[i].y == PastBody[i].y))
        {
            changedPixels.push_back({Body[i].x, Body[i].y, 0, 255, 0});
        }
    }
    if (Body.size() == PastBody.size())
    {
        changedPixels.push_back({PastBody[PastBody.size()-1].x, PastBody[PastBody.size()-1].y, 0, 0, 0});
    }
    // Snake

    // Target
    changedPixels.push_back({Target.x, Target.y, 255, 0, 0});
    // Target
    return changedPixels;
}

void Game::passInput(std::string pressedKey)
{
    if (pressedKey == "none"){return;}
    if (pressedKey == "right" && Direction == "left"){return;}
    else if(pressedKey == "left" && Direction == "right"){return;}
    else if(pressedKey == "up" && Direction == "down"){return;}
    else if(pressedKey == "down" && Direction == "up"){return;}

    else
    {
        Direction = pressedKey;
    }
}

void Game::update()
{
    PastBody = Body;
    Location value;

    if(Direction == "right")
    {
        value.x = Body[0].x + 1;
        value.y = Body[0].y;
    }
    else if(Direction == "left")
    {
        value.x = Body[0].x - 1;
        value.y = Body[0].y;
    }
    else if(Direction == "up")
    {
        value.x = Body[0].x;
        value.y = Body[0].y + 1;
    }
    else if(Direction == "down")
    {
        value.x = Body[0].x;
        value.y = Body[0].y - 1;
    }

    Body.insert(Body.begin(), value);

    if(value.x > MapSizeX || value.x < 0 || value.y > MapSizeY || value.y < 0) // Quit if snake run out of the map
    {
        *quit = true;
    }
    for (int i = 0; i < Body.size(); i++) // Quit game if snake collided itself
    {
        if (PastBody[i].x == Body[0].x && PastBody[i].y == Body[0].y)
        {
            *quit = true;
        }
    }

    if (Target.x == Body[0].x && Target.y == Body[0].y) // Got target
    {
        int foundTargetPosition = false;
        while(!foundTargetPosition)
        {
            foundTargetPosition = true;
            Target.x = rand() % MapSizeX;
            Target.y = rand() % MapSizeY;
            for (int i = 0; i < Body.size(); i++) {
                if(Target.x == Body[i].x && Target.y == Body[i].y)
                {
                    foundTargetPosition = false;
                    break;
                }
            }
        }
        return;
    }

    Body.pop_back();
}

#endif
