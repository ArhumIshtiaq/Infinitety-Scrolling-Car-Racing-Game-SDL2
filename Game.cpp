#include "game.hpp"
#include "textureManager.hpp"
#include "gameObjects.hpp"
#include "player.hpp"
#include "traffic.hpp"
#include "trafficList.hpp"
#include "perkList.hpp"
#include "itemFactory.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

game *game::instance = new game();

game::game()
{
    paused = true;
    startScreen = true;
    currentScreen = "selectStart";
}

game *game::getInstance()
{
    return instance;
}

player *Player;
trafficList *allTraffic = new trafficList;
perkList *allPerks = new perkList;
SDL_Texture *backgroundTexture;
SDL_Rect backgroundRect, srcRect;
const Uint8 *keyState;
itemFactory *allItems;
std::string bg;
time_t currentTime = time(NULL);
tm *localTime = localtime(&currentTime);

void game::init(const char *title, int posAtX, int posAtY, int width, int height)
{
    if (SDL_INIT_EVERYTHING)
    {
        window = SDL_CreateWindow("Crazy Taxi v2", posAtX, posAtY, width, height, 0);
        isRunning = true;
        renderer = SDL_CreateRenderer(window, -1, 0);

        if (window)
        {
            cout << "Window has been initialized!\n";
        }

        if (renderer)
        {
            cout << "Renderer has been created!\n";
        }
    }
    else
    {
        isRunning = false;
    }

    if (localTime->tm_hour >= 6 && localTime->tm_hour <= 18)
    {
        bg = "assets/bgd.png";
    }
    else
    {
        bg = "assets/bgn.png";
    }

    backgroundTexture = textureManager::loadTexture(bg.c_str(), renderer);
    srcRect.w = 800;
    srcRect.h = 400;
    backgroundRect.x = backgroundRect.y = 0;
    backgroundRect.h = 600;
    backgroundRect.w = srcRect.w;
    srcRect.y = 0;

    Player = new player("assets/player.png", renderer, 400, 500, allTraffic, allPerks);
    Player->setSize(60, 30);
    allItems = new itemFactory(allTraffic, allPerks, renderer);
    playing = false;
}

void game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
    keyState = SDL_GetKeyboardState(NULL);

    if (!getPaused())
    {
        if (playing == false)
        {
            playing = true;
        }

        if ((keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT]) && Player->posAtX < 480)
        {
            Player->move("right");
        }
        if ((keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT]) && Player->posAtX > 300)
        {
            Player->move("left");
        }
        if ((keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN]) && Player->posAtY < 530)
        {
            Player->move("down");
        }
        if ((keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP]) && Player->posAtY > 0)
        {
            Player->move("up");
        }
        if (keyState[SDL_SCANCODE_P])
        {
            currentScreen == "paused";
            paused = true;
        };
    }
    else
    {
        bool keyDown = false;
        switch (event.type)
        {
        case SDL_KEYDOWN:
            if (!keyDown)
            {
                if (currentScreen == "selectStart")
                {
                    if (keyState[SDL_SCANCODE_DOWN])
                    {
                        currentScreen = "selectInstructions";
                    }
                    if (keyState[SDL_SCANCODE_RETURN])
                    {
                        paused = false;
                        startScreen = false;
                        currentScreen = "paused";
                    }
                }
                else if (currentScreen == "selectInstructions")
                {
                    if (keyState[SDL_SCANCODE_UP])
                    {
                        currentScreen = "selectStart";
                    }
                    else if (keyState[SDL_SCANCODE_DOWN])
                    {
                        currentScreen = "exit";
                    }
                    else if (keyState[SDL_SCANCODE_RETURN])
                    {
                        currentScreen = "instructions";
                    }
                }
                else if (currentScreen == "exit")
                {
                    if (keyState[SDL_SCANCODE_UP])
                    {
                        currentScreen = "selectInstructions";
                    }
                    else if (keyState[SDL_SCANCODE_RETURN])
                    {
                        isRunning = false;
                    };
                }
                else if (currentScreen == "instructions")
                {
                    if (keyState[SDL_SCANCODE_RETURN])
                    {
                        currentScreen = "selectInstructions";
                    };
                }
                else if (currentScreen == "gameover")
                {
                    if (keyState[SDL_SCANCODE_RETURN])
                    {
                        paused = false;
                        Player->reset();
                        allItems->resetTrafficSpeed();
                        allItems->deleteAllItems();
                        currentScreen = "paused";
                    }
                }
                else if (currentScreen == "paused")
                {
                    if (keyState[SDL_SCANCODE_RETURN])
                    {
                        paused = false;
                    }
                }
            }
            keyDown = true;
            break;
        case SDL_KEYUP:
            keyDown = false;
            break;
        default:
            break;
        }
    }
}

