#include "Player.h"

Player::Player()
: Entity(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL)
{
    weaponType = 0;

	ammo[WPN_PISTOL] = 12; 
	ammo[WPN_UZI] = 100;
	ammo[WPN_SHOTGUN] = 8;
}

void Player::move(int keyboard[])
{
	dx *= 0.85;
	dy *= 0.85;
	
	if (keyboard[SDL_SCANCODE_W])
	{
		dy = -PLAYER_SPEED;
	}
	
	if (keyboard[SDL_SCANCODE_S])
	{
		dy = PLAYER_SPEED;
	}
	
	if (keyboard[SDL_SCANCODE_A])
	{
		dx = -PLAYER_SPEED;
	}
	
	if (keyboard[SDL_SCANCODE_D])
	{
		dx = PLAYER_SPEED;
	}

	x = MIN(MAX(x, w / 2), SCREEN_WIDTH - w / 2);
	y = MIN(MAX(y, h / 2), SCREEN_HEIGHT - h / 2);
	x += dx;
	y += dy;
		
	reload = MAX(reload - 1, 0);
}

void Player::touchItem(Item *i)
{
	int distance = getDistance(x, y, i->x, i->y);

	if (distance < radius + i->radius)
	{
		switch (i->type)
		{
		case HEATH_ITEM:
			i->health = 0;
			health++;
			break;

		case UZI_ITEM:
			i->health = 0;
			ammo[WPN_UZI] += 30;
			break;
		
		case SHOTGUN_ITEM:
			i->health = 0;
			ammo[WPN_SHOTGUN] += 4;
			break;
		
		default:
			break;
		}
	}
	return;
}