#include "itemFactory.hpp"
#include <time.h>

itemFactory::itemFactory(trafficList *traffic, perkList *pows, SDL_Renderer *renderer)
{
    ren = renderer;
    tList = traffic;
    pList = pows;
    timedelay = 5;

    perkAssets[0] = new perk("assets/speed.png", ren, rand() % 300 + 300, -10);
    perkAssets[0]->setSpecial("speed");
    perkAssets[1] = new perk("assets/shield.png", ren, rand() % 300 + 300, -10);
    perkAssets[1]->setSpecial("shield");

    obstacleAssets[0] = new Traffic("assets/enemy1.png", ren, rand() % 300 + 300, -10);
    obstacleAssets[0]->setDamage(5);
    obstacleAssets[1] = new Traffic("assets/enemy2.png", ren, rand() % 300 + 300, -10);
    obstacleAssets[1]->setDamage(7);
    obstacleAssets[2] = new Traffic("assets/enemy3.png", ren, rand() % 300 + 300, -10);
    obstacleAssets[2]->setDamage(10);
}

void itemFactory::update()
{
    if (perkSpeed < SDL_GetTicks())
    {
        perk *tempPerk = new perk(*perkAssets[rand() % 2]);
        tempPerk->setXPos(lanes[rand() % 3]);
        pList->append(new perk(*tempPerk));
        perkSpeed = SDL_GetTicks() + 4000;
    }

    if (trafficSpeed < SDL_GetTicks())
    {
        Traffic *tempTraffic = new Traffic(*obstacleAssets[rand() % 3]);
        tempTraffic->setXPos(lanes[rand() % 3]);
        tList->append(tempTraffic);
        trafficSpeed = SDL_GetTicks() + 300;
    }

    freeMem();
}

void itemFactory::freeMem()
{
    for (int i = 0; i < tList->size(); i++)
    {
        if (tList->at(i)->getY() > 600)
        {
            tList->removeAt(i);
        }
    }
    for (int i = 0; i < pList->size(); i++)
    {
        if (pList->at(i)->getY() > 600)
        {
            pList->removeAt(i);
        }
    }
}

int itemFactory::increaseTrafficSpeed()
{
    if (SDL_GetTicks() % 500 == 0)
    {
        trafficGenFactor -= 20 * (SDL_GetTicks() / 500);
    }
    return trafficGenFactor;
};