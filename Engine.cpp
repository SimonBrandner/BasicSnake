#include "Engine.hpp"

Engine::Engine(int windowSizeX, int windowSizeY, int scaleX, int scaleY, bool * q) // Constructor
{
    SDL_Init(SDL_INIT_VIDEO); // SDL init

    // SDL Variables
    sdlWindow = SDL_CreateWindow("My application", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSizeX, windowSizeY, 0);
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC);
    // SDL Variables

    SDL_RenderSetScale(sdlRenderer, scaleX, scaleY);
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderPresent(sdlRenderer);

    game = new Game(10, windowSizeX/scaleX, windowSizeY/scaleY, quit); // Initialize game
    quit = q;
}

void Engine::update()
{
    // Variables
    std::vector<Pixel> changedPixels;
    // Variables

    // Events
    SDL_PollEvent(&sdlEvent);
    std::string pressedKey = handleSDLEvent();
    // Events

    // Interaction with the game object
    game->passInput(pressedKey); // Pass input into the game object
    if (loopNumber > 10)
    {
        game->update();
        loopNumber = 0;
    }
    changedPixels = game->getChangedPixels(); // Get changed pixels

    // Interaction with the game object

    renderFrame(changedPixels); // Render frame
    loopNumber++;
}

void Engine::renderFrame(std::vector<Pixel> changedPixels)
{
    for (int i = 0; i < changedPixels.size(); i++)
    {
        SDL_SetRenderDrawColor(sdlRenderer, changedPixels[i].red, changedPixels[i].green, changedPixels[i].blue, changedPixels[i].opacity);
        SDL_RenderDrawPoint(sdlRenderer, changedPixels[i].x, changedPixels[i].y);
    }

    SDL_RenderPresent(sdlRenderer);
}

std::string Engine::handleSDLEvent()
{
    if(sdlEvent.type == SDL_QUIT)
    {
        *quit = true;
        return "quit";
    }
    else if(sdlEvent.type == SDL_KEYDOWN)
    {
        switch(sdlEvent.key.keysym.sym)
        {
            case SDLK_q:
            *quit = true;
            break;

            case SDLK_UP:
            return "down";
            break;

            case SDLK_DOWN:
            return "up";
            break;

            case SDLK_LEFT:
            return "left";
            break;

            case SDLK_RIGHT:
            return "right";
            break;
        }
    }
    return "none";
}
