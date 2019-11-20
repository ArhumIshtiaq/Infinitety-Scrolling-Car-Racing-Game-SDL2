#pragma once
#include "Items.hpp"

class loc3Items
{
    Item item1;
    Item item2;
    Item item3;
    Item item4;
    Item item5;
    static loc3Items getInstance();
    Item* aquireItem();
    void releaseItem();
};