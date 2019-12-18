#pragma once

#include "Game.hpp"
#include <SDL_ttf.h>

class textureManager
{
public:
    static SDL_Texture *Loadtexture(const char *filepath, SDL_Renderer *ren);
    static SDL_Texture* LoadtextureFromText (const char* textToRender, SDL_Color textColor, int textSize, SDL_Renderer* ren);
    ~TextureManager();
};
