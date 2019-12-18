#include "textureManager.hpp"

SDL_Texture *textureManager::Loadtexture(const char *filepath, SDL_Renderer *ren)
{
    SDL_Surface *temp = IMG_Load(filepath);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, temp);
    SDL_FreeSurface(temp);
    return tex;
}

SDL_Texture* textureManager::LoadtextureFromText(const char* textToRender, SDL_Color textColor, int textSize, SDL_Renderer* ren){
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    TTF_Font *font = TTF_OpenFont( "arial.ttf", textSize );
    SDL_Surface *tempTextSurface = TTF_RenderText_Solid( font, textToRender, textColor);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren,tempTextSurface);
    SDL_FreeSurface(tempTextSurface);
    return tex;
}

textureManager::~TextureManager(){
};