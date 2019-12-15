#pragma once
#include "textureManager.hpp"
#include <time.h>
#include "game.hpp"
#include "gameObjects.hpp"
#include "traffic.hpp"

class NodeObstacle
{
public:
    Traffic *data;
    NodeObstacle *next;

    NodeObstacle(Traffic *p)
    {
        data = p;
        next = nullptr;
    }
};

class trafficList
{
public:
    NodeObstacle *head;

    trafficList();
    int size();
    void append(Traffic *data);
    void remove();
    void removeAt(int idx);
    Traffic *at(int idx);
};
