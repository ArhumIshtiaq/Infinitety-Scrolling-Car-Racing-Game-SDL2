#pragma once
#include "textureManager.hpp"
#include <time.h>
#include "game.hpp"
#include "gameObjects.hpp"
#include "trafficList.hpp"
#include "perk.hpp"

class Node
{
public:
    perk *data;
    Node *next;

    Node(perk *p)
    {
        data = p;
        next = nullptr;
    }
};

class perkList
{
public:
    Node *head;
    perkList();
    int size();
    void append(perk *data);
    void remove();
    void removeAt(int idx);
    perk *at(int idx);
};
