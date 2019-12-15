#pragma once

#include "game.hpp"

class textureManager
{
public:
    static SDL_Texture *Loadtexture(const char *filepath, SDL_Renderer *ren);
};
