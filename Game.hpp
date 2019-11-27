#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Game
{
    public:
        bool isRunning;
        SDL_Renderer* renderer;
        SDL_Window* window;
        SDL_Texture* bg;
        static int obj_count;
        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void handleEvents();
        void update();
        void render();
        void clean();
        bool running();
};