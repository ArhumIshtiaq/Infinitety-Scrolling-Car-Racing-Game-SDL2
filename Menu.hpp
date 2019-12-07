#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Game.hpp"

class Menu
{
    public:
        SDL_Surface* background;
        string event;
        void click(string, SDL_Renderer*);
        void show(SDL_Surface*);
};

void Menu::show(SDL_Surface* screen)
{
    int x,y;
    const int numMenu = 3;
    const char* label[numMenu] = {"Start", "How to Play", "Exit"};
    SDL_Surface* menus[numMenu];
    bool selected[numMenu] = {0,0,0};
    menus[0] = IMG_Load("Assets/thumbnail_sprite-01.png");
    menus[1] = IMG_Load("Assets/thumbnail_sprite-02.png");
    menus[2] = IMG_Load("Assets/thumbnail_sprite-3.png");
    SDL_Rect pos[numMenu];
    pos[0].x = screen->clip_rect.w/2 - menus[0]->clip_rect.h/2;
    pos[0].y = screen->clip_rect.h/2 - menus[0]->clip_rect.h;
    pos[1].x = screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
    pos[1].y = screen->clip_rect.h/2 + menus[0]->clip_rect.h;

    SDL_Event MenuEvent;

    while(1)
    {
        while(SDL_PollEvent(&MenuEvent))
        {
            switch(MenuEvent.type)
            {
                case SDL_QUIT:
                    for (int i = 0; i < numMenu; i++)
                    {
                        SDL_FreeSurface(menus[i]);
                    }
                    clean();
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = MenuEvent.button.x;
                    y = MenuEvent.motion.y;
                    for(int i = 0; i < numMenu; i += 1) {
                        if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
                        {
                            if(!selected[i])
                            {
                                selected[i] = 1;
                                event = label[i];
                                click(event, gRenderer)

                            }
                        }
                    break;
            }
        }
    }

}

void Menu::click(string event, SDL_Renderer* Renderer)
{
    switch (event)
        case "Start":
            break;
        case "How to Play":
            break;
        case "Exit":
            for (int i = 0; i < numMenu; i++)
                {
                    SDL_FreeSurface(menus[i]);
                }
            clean(); 
            break;
}