#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string.h>
#include "Button.hpp"
#include "Game.cpp"

class ExitButton : public Button 
{
    void click(SDL_Rect*);
};