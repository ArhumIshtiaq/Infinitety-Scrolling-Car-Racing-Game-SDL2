#include "ExitButton.hpp"


void ExitButton::click(SDL_Rect*)
{
    int x, y;
    SDL_Event event;

    while(1)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    close();
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.motion.y;
                    if(x>=13 && x<=256 && y>=791 && y<=881)
                    {
                        close();
                    }
                    break;

            }
        }
    }
}