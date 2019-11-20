#pragma once
#include <iostream>

class Player
{ 
    private:
    static Player* player; 
    SDL_image sprite();
    Player() {}
  
    public:
    static Player getInstance() 
    { 
        if (player == NULL) 
            player = new Player(); 
        return *player; 
    } 

    bool checkCollision();
    void Jump();
    void moveLeft();
    void moveRight();
    void collectItem();
};