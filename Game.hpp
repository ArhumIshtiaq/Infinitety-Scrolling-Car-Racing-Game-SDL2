#pragma once
#include "SDL.h"
#include <SDL_image.h>
#include <iostream>
#include <time.h>

using namespace std;
class game
{
public:
    game();
    ~game();

    void init(const char *title, int posAtX, int posAtY, int height, int width);
    void update();
    void render();
    void clean();
    void HandleEvents();
    bool running();
    bool getStartScreen();
    bool getPaused();
    void levelChanged();

private:
    bool startScreen;
    bool paused;
    string currentScreen;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};
