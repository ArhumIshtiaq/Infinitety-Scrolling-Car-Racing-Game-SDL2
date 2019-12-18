#include "perk.hpp"
#include "textureManager.hpp"
perk::perk(const char *texturepath, SDL_Renderer *ren, int x, int y)
{
    renderer = ren;
    objectTexture = textureManager::loadTexture(texturepath, renderer);
    posAtX = x;
    posAtY = y;
    objectDimensions.h = 32;
    objectDimensions.w = 32;
    type = "perk";
}

void perk::update()
{
    posAtY += verticalspeed;
    objectDimensions.y = posAtY;
    objectDimensions.x = posAtX;
}

string perk::getspecial()
{
    return special;
}

void perk::setSpecial(string num)
{
    special = num;
}
