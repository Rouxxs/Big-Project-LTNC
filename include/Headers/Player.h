#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "const.h"
#include "Item.h"

class Player : public Entity
{
public:
	int weaponType;
	int ammo[WPN_MAX];

	Player();

	void move(int keyboard[]);

	void touchItem(Item *i);
};

#endif