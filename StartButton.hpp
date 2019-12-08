#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string.h>
#include "Button.hpp"

class StartButton : public Button 
{
    void click(SDL_Rect*);
    void show();
};