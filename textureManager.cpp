#include "textureManager.hpp"
#include <SDL_ttf.h>

SDL_Texture *textureManager::loadTexture(const char *filepath, SDL_Renderer *ren)
{
    SDL_Surface *temp = IMG_Load(filepath);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, temp);
    SDL_FreeSurface(temp);
    return tex;
}

SDL_Texture *textureManager::loadText(const char *textToRender, SDL_Color color, int fontSize, SDL_Renderer *ren)
{
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }

    TTF_Font *font = TTF_OpenFont("assets/Raleway-Black.ttf", fontSize);
    SDL_Surface *tempTextSurface = TTF_RenderText_Solid(font, textToRender, color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tempTextSurface);
    SDL_FreeSurface(tempTextSurface);
    return tex;
}