#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string.h>

class Button
{
    SDL_Surface* button;
    virtual void click(SDL_Rect*);
};