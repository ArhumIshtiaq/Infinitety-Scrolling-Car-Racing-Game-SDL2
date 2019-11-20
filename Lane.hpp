#pragma once

class Lane
{
    public:
        Lane* laneArray;
        float speed;
        void addCar();
        void removeCar();
        void move();
}