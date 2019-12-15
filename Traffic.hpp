#pragma once
#include "gameObjects.hpp"

class Traffic : public gameObjects
{
private:
    int verticalspeed = rand() % 2 + 3;
    int damage = 5;

public:
    virtual void update();
    Traffic(const char *texturepath, SDL_Renderer *ren, int x, int y);
    void setSpeed(int num);
    int effect();
    void setDamage(int num);
};
