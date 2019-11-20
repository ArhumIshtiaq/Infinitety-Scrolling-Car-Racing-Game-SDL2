#pragma once
#include "Items.hpp"

class itemsPool
{
    Item item1;
    Item item2;
    Item item3;
    Item item4;
    Item item5;
    static itemsPool getInstance();
    Item* aquireItem();
    void releaseItem();
}