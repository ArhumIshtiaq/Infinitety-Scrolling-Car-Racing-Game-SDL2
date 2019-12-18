#include "Player.hpp"

player::player(const char *texturepath, SDL_Renderer *ren, int x, int y, trafficList *allobtacles, perkList *allpows)
{
    totalObstacles = allobtacles;
    totalPowers = allpows;
    renderer = ren;
    objectTexture = textureManager::Loadtexture(texturepath, renderer);
    posAtX = x;
    posAtY = y;
    GOd.h = 60;
    GOd.w = 30;
    health = 100;
    speed = 8;
    sheild = false;
    type = "Player";
    cout << "Player health:" << health << endl;
}

int player::getHealth()
{
    return health;
}

int player::getSpeed()
{
    return speed;
}

void player::update()
{
    GOd.y = posAtY;
    GOd.x = posAtX;
    collisionDetection();
    if (health < 0)
    {
        cout << "Game Over!" << endl;
    }
}

void player::collisionDetection()
{
    for (int i = 0; i < totalObstacles->size(); i++)
    {
        if (SDL_HasIntersection(&GOd, totalObstacles->at(i)->getRect()))
        {
            if (!sheild)
                health -= totalObstacles->at(i)->effect();
            cout << "Player health:" << health << endl;
            totalObstacles->removeAt(i);
            break;
        }
    }
    for (int i = 0; i < totalPowers->size(); i++)
    {
        if (SDL_HasIntersection(&GOd, totalPowers->at(i)->getRect()))
        {
            // for powerups
            if (totalPowers->at(i)->getspecial() == "shield")
            {
                activateSheild();
                objectTexture = textureManager::Loadtexture("assets/shielded.png", renderer);
                setSize(66, 33);
                totalPowers->removeAt(i);
                break;
            }
            if (totalPowers->at(i)->getspecial() == "speed")
            {
                activateSpeed();
                totalPowers->removeAt(i);
                break;
            }
        }
    }
    normalize();
}

void player::move(string direction)
{
    if (direction == "right")
    {
        posAtX += speed;
    }
    else if (direction == "left")
    {
        posAtX -= speed;
    }
    else if (direction == "up")
    {
        posAtY -= (speed / 3) * 2;
    }
    else if (direction == "down")
    {
        posAtY += (speed / 3) * 2;
    }
}

void player::activateSpeed()
{
    cout << "SPEED POWERUP" << endl;
    speed = 15;
    speedTimer = SDL_GetTicks() + 5000;
}

void player::activateSheild()
{
    cout << "SHIELD POWERUP" << endl;
    sheild = true;
    sheildTimer = SDL_GetTicks() + 5000;
}

void player::normalize()
{
    if (speedTimer < SDL_GetTicks())
    {
        speed = 8;
    }
    if (sheildTimer < SDL_GetTicks() && sheild)
    {
        setSize(60, 30);
        objectTexture = textureManager::Loadtexture("assets/Player.png", renderer);
        sheild = false;
    }
}

player::~player(){};
