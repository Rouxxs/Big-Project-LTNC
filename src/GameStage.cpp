#include "GameStage.h"



void GameStage::initStage()
{
	targetterTexture = loadTexture("gfx/targetter.png");

	bullet = loadTexture("gfx/Bullet.png");

	fontTexture = loadTexture("gfx/font.png");

	healthTexture = loadTexture("gfx/health.png");
	uziTexture = loadTexture("gfx/uzi.png");
	shotgunTexture = loadTexture("gfx/shotgun.png");

	enemyTail = &enemyHead;

	bulletTail = &bulletHead;

	itemTail = &itemHead;

	score = 0;

	enemySpawnTimer = 0;

	initPlayer();
}

void GameStage::logic()
{
	doPlayer();

	doEnemies();

	doBullets();

	spawnEnemy();

	doItems();

}

void GameStage::draw()
{
	blitRotated(player->texture, player->x, player->y, player->angle); // draw player
	drawEnemies();
	drawBullets();
	drawItems();
	drawHud();
	blit(targetterTexture, mouse.x, mouse.y, 1);
}

void GameStage::initPlayer()
{
	player = new Player;
	
	player->texture = loadTexture("gfx/Player.png");
	player->health = 5;
	player->radius = 24;
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	player->weaponType = 0;

	
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
	player->move(keyboard);

	player->angle = getAngle(player->x, player->y, mouse.x, mouse.y);

	if (player->reload == 0 && player->ammo[player->weaponType] > 0 && mouse.button[SDL_BUTTON_LEFT])
	{
		fireBullet();
		
		player->ammo[player->weaponType]--;
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
		if (player->weaponType == WPN_PISTOL && player->ammo[WPN_PISTOL] == 0)
		{
			player->ammo[WPN_PISTOL] = 12;
		}
		
		mouse.button[SDL_BUTTON_RIGHT] = 0;
	}

	
}

void GameStage::doEnemies()
{
	Enemy *e, *prev;

	prev = &enemyHead;

	for (e = enemyHead.next ; e != NULL ; e = e->next)
	{
		e->move(player);
		e->x += e->dx;
    	e->y += e->dy;
		
		e->reload = MAX(e->reload - 1, 0);
		
		if(e->health <= 0)
		{
			if (rand() % 2 == 0)
			{
				addRandomItem(e->x, e->y);
			}

			score += 10;
			if (e == enemyTail)
			{
				enemyTail = prev;
			}
			
			prev->next = e->next;
			delete e;
			e = prev;
		}
		prev = e;
	}
	
}

void GameStage::drawEnemies()
{
	Enemy *e;
	
	for (e = &enemyHead; e != NULL ; e = e->next)
	{
		blitRotated(e->texture, e->x, e->y, e->angle);
	}
}

