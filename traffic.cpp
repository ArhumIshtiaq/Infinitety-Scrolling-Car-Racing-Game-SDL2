#include "traffic.hpp"

Traffic::Traffic(const char *texturepath, SDL_Renderer *ren, int x, int y)
{
    renderer = ren;
    objectTexture = textureManager::Loadtexture(texturepath, renderer);
    posAtX = x;
    posAtY = y;
    GOd.h = 60;
    GOd.w = 30;
    type = "Traffic";
}

void Traffic::setSpeed(int num)
{
    verticalspeed = num;
}

int Traffic::effect()
{
    return damage;
}

void Traffic::setDamage(int num)
{
    damage = num;
}

void Traffic::update()
{
    posAtY += rand()%5 + 5;
    GOd.y = posAtY;
    GOd.x = posAtX;
}