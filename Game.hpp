#pragma once
#include "SDL.h"
#include <SDL_image.h>
#include <iostream>
#include <time.h>
#include <sstream>

using namespace std;
class game
{
public:
    game();
    ~game();

    void init(const char *title, int posAtX, int posAtY, int height, int width);
    void update();
    void render();
    void clean();
    void HandleEvents();
    bool running();
    bool getStartScreen();
    bool getPaused();
    void levelChanged();
    std::string loadHighScore(const char* filename);
    void saveScore(const char* filename, float score);
    Uint32 getTime();
    void resetTime();

private:
    static game *instance;
    bool startScreen;
    bool paused;
    bool playing;
    string currentScreen;
    SDL_Rect dataRect;
    SDL_Texture *dataTexture;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint32 currTime = 0;
    Uint32 startTime = 0;
    int score = 0;

    static game *getInstance();
};
