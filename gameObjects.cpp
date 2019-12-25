#include "gameObjects.hpp"

void gameObjects::update()
{
    objectDimensions.y = posAtY;
    objectDimensions.x = posAtX;
}

SDL_Rect *gameObjects::getRect()
{
    return &objectDimensions;
}

void gameObjects::render()
{
    SDL_RenderCopy(renderer, objectTexture, NULL, &objectDimensions);
}

void gameObjects::setSize(int x, int y)
{
    objectDimensions.h = x;
    objectDimensions.w = y;
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
