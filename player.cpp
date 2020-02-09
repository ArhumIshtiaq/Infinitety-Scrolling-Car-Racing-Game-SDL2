#include "player.hpp"

player::player(const char *texturepath, SDL_Renderer *ren, int x, int y, trafficList *allObs, perkList *allPerks)
{
    totalObstacles = allObs;
    totalPowers = allPerks;
    renderer = ren;
    objectTexture = textureManager::loadTexture(texturepath, renderer);
    posAtX = x;
    posAtY = y;
    objectDimensions.h = 60;
    objectDimensions.w = 30;
    health = 100;
    score = 0;
    speed = 8;
    sheild = false;
    type = "Player";
    cout << "Player health:" << health << endl;
}

void player::setScore(int x)
{
    score = x;
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
    objectDimensions.y = posAtY;
    objectDimensions.x = posAtX;
    collisionDetection();
    if (health <= 0)
    {
        cout << "Game Over!" << endl;
    }
}

void player::collisionDetection()
{
    for (int i = 0; i < totalObstacles->size(); i++)
    {
        if (SDL_HasIntersection(&objectDimensions, totalObstacles->at(i)->getRect()))
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
        if (SDL_HasIntersection(&objectDimensions, totalPowers->at(i)->getRect()))
        {
            if (totalPowers->at(i)->getspecial() == "shield")
            {
                activateSheild();
                objectTexture = textureManager::loadTexture("assets/shielded.png", renderer);
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
        posAtX += (speed / 2);
        if (posAtX >= 480)
        {
            posAtX = 479;
        }
    }
    else if (direction == "left")
    {
        posAtX -= (speed / 2);
        if (posAtX <= 300)
        {
            posAtX = 301;
        }
    }
    else if (direction == "up")
    {
        posAtY -= (speed / 3) * 2;
        if (posAtY < 0)
        {
            posAtY = 0;
        }
    }
    else if (direction == "down")
    {
        posAtY += (speed / 3) * 2;
        if (posAtY >= 530)
        {
            posAtY = 529;
        }
    }
}

void player::activateSpeed()
{
    cout << "SPEED POWERUP" << endl;
    speed = this->speed * 1.2;
}

void player::activateSheild()
{
    cout << "SHIELD POWERUP" << endl;
    sheild = true;
    sheildTimer = SDL_GetTicks() + 5000;
}

int player::getScore()
{
    return score;
}

void player::resetScore()
{
    score = 0;
}

void player::normalize()
{

    if (sheildTimer < SDL_GetTicks() && sheild)
    {
        setSize(60, 30);
        objectTexture = textureManager::loadTexture("assets/Player.png", renderer);
        sheild = false;
    }
}

void player::reset()
{
    resetScore();
    health = 100;
    speed = 8;
    sheild = false;
}

player::~player(){};
