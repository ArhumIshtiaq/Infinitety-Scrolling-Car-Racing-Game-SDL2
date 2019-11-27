#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Menu
{
    public:
        SDL_Surface* background;
        void click(SDL_Renderer*);
        void show(SDL_Surface*);
};

void Menu::show(SDL_Surface* screen)
{
    int x,y;
    const int numMenu = 3;
    const char* label[numMenu] = {"Start", "How to Play", "Exit"};
    SDL_Surface* menus[numMenu];
    bool selected[numMenu] = {0,0,0};
    menus[0] = ;
    menus[1] = ;
    SDL_Rect pos[numMenu];
    pos[0].x = screen->clip_rect.w/2 + menus[0]->clip.h/2;
}