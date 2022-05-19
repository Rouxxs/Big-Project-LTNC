#include "GameStage.h"

void GameStage::initStage()
{
	targetterTexture = loadTexture("gfx/targetter.png");

	bullet = loadTexture("gfx/Bullet.png");
	enemyBullet = loadTexture("gfx/enemyBullet.png");

	fontTexture = loadTexture("gfx/font.png");

	healthTexture = loadTexture("gfx/health.png");

	uziTexture = loadTexture("gfx/uzi.png");

	shotgunTexture = loadTexture("gfx/shotgun.png");

	gridTexture[0] = loadTexture("gfx/grid01.png");
	gridTexture[1] = loadTexture("gfx/grid02.png");
	gridTexture[2] = loadTexture("gfx/grid03.png");
	gridTexture[3] = loadTexture("gfx/grid04.png");

	enemyTexture[0] = loadTexture("gfx/enemy01.png");
	enemyTexture[1] = loadTexture("gfx/enemy02.png");
	enemyTexture[2] = loadTexture("gfx/enemy03.png");

	sqr16 = loadTexture("gfx/whiteSquare16.png");
	sqr8 = loadTexture("gfx/whiteSquare8.png");

	enemyTail = &enemyHead;

	bulletTail = &bulletHead;

	itemTail = &itemHead;

	effectTail = &effectHead;

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
	
	doEffect();

	doItems();

	doCamera();	
}

void GameStage::draw()
{
	drawGrid();

	drawEnemies();

	drawBullets();

	drawItems();

	drawEffect();

	drawHud();

	blitRotated(player->texture, player->x - camera.x, player->y - camera.y, player->angle); // draw player

	blit(targetterTexture, mouse.x, mouse.y, 1);
}

void GameStage::drawGrid()
{
	int x1, x2, y1, y2, x, y, mx, my, n;

	x1 = (camera.x % GRID_SIZE) * (-1);
	x2 = x1 + GRID_RENDER_WIDTH * GRID_SIZE + ((x1 == 0) ? 0 : GRID_SIZE);

	y1 = (camera.y % GRID_SIZE) * (-1);
	y2 = y1 + GRID_RENDER_HEIGHT * GRID_SIZE + ((y1 == 0) ? 0 : GRID_SIZE);

	mx = camera.x / GRID_SIZE;
	my = camera.y / GRID_SIZE;

	n = 0;

	for (x = x1; x < x2; x += GRID_SIZE)
	{
		for (y = y1; y < y2; y += GRID_SIZE)
		{
			if (mx >= 0 && my >= 0 && mx <= (ARENA_WIDTH / GRID_SIZE) - 1 && my <= (ARENA_HEIGHT / GRID_SIZE) - 1)
			{
				n = ((mx * my) / 40) % 4;

				blit(gridTexture[n], x, y, 0);
			}

			my++;
		}

		my = camera.y / GRID_SIZE;
		mx++;
	}
}

void GameStage::initPlayer()
{
	player = new Player;
	
	player->texture = loadTexture("gfx/Player.png");
	player->health = 20;
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

	player->angle = getAngle(player->x - camera.x, player->y - camera.y, mouse.x, mouse.y);	

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
		
		switch(rand() % 12)
		{
						
			case 1:
				fireType1(e);
				break;

			case 2:
				fireType2(e);
				break;

			default:
				fireType3(e);
				break;			
		}
				
		if(getDistance(player->x, player->y, e->x, e->y) < player->radius + e->radius)
		{
			player->health--;
		}

		if(e->health <= 0)
		{
			addEnemyDeathEffect(e);

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
		SDL_SetTextureColorMod(e->texture, e->color.r, e->color.g, e->color.b);
		blitRotated(e->texture, e->x - camera.x, e->y - camera.y, e->angle);
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
		
		bulletHitEntity(b);

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
		blitRotated(b->texture, b->x - camera.x, b->y - camera.y, b->angle);
	}
}