bool game::running()
{
    return isRunning;
}

void game::update()
{
    if (!getPaused())
    {

        if (srcRect.y > 20)
        {
            srcRect.y -= Player->getSpeed() / 4;
        }
        else
        {
            srcRect.y = 200;
        }

        if (Player->getHealth() <= 0)
        {
            if (Player->getScore() > stoi(loadHighScore("assets/hs.txt")))
            {
                saveScore("assets/hs.txt", Player->getScore());
            }
            currentScreen = "gameover";
            paused = true;
            Player->reset();
            allItems->freeMem();
            resetTime();
            playing = false;
        }

        for (int i = 0; i < allTraffic->size(); i++)
        {
            allTraffic->at(i)->update();
        }

        for (int i = 0; i < allPerks->size(); i++)
        {
            allPerks->at(i)->update();
        }
        Player->setScore(getTime() * (Player->getSpeed() / 5));
        int oldSpeed = Player->getSpeed();
        Player->update();
        int newSpeed = Player->getSpeed();
        if (newSpeed > oldSpeed)
        {
            allItems->increaseTrafficSpeed();
        }
        allItems->update();
    }
}

void game::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, &srcRect, &backgroundRect);

    if (getPaused())
    {
        SDL_Rect fullScreenRect;
        fullScreenRect.w = 800;
        fullScreenRect.h = 600;
        fullScreenRect.x = 0;
        fullScreenRect.y = 0;

        SDL_Texture *screen;

        if (currentScreen == "selectStart")
        {
            screen = textureManager::loadTexture("assets/start.png", renderer);
        }
        else if (currentScreen == "selectInstructions")
        {
            screen = textureManager::loadTexture("assets/instructions.png", renderer);
        }
        else if (currentScreen == "exit")
        {
            screen = textureManager::loadTexture("assets/exit.png", renderer);
        }
        else if (currentScreen == "instructions")
        {
            screen = textureManager::loadTexture("assets/nn.png", renderer);
        }
        else if (currentScreen == "gameover")
        {
            screen = textureManager::loadTexture("assets/gameover.png", renderer);
        }
        else if (currentScreen == "paused")
        {
            screen = textureManager::loadTexture("assets/pause.png", renderer);
        }

        SDL_RenderCopy(renderer, screen, NULL, &fullScreenRect);
    }
    else
    {
        Player->render();
        for (int i = 0; i < allTraffic->size(); i++)
        {
            allTraffic->at(i)->render();
        }
        for (int i = 0; i < allPerks->size(); i++)
        {
            allPerks->at(i)->render();
        }

        SDL_Color color = {255, 255, 255};

        dataRect.w = 70;
        dataRect.h = 50;
        dataRect.x = 20;
        dataRect.y = 50;

        {
            std::ostringstream oss;
            oss << getTime();
            dataTexture = textureManager::loadText(oss.str().c_str(), color, 25, renderer);
            SDL_RenderCopy(renderer, dataTexture, NULL, &dataRect);
        }

        SDL_DestroyTexture(dataTexture);

        dataRect.x = 720;

        {
            std::ostringstream oss;
            oss << Player->getScore();
            dataTexture = textureManager::loadText(oss.str().c_str(), color, 25, renderer);
            SDL_RenderCopy(renderer, dataTexture, NULL, &dataRect);
        }

        SDL_DestroyTexture(dataTexture);

        dataRect.x = 720;
        dataRect.y = 0;

        {
            std::ostringstream oss;
            oss << Player->getHealth();
            dataTexture = textureManager::loadText(oss.str().c_str(), color, 25, renderer);
            SDL_RenderCopy(renderer, dataTexture, NULL, &dataRect);
        }

        SDL_DestroyTexture(dataTexture);

        dataRect.w = 200;
        dataRect.x = 20;

        {
            std::ostringstream oss;
            oss << "Highscore: " + loadHighScore("assets/hs.txt");
            dataTexture = textureManager::loadText(oss.str().c_str(), color, 25, renderer);
            SDL_RenderCopy(renderer, dataTexture, NULL, &dataRect);
        }
    }
    SDL_RenderPresent(renderer);
}

bool game::getStartScreen()
{
    return startScreen;
}

bool game::getPaused()
{
    return paused;
}

std::string game::loadHighScore(const char *path)
{
    std::string highscore;
    std::fstream file(path);

    if (file.is_open())
    {
        getline(file, highscore);
    };

    file.close();

    return highscore;
};

void game::saveScore(const char *path, float score)
{
    std::ostringstream oss;
    oss << score;
    std::fstream file(path);

    if (file.is_open())
    {
        file << oss.str().c_str();
    };

    file.close();
};

Uint32 game::getTime()
{
    return (SDL_GetTicks() - startTime) / 1000;
}

void game::resetTime()
{
    startTime = SDL_GetTicks();
}