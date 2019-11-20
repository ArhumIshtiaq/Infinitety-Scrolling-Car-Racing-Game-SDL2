#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string.h>
#include "loc1Items.hpp"
#include "loc2Items.hpp"
#include "loc3Items.hpp"

class Item : public loc1Items, public loc2Items, public loc3Items
{
    SDL_Image sprite;
    int score;
    Item();
};