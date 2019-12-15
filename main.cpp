#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "game.hpp"

using namespace std;

int main(int argc, char **argv)
{
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const int fps = 60;
    const int frameDelay = 1000 / fps;

    Uint32 frameStart;
    int frameTime;

    game *Game = new game();
    Game->init("CRAZY TAXI v2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);

    while (Game->running())
    {

        frameStart = SDL_GetTicks();

        Game->HandleEvents();
        Game->update();
        Game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    return 0;
}
