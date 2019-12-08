#include "StartButton.hpp"

void StartButton::click(SDL_Rect*)
{
    SDL_Event event;

    while(1)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                break;

            }
        }
    }
}

void StartButton::show()
{

}