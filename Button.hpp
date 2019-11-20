#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>

class Button
{
    int w;
    int h;
    SDL_Rect* rect;
    void click(SDL_Rect*);
    void hover();
    void setText(string);
};