#include "game.hpp"
#include "textureManager.hpp"
#include "gameObjects.hpp"
#include "player.hpp"
#include "traffic.hpp"
#include "trafficList.hpp"
#include "perkList.hpp"
#include "itemFactory.hpp"

game::game()
{
    paused = true;
    startScreen = true;
    currentScreen = "selectStart";
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

    backgroundTexture = textureManager::Loadtexture(bg.c_str(), renderer);
    srcRect.w = 800;
    srcRect.h = 400;
    backgroundRect.x = backgroundRect.y = 0;
    backgroundRect.h = 600;
    backgroundRect.w = srcRect.w;
    srcRect.y = 0;

    Player = new player("assets/player.png", renderer, 400, 500, allTraffic, allPerks);
    Player->setSize(60, 30);
    allItems = new itemFactory(allTraffic, allPerks, renderer);
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

    if (!getStartScreen())
    {
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
            startScreen = true;
            paused = !paused;
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
                        currentScreen = "quit";
                    }
                    else if (keyState[SDL_SCANCODE_RETURN])
                    {
                        currentScreen = "instructions";
                    }
                }
                else if (currentScreen == "quit")
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
    if (!startScreen && !paused)
    {

        if (srcRect.y > 20)
        {
            srcRect.y -= Player->getSpeed()/4;
            
        }
        else
        {
            srcRect.y = 200;
        }

        if (Player->getHealth() <= 0)
        {
            isRunning = false;
        }

        for (int i = 0; i < allTraffic->size(); i++)
        {
            allTraffic->at(i)->update();
        }

        for (int i = 0; i < allPerks->size(); i++)
        {
            allPerks->at(i)->update();
        }

        Player->update();

        allItems->update();
    }
}

void game::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, &srcRect, &backgroundRect);

    if (getStartScreen())
    {
        SDL_Rect fullScreenRect;
        fullScreenRect.w = 800;
        fullScreenRect.h = 600;
        fullScreenRect.x = 0;
        fullScreenRect.y = 0;

        SDL_Texture *screen;

        if (currentScreen == "selectStart")
        {
            screen = textureManager::Loadtexture("assets/start.png", renderer);
        }
        else if (currentScreen == "selectInstructions")
        {
            screen = textureManager::Loadtexture("assets/instructions.png", renderer);
        }
        else if (currentScreen == "quit")
        {
            screen = textureManager::Loadtexture("assets/exit.png", renderer);
        }
        else if (currentScreen == "instructions")
        {
            screen = textureManager::Loadtexture("assets/nn.png", renderer);
        }
        else if (currentScreen == "paused")
        {
            screen = textureManager::Loadtexture("assets/paused.png", renderer);
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
    };
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

void game::levelChanged()
{

}