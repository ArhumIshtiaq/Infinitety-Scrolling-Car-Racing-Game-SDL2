#pragma once

#include "game.hpp"

class textureManager
{
public:
    static SDL_Texture *loadTexture(const char *filepath, SDL_Renderer *ren);
    static SDL_Texture *loadText(const char *textToRender, SDL_Color color, int fontSize, SDL_Renderer *ren);
};