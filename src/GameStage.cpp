#include "GameStage.h"



void GameStage::initStage()
{
	targetterTexture = loadTexture("gfx/targetter.png");

	Bullet = loadTexture("gfx/Bullet.png");

	fontTexture = loadTexture("gfx/font.png");

	entityTail = &entityHead;

	bulletTail = &bulletHead;

	initPlayer();

}

void GameStage::logic()
{
	doPlayer();

	doEntities();

	doBullets();
}

void GameStage::draw()
{
	drawEntities();
	drawBullets();
	drawHud();
	blit(targetterTexture, mouse.x, mouse.y, 1);
}

void GameStage::initPlayer()
{
	
	entityTail->next = player;
	entityTail = player;
	
	player->texture = loadTexture("gfx/Player.png");
	player->health = 5;
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	player->weaponType = 0;

	ammo[WPN_PISTOL] = 12;
	ammo[WPN_UZI] = 100;
	ammo[WPN_SHOTGUN] = 8;
	
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void GameStage::fireBullet()
{
	switch (player->weaponType)
	{
		case WPN_UZI:
			fireUzi();
			break;
			
		case WPN_SHOTGUN:
			fireShotgun();
			break;
			
		default:
			firePistol();
			break;
	}
}

void GameStage::doPlayer()
{
	
	player->dx *= 0.85;
	player->dy *= 0.85;
	
	if (keyboard[SDL_SCANCODE_W])
	{
		player->dy = -PLAYER_SPEED;
	}
	
	if (keyboard[SDL_SCANCODE_S])
	{
		player->dy = PLAYER_SPEED;
	}
	
	if (keyboard[SDL_SCANCODE_A])
	{
		player->dx = -PLAYER_SPEED;
	}
	
	if (keyboard[SDL_SCANCODE_D])
	{
		player->dx = PLAYER_SPEED;
	}
	
	player->angle = getAngle(player->x, player->y, mouse.x, mouse.y);

	if (player->reload == 0 && ammo[player->weaponType] > 0 && mouse.button[SDL_BUTTON_LEFT])
	{
		fireBullet();
		
		ammo[player->weaponType]--;
	}
	
	if (mouse.wheel < 0)
	{
		if (--player->weaponType < WPN_PISTOL)
		{
			player->weaponType = WPN_MAX - 1;
		}
		
		mouse.wheel = 0;
	}
	
	if (mouse.wheel > 0)
	{
		if (++player->weaponType >= WPN_MAX)
		{
			player->weaponType = WPN_PISTOL;
		}
		
		mouse.wheel = 0;
	}
	
	if (mouse.button[SDL_BUTTON_RIGHT])
	{
		if (player->weaponType == WPN_PISTOL && ammo[WPN_PISTOL] == 0)
		{
			ammo[WPN_PISTOL] = 12;
		}
		
		mouse.button[SDL_BUTTON_RIGHT] = 0;
	}
}

void GameStage::doEntities()
{
	Entity *e;
	
	for (e = entityHead.next ; e != NULL ; e = e->next)
	{
		e->x += e->dx;
		e->y += e->dy;
		
		e->reload = MAX(e->reload - 1, 0);
		if (e == player)
		{
			e->x = MIN(MAX(e->x, e->w / 2), SCREEN_WIDTH - e->w / 2);
			e->y = MIN(MAX(e->y, e->h / 2), SCREEN_HEIGHT - e->h / 2);
		}
	}
}

void GameStage::drawEntities()
{
	Entity *e;
	
	for (e = entityHead.next ; e != NULL ; e = e->next)
	{
		blitRotated(e->texture, e->x, e->y, e->angle);
	}
}

void GameStage::doBullets()
{
	Entity *b, *prev;
	
	prev = &bulletHead;
	
	for (b = bulletHead.next ; b != NULL ; b = b->next)
	{
		b->x += b->dx;
		b->y += b->dy;
		
		if (--b->health <= 0)
		{
			if (b == bulletTail)
			{
				bulletTail = prev;
			}
			
			prev->next = b->next;
			delete b;
			b = prev;
		}
		
		prev = b;
	}
}

void GameStage::drawBullets()
{
	Entity *b;
	
	for (b = bulletHead.next ; b != NULL ; b = b->next)
	{
		blitRotated(b->texture, b->x, b->y, b->angle);
	}
}

void GameStage::fireUzi()
{
	Entity *b = new Entity;
	
	bulletTail->next = b;
	bulletTail = b;
	
	b->x = player->x;
	b->y = player->y;
	b->texture = Bullet;
	b->health = FPS * 2;
	b->angle = player->angle;
	
	calcSlope(mouse.x, mouse.y, b->x, b->y, &b->dx, &b->dy);
	
	b->dx *= 16;
	b->dy *= 16;
	
	player->reload = 4;
}

void GameStage::fireShotgun()
{
	Entity *b;
	int i, destX, destY;
	float dx, dy;
	
	calcSlope(mouse.x, mouse.y, player->x, player->y, &dx, &dy);
	
	dx = player->x + (dx * 128);
	dy = player->y + (dy * 128);
	
	for (i = 0 ; i < 8 ; i++)
	{
		b = new Entity;
		
		bulletTail->next = b;
		bulletTail = b;
		
		b->x = player->x + rand() % 16 - rand() % 16;
		b->y = player->y + rand() % 16 - rand() % 16;
		b->texture = Bullet;
		b->health = FPS * 2;
		b->angle = player->angle;
		
		destX = dx + (rand() % 24 - rand() % 24);
		destY = dy + (rand() % 24 - rand() % 24);
		
		calcSlope(destX, destY, b->x, b->y, &b->dx, &b->dy);
		
		b->dx *= 16;
		b->dy *= 16;
	}
	
	player->reload = FPS * 0.75;
}

void GameStage::firePistol()
{
	Entity *b = new Entity;
	
	bulletTail->next = b;
	bulletTail = b;
	
	b->x = player->x;
	b->y = player->y;
	b->texture = Bullet;
	b->health = FPS * 2;
	b->angle = player->angle;
	
	calcSlope(mouse.x, mouse.y, b->x, b->y, &b->dx, &b->dy);
	
	b->dx *= 16;
	b->dy *= 16;
	
	player->reload = 16;
}

void GameStage::drawText(int x, int y, int r, int g, int b, int align, const char* text, int w, int number)
{
	SDL_Rect rect;
	std::ostringstream s;
	s << text << std::setw(w) << std::setfill('0') << number;
	std::string str = s.str();

	int len = str.size();
	
	switch (align)
	{
		case TEXT_RIGHT:
			x -= (len * GLYPH_WIDTH);
			break;
			
		case TEXT_CENTER:
			x -= (len * GLYPH_WIDTH) / 2;
			break;
	}
	
	rect.w = GLYPH_WIDTH;
	rect.h = GLYPH_HEIGHT;
	rect.y = 0;
	
	SDL_SetTextureColorMod(fontTexture, r, g, b);
	
	for (int i = 0 ; i < len ; i++)
	{
		char c = str[i];
		
		if (c >= ' ' && c <= 'Z')
		{
			rect.x = (c - ' ') * GLYPH_WIDTH;
			
			blitRect(fontTexture, &rect, x, y);
			
			x += GLYPH_WIDTH;
		}
	}
}

void GameStage::drawWeaponInfo(const char* name, int type, int x, int y)
{
	int r, g, b;
	
	if (player->weaponType == type)
	{
		r = b = 0;
		g = 255;
	}
	else
	{
		r = g = b = 255;
	}
	
	drawText(x, y, r, g, b, TEXT_LEFT, name, 3, ammo[type]);
}

void GameStage::drawHud()
{
	drawText(10, 10, 255, 255, 255, TEXT_LEFT, "HEALTH:", 2, player->health);
	
	drawText(250, 10, 255, 255, 255, TEXT_LEFT, "SCORE:", 5, 0);
	
	drawWeaponInfo("PISTOL:", WPN_PISTOL, 550, 10);
	
	drawWeaponInfo("UZI:", WPN_UZI, 800, 10);
	
	drawWeaponInfo("SHOTGUN:", WPN_SHOTGUN, 1050, 10);
}
