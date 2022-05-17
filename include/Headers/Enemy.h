#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity
{
public:
Enemy *next;

Enemy(float x_ = 0, float y_ = 0, int w_ = 0, int h_ = 0, float dx_ = 0, float dy_ = 0, int health_ = 0, int angle_ = 0, int reload_ = 0, int r = 0, SDL_Texture* tex = NULL, Enemy *n = NULL) : Entity(x_, y_, w_, h_, dx_, dy_, health_, angle_, reload_, r, tex)
{next = n;}

void move(Player *player)
{
    this->angle = getAngle(this->x, this->y, player->x, player->y);

	calcSlope(player->x, player->y, this->x, this->y, &this->dx, &this->dy);
}
};

#endif