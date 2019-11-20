#pragma once
#include "Items.hpp"

class loc1Items
{
    Item item1;
    Item item2;
    Item item3;
    Item item4;
    Item item5;
    static loc1Items getInstance();
    Item* aquireItem();
    void releaseItem();
};