#pragma once
#include <iostream>

class Gamestate 
{ 
    private:
        static Gamestate* state; 
        Gamestate() {} 
    public:
        int score;
        static int highscore;
        int level;
        float currentTime;
    
    public:
        static Gamestate getInstance() 
        { 
            if (state==NULL) 
                state = new Gamestate(); 
            return *state; 
        } 
} 