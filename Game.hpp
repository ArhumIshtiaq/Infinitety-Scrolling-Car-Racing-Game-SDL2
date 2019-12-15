#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "texture.hpp"

class Game
{
public:
    bool isRunning;
    SDL_Renderer *renderer;
    SDL_Window *window;



    static int obj_count;
    // void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    // void handleEvents();
    // void update();
    bool loadMedia();
    // void render();
    // void clean();
    // bool running();
    bool init();
    bool loadBG();
    void close();
};