void GameStage::doBullets()
{
	Bullet *b, *prev;
	
	prev = &bulletHead;
	
	for (b = bulletHead.next ; b != NULL ; b = b->next)
	{
		b->x += b->dx;
		b->y += b->dy;
		
		bulletHitEnemy(b);

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

void GameStage::doItems()
{
	Item *i, *prev = &itemHead;

	for (i = itemHead.next; i != NULL; i = i->next)
	{
		player->touchItem(i);
		
		if (--i->health <= 0)
		{
			if (i == itemTail)
			{
				itemTail = prev;
			}
			
			prev->next = i->next;
			delete i;
			i = prev;
		}
		prev = i;
	}
}

void GameStage::drawBullets()
{
	Bullet *b;
	
	for (b = bulletHead.next ; b != NULL ; b = b->next)
	{
		blitRotated(b->texture, b->x, b->y, b->angle);
	}
}

void GameStage::drawItems()
{
	
	for (Item *i = &itemHead; i != NULL; i = i->next)
	{
		blit(i->texture, i->x, i->y, 0);
	}

}

void GameStage::fireUzi()
{
	Bullet *b = new Bullet;
	
	bulletTail->next = b;
	bulletTail = b;
	
	b->x = player->x;
	b->y = player->y;
	b->texture = bullet;
	b->health = FPS * 2;
	b->angle = player->angle;
	b->radius = 16;
	
	calcSlope(mouse.x, mouse.y, b->x, b->y, &b->dx, &b->dy);
	
	b->dx *= 16;
	b->dy *= 16;
	
	player->reload = 4;
}

void GameStage::fireShotgun()
{
	Bullet *b;
	int i, destX, destY;
	float dx, dy;
	
	calcSlope(mouse.x, mouse.y, player->x, player->y, &dx, &dy);
	
	dx = player->x + (dx * 128);
	dy = player->y + (dy * 128);
	
	for (i = 0 ; i < 8 ; i++)
	{
		b = new Bullet;
		
		bulletTail->next = b;
		bulletTail = b;
		
		b->x = player->x + rand() % 16 - rand() % 16;
		b->y = player->y + rand() % 16 - rand() % 16;
		b->texture = bullet;
		b->health = FPS * 2;
		b->angle = player->angle;
		b->radius = 16;
		
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
	Bullet *b = new Bullet;
	
	bulletTail->next = b;
	bulletTail = b;
	
	b->x = player->x;
	b->y = player->y;
	b->texture = bullet;
	b->health = FPS * 2;
	b->angle = player->angle;
	b->radius = 16;
	
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
	
	drawText(x, y, r, g, b, TEXT_LEFT, name, 3, player->ammo[type]);
}

void GameStage::drawHud()
{
	drawText(10, 10, 255, 255, 255, TEXT_LEFT, "HEALTH:", 2, player->health);
	
	drawText(250, 10, 255, 255, 255, TEXT_LEFT, "SCORE:", 5, score);
	
	drawWeaponInfo("PISTOL:", WPN_PISTOL, 550, 10);
	
	drawWeaponInfo("UZI:", WPN_UZI, 800, 10);
	
	drawWeaponInfo("SHOTGUN:", WPN_SHOTGUN, 1050, 10);
}

void GameStage::addEnemy(int x, int y)
{
	Enemy *e = new Enemy;

	enemyTail->next = e;
	enemyTail = e;

	e->texture = loadTexture("gfx/enemy01.png");
	e->health = 5;
	e->x = x;
	e->y = y;
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->radius = 32;
}

 void GameStage::bulletHitEnemy(Bullet *b)
{
	Enemy *e;
	int distance;

	for (e = enemyHead.next ; e != NULL ; e = e->next)
	{
		distance = getDistance(e->x, e->y, b->x, b->y);

		if (distance < e->radius + b->radius)
		{
			b->health = 0;
			e->health--;
			return;
		}
	}
}

void GameStage::spawnEnemy()
{
	int x, y;

	if (--enemySpawnTimer <= 0)
	{
		switch (rand() % 4)
		{
			case 0:
				x = -100;
				y = rand() % SCREEN_HEIGHT;
				break;

			case 1:
				x = SCREEN_WIDTH + 100;
				y = rand() % SCREEN_HEIGHT;
				break;

			case 2:
				x = rand() % SCREEN_WIDTH;
				y = -100;
				break;

			case 3:
				x = rand() % SCREEN_WIDTH;
				y = SCREEN_HEIGHT + 100;
				break;
		}

		addEnemy(x, y);

		enemySpawnTimer = FPS + (rand() % FPS);
	}
}

void GameStage::addRandomItem(int x, int y)
{
	int r;

	r = rand() % 5;

	if (r == 0)
	{
		addHealth(x, y);
	}
	else if (r < 3)
	{
		addUziBullet(x, y);
	}
	else
	{
		addShotgunBullet(x, y);
	}
}

void GameStage::addHealth(int x, int y)
{
	Item *i = new Item;

	itemTail->next = i;
	itemTail = i;

	i->x = x;
	i->y = y;
	i->type = HEATH_ITEM;
	i->texture = healthTexture;
	SDL_QueryTexture(i->texture, NULL, NULL, &i->w, &i->h);
	i->radius = 16;
}

void GameStage::addUziBullet(int x, int y)
{
	Item *i = new Item;

	itemTail->next = i;
	itemTail = i;

	i->x = x;
	i->y = y;
	i->type = UZI_ITEM;
	i->texture = uziTexture;
	SDL_QueryTexture(i->texture, NULL, NULL, &i->w, &i->h);
	i->radius = 16;
}

void GameStage::addShotgunBullet(int x, int y)
{
	Item *i = new Item;

	itemTail->next = i;
	itemTail = i;

	i->x = x;
	i->y = y;
	i->type = SHOTGUN_ITEM;
	i->texture = shotgunTexture;
	SDL_QueryTexture(i->texture, NULL, NULL, &i->w, &i->h);
	i->radius = 16;
}
