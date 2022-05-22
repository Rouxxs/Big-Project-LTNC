#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Item : public Entity
{
public:
Item *next;
int type;

Item()
{
    health = FPS*5;
    radius = 16;
    color = {255, 255, 255, 255};
    next = NULL;
}

};

#endif