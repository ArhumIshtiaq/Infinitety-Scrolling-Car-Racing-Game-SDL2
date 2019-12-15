#include "texture.hpp"

texture::texture(std::string path, SDL_Window *gWindow, SDL_Renderer *gRenderer)
{
    //Initialize
    mTexture = NULL;
    loadFromFile(path, gWindow, gRenderer);
    mWidth = 0;
    mHeight = 0;
}

texture::~texture()
{
    //Deallocate
    this->free(mTexture);
}

void texture::render(int x, int y, SDL_Renderer *gRenderer, SDL_Rect *clip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

bool texture::loadFromFile(std::string path, SDL_Window *gWindow, SDL_Renderer *gRenderer)
{
    //Get rid of preexisting texture
    free(mTexture);

    //The final texture
    SDL_Texture *newTexture = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Convert surface to display format
        SDL_Surface *formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_GetWindowPixelFormat(gWindow), 0);
        if (formattedSurface == NULL)
        {
            printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //Create blank streamable texture
            newTexture = SDL_CreateTexture(gRenderer, SDL_GetWindowPixelFormat(gWindow), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
            if (newTexture == NULL)
            {
                printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
            }
            else
            {
                //Lock texture for manipulation
                SDL_LockTexture(newTexture, NULL, &mPixels, &mPitch);

                //Copy loaded/formatted surface pixels
                memcpy(mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

                //Unlock texture to update
                SDL_UnlockTexture(newTexture);
                mPixels = NULL;

                //Get image dimensions
                mWidth = formattedSurface->w;
                mHeight = formattedSurface->h;
            }

            //Get rid of old formatted surface
            SDL_FreeSurface(formattedSurface);
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void texture::free(SDL_Texture *mTexture)
{
    SDL_DestroyTexture(mTexture);
}