#include "Enemy.h"

void Enemy::move(Player *player)
{
    this->angle = getAngle(this->x, this->y, player->x, player->y);

    calcSlope(player->x, player->y, this->x, this->y, &this->dx, &this->dy);
}