#include "itemFactory.hpp"
#include <time.h>

itemFactory::itemFactory(trafficList *traffic, perkList *perks, SDL_Renderer *renderer)
{
    ren = renderer;
    tList = traffic;
    pList = perks;
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
        perk *tempPerk = new perk(*perkAssets[1]);
        tempPerk->setXPos(lanes[rand() % 3]);
        pList->append(new perk(*tempPerk));
        perkSpeed = SDL_GetTicks() + 6000;
    }

    if (checkpointSpeed < SDL_GetTicks())
    {
        perk *tempPerk = new perk(*perkAssets[0]);
        tempPerk->setXPos(lanes[rand() % 3]);
        pList->append(new perk(*tempPerk));
        checkpointSpeed = SDL_GetTicks() + 10000;
    }

    if (trafficSpeed < SDL_GetTicks())
    {
        Traffic *tempTraffic = new Traffic(*obstacleAssets[rand() % 3]);
        tempTraffic->setXPos(lanes[rand() % 3]);
        tList->append(tempTraffic);
        trafficSpeed = SDL_GetTicks() + trafficGenFactor;
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

void itemFactory::deleteAllItems()
{
    for (int i = 0; i < tList->size(); i++)
    {
        tList->removeAt(i);
    }
    for (int i = 0; i < pList->size(); i++)
    {
        pList->removeAt(i);
    }
}

void itemFactory::increaseTrafficSpeed()
{
    trafficGenFactor = trafficGenFactor / 1.2;
};

void itemFactory::resetTrafficSpeed()
{
    trafficGenFactor = 1000;
}