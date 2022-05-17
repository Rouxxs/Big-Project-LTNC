#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Item : public Entity
{
public:
Item *next;
int type;

Item(float x_ = 0, float y_ = 0, int w_ = 0, int h_ = 0, float dx_ = 0, float dy_ = 0, int health_ = FPS*5, int angle_ = 0, int reload_ = 0, int r = 0, SDL_Texture* tex = NULL, Item *n = NULL) : Entity(x_, y_, w_, h_, dx_, dy_, health_, angle_, reload_, r, tex)
{next = n;}

};

#endif