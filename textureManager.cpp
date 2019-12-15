#include "textureManager.hpp"

SDL_Texture *textureManager::Loadtexture(const char *filepath, SDL_Renderer *ren)
{
    SDL_Surface *temp = IMG_Load(filepath);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, temp);
    SDL_FreeSurface(temp);
    return tex;
}
