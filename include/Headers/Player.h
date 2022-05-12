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

	Player(float x_ = 0, float y_ = 0, int w_ = 0, int h_ = 0, float dx_ = 0, float dy_ = 0, int health_ = 0, int angle_ = 0, int wbt = 0, int reload_ = 0, int r = 0, SDL_Texture* tex = NULL) : Entity(x_, y_, w_, h_, dx_, dy_, health_, angle_, reload_, r, tex)
	{
		weaponType = wbt;

		ammo[WPN_PISTOL] = 12;
		ammo[WPN_UZI] = 100;
		ammo[WPN_SHOTGUN] = 8;
	}

	void move(int keyboard[]);

	void touchItem(Item *i);
};

#endif