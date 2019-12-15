#include "gameObjects.hpp"

void gameObjects::update()
{
    GOd.y = posAtY;
    GOd.x = posAtX;
}

string gameObjects::getTitle()
{
    return type;
}

SDL_Rect *gameObjects::getRect()
{
    return &GOd;
}

void gameObjects::render()
{
    SDL_RenderCopy(renderer, objectTexture, NULL, &GOd);
}

void gameObjects::setSize(int x, int y)
{
    GOd.h = x;
    GOd.w = y;
}

void gameObjects::setXPos(float x)
{
    posAtX = x;
}

void gameObjects::setYPos(float y)
{
    posAtY = y;
}

void gameObjects::setPosition(float x, float y)
{
    posAtX = x;
    posAtY = y;
}

float gameObjects::getX()
{
    return posAtX;
}
float gameObjects::getY()
{
    return posAtY;
}
