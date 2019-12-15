#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class texture
{
public:
    //Initializes variables
    texture(std::string path, SDL_Window *gWindow, SDL_Renderer *gRenderer);

    //Deallocates memory
    ~texture();

    //Loads image at specified path
    bool loadFromFile(std::string path, SDL_Window *gWindow, SDL_Renderer *gRenderer);

    //Deallocates texture
    void free(SDL_Texture* mTexture);

    //Renders texture at given point
    void render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect *clip = NULL);

    //Gets image dimensions
    int getWidth();
    int getHeight();


private:
    //The actual hardware texture
        SDL_Texture* mTexture;
        void* mPixels;
        int mPitch;

        //Image dimensions
        int mWidth;
        int mHeight;
};