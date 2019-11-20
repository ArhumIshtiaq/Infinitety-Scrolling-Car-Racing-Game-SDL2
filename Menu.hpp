#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Menu
{
    public:
        SDL_Image* background;
        void click(SDL_Render*);
        void show(SDL_Image*);
};