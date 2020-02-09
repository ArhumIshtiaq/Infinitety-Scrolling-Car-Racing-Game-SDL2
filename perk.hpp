#pragma once
#include "gameObjects.hpp"
#include "game.hpp"

class perk : public gameObjects
{
private:
    string type;
    string special;
    int verticalspeed = 5;

public:
    perk(const char *texturepath, SDL_Renderer *ren, int x, int y);
    virtual void update() override;
    string getspecial();
    void setSpecial(string num);
};