void GameStage::drawItems()
{
	Item *i;

	for (i = &itemHead; i != NULL; i = i->next)
	{
		blit(i->texture, i->x - camera.x, i->y - camera.y, 0);
	}

}

Bullet* GameStage::createBullet()
{
	Bullet* b = new Bullet;

	bulletTail->next = b;
	bulletTail = b;

	b->x = player->x;
	b->y = player->y;
	b->texture = bullet;
	b->health = FPS * 2;
	b->angle = player->angle;
	b->radius = 16;
	b->side = SIDE_PLAYER;

	SDL_QueryTexture(b->texture, NULL, NULL, &b->w, &b->h);
	b->color.r = 128;
	b->color.g = b->color.b = b->color.a = 255;
	
	return b;
}

void GameStage::fireUzi()
{
	Bullet *b = createBullet();
	
	calcSlope(mouse.x, mouse.y, b->x - camera.x, b->y - camera.y, &b->dx, &b->dy);
	
	b->dx *= 16;
	b->dy *= 16;
	
	player->reload = 4;
}

void GameStage::fireShotgun()
{
	Bullet *b;
	int i, destX, destY;
	float dx, dy;
	
	calcSlope(mouse.x, mouse.y, player->x - camera.x, player->y - camera.y, &dx, &dy);
	
	dx = player->x + (dx * 128);
	dy = player->y + (dy * 128);
	
	for (i = 0 ; i < 8 ; i++)
	{
		b = createBullet();
		
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
	Bullet *b = createBullet();
	
	calcSlope(mouse.x, mouse.y, b->x - camera.x, b->y - camera.y, &b->dx, &b->dy);
	
	b->dx *= 16;
	b->dy *= 16;
	
	player->reload = 16;
}

void GameStage::enemyFire(Enemy* e)
{
	Bullet* b = new Bullet;

	bulletTail->next = b;
	bulletTail = b;

	b->x = e->x;
	b->y = e->y;
	b->texture = enemyBullet;
	b->health = FPS * 2;
	b->angle = getAngle(e->x, e->y, player->x, player->y);
	b->radius = 10;
	b->side = SIDE_ENEMY;

	SDL_QueryTexture(b->texture, NULL, NULL, &b->w, &b->h);
	b->color.r = 255;
	b->color.g = b->color.b = 0;
	b->color.a = 255;
	
	calcSlope(player->x, player->y, b->x, b->y, &b->dx, &b->dy);
	
	b->dx *= 12;
	b->dy *= 12;
}

void GameStage::fireType1(Enemy *e)
{
	if (player != NULL)
	{
		e->angle = getAngle(e->x, e->y, player->x, player->y);

		calcSlope(player->x, player->y, e->x, e->y, &e->dx, &e->dy);

		e->reload = MAX(e->reload - 1, 0);

		if (e->reload <= 0 && getDistance(e->x, e->y, player->x, player->y) < SCREEN_HEIGHT / 2)
		{
			enemyFire(e);

			e->reload = FPS * 3;
		}
	}
}

void GameStage::fireType2(Enemy *e)
{
	float dx, dy;
	
	if (++e->angle >= 360)
	{
		e->angle = 0;
	}
	
	if (player != NULL)
	{
		calcSlope(player->x, player->y, e->x, e->y, &dx, &dy);
		
		dx /= 10;
		dy /= 10;
		
		e->dx += dx;
		e->dy += dy;
		
		e->dx = MAX(MIN(e->dx, 3), -3);
		e->dy = MAX(MIN(e->dy, 3), -3);
		
		e->reload = MAX(e->reload - 1, 0);
		
		if (e->reload <= 0 && getDistance(e->x, e->y, player->x, player->y) < SCREEN_HEIGHT / 2)
		{
			enemyFire(e);
			
			e->reload = FPS / 2;
		}
	}
}

void GameStage::fireType3(Enemy *e)
{
	float dx, dy;
	
	e->angle -= 5;
	
	if (e->angle < 0)
	{
		e->angle = 359;
	}
	
	calcSlope(player->x, player->y, e->x, e->y, &dx, &dy);
	
	dx /= 10;
	dy /= 10;
	
	e->dx += dx;
	e->dy += dy;
	
	e->dx = MAX(MIN(e->dx, 5), -5);
	e->dy = MAX(MIN(e->dy, 5), -5);
	
	e->reload = MAX(e->reload - 1, 0);
	
	if (e->reload <= 0 && getDistance(e->x, e->y, player->x, player->y) < SCREEN_HEIGHT)
	{
		enemyFire(e);
		
		e->reload = FPS * 3;
	}
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
	e->color.r = e->color.g = e->color.b = e->color.a = 255;

	switch (rand() % 12)
	{
		case 0:
			e->texture = enemyTexture[1];
			e->x = x;
			e->y = y;
			e->radius = 35;
			e->health = 25;
			break;
			
		case 1:
			e->texture = enemyTexture[2];
			e->x = x;
			e->y = y;
			e->radius = 26;
			e->health = 2;
			break;
			
		default:
			e->texture = enemyTexture[0];
			e->x = x;
			e->y = y;
			e->radius = 32;
			e->health = 5;
			break;
	}
	
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
}

 void GameStage::bulletHitEntity(Bullet *b)
{
	Enemy *e;

	if(b->side == SIDE_PLAYER)
	{
		for (e = enemyHead.next ; e != NULL ; e = e->next)
		{

			if (getDistance(e->x, e->y, b->x, b->y) < e->radius + b->radius)
			{
				addBulletHitEffect(e);
				b->health = 0;
				e->health--;
				return;
			}
		}
	}
	else if(b->side == SIDE_ENEMY)
	{
		if(getDistance(player->x, player->y, b->x, b->y) < player->radius + b->radius)
		{
			b->health = 0;
			player->health--;
			return;
		}
	}
}

void GameStage::spawnEnemy()
{
	int x, y;
	
	if (--enemySpawnTimer <= 0)
	{
		x = player->x + (rand() % SCREEN_WIDTH) - (rand() % SCREEN_WIDTH);
		y = player->y + (rand() % SCREEN_HEIGHT) - (rand() % SCREEN_HEIGHT);
		
		if (getDistance(x, y, player->x, player->y) > SCREEN_WIDTH / 2)
		{
			addEnemy(x, y);
			
			enemySpawnTimer = (FPS * 2) + rand() % FPS;
		}
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

void GameStage::doCamera()
{
	camera.x = player->x - (SCREEN_WIDTH / 2);
	camera.y = player->y - (SCREEN_HEIGHT / 2);
	
	if(player->x < SCREEN_WIDTH/2 + GRID_SIZE/2 && player->y < SCREEN_HEIGHT/2 + GRID_SIZE/2)
	{
		camera.x = GRID_SIZE/2;
		camera.y = GRID_SIZE/2;
	}
	else if (player->x < SCREEN_WIDTH/2 + GRID_SIZE/2) 
	{
		camera.x = GRID_SIZE/2;
	}
	else if (player->y < SCREEN_HEIGHT/2 + GRID_SIZE/2)
	{
		camera.y = GRID_SIZE/2;
	}

	if (player->x > ARENA_WIDTH - SCREEN_WIDTH/2 - GRID_SIZE/2 && player->y > ARENA_HEIGHT - SCREEN_HEIGHT/2 - GRID_SIZE/2)
	{
		camera.x = ARENA_WIDTH - SCREEN_WIDTH - GRID_SIZE/2;
		camera.y = ARENA_HEIGHT - SCREEN_HEIGHT - GRID_SIZE/2;
	}
	else if (player->x > ARENA_WIDTH - SCREEN_WIDTH/2 - GRID_SIZE/2)
	{
		camera.x = ARENA_WIDTH - SCREEN_WIDTH - GRID_SIZE/2;
	}
	else if(player->y > ARENA_HEIGHT - SCREEN_HEIGHT/2 - GRID_SIZE/2)
	{
		camera.y = ARENA_HEIGHT - SCREEN_HEIGHT - GRID_SIZE/2;
	}

}

void GameStage::doEffect()
{
	Effect *e, *prev;
	
	prev = &effectHead;
	
	for (e = effectHead.next ; e != NULL ; e = e->next)
	{
		e->x += e->dx;
		e->y += e->dy;
		
		e->color.a = MAX(e->color.a - 1, 0);
		
		if (--e->life <= 0)
		{
			if (e == effectTail)
			{
				effectTail = prev;
			}
			
			prev->next = e->next;
			delete e;
			e = prev;
		}
		
		prev = e;
		
	}
}

void GameStage::drawEffect()
{
	Effect *e;
	
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
	
	for (e = effectHead.next ; e != NULL ; e = e->next)
	{
		SDL_SetTextureBlendMode(e->texture, SDL_BLENDMODE_ADD);
		
		SDL_SetTextureColorMod(e->texture, e->color.r, e->color.g, e->color.b);
		SDL_SetTextureAlphaMod(e->texture, e->color.a);
				
		blit(e->texture, e->x - camera.x, e->y - camera.y, 1);
	}
	
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

void GameStage::addEnemyDeathEffect(Enemy* enemy)
{
	int test = 0;
	for (int i = 0 ; i < 128 ; i++)
	{
		Effect* e = new Effect;
		effectTail->next = e;
		effectTail = e;
		
		e->x = enemy->x;
		e->y = enemy->y;
		e->dx = 400 - rand() % 800;
		e->dy = 400 - rand() % 800;
		
		e->dx /= 100;
		e->dy /= 100;
		
		e->texture = sqr16;
		
		e->color.r = 255;
		e->color.g = 0;
		e->color.b = 0;
		e->color.a = rand() % 255;
		
		e->life = rand() % FPS;
	}
}

void GameStage::addPlayerDeathEffect()
{
	Effect *e;
	int i, test = 0;
	
	for (i = 0 ; i < 128 ; i++)
	{
		e = new Effect;
		effectTail->next = e;
		effectTail = e;
		
		e->x = player->x;
		e->y = player->y;
		e->dx = 400 - rand() % 800;
		e->dy = 400 - rand() % 800;
		
		e->dx /= 100;
		e->dy /= 100;
		
		e->texture = sqr16;
		
		e->color.r = rand() % 128;
		e->color.g = 128 + rand() % 128;
		e->color.b = 255;
		e->color.a = rand() % 255;
		
		e->life = rand() % FPS;

	}
}

void GameStage::addBulletHitEffect(Enemy* enemy)
{
	Effect *e;
	
	for (int i = 0 ; i < 16 ; i++)
	{
		e = new Effect;
		effectTail->next = e;
		effectTail = e;
		
		e->x = enemy->x;
		e->y = enemy->y;
		e->dx = 400 - rand() % 800;
		e->dy = 400 - rand() % 800;
		
		e->dx /= 100;
		e->dy /= 100;
		
		e->texture = sqr16;
		
		e->color = enemy->color;
		
		e->color.a = rand() % 255;
		
		e->life = rand() % FPS;
	}
}

void GameStage::doEnemyEffect(Enemy* enemy)
{
	Effect *e;

	for (int i = 0 ; i < 128 ; i++)
	{
		e = new Effect;
		effectTail->next = e;
		effectTail = e;

		e->x = enemy->x;
		e->y = enemy->y;
		e->dx = 400 - rand() % 800;
		e->dy = 400 - rand() % 800;

		e->dx /= 100;
		e->dy /= 100;

		e->texture = sqr16;

		e->color.r = 255;
		e->color.g = 128 + rand() % 128;
		e->color.b = 0;
		e->color.a = rand() % 255;

		e->life = rand() % FPS;
	}
}
