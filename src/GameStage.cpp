#include "GameStage.h"



void GameStage::initStage()
{
	targetterTexture = loadTexture("gfx/targetter.png");

	entityTail = &entityHead;

	initPlayer();

}

void GameStage::logic()
{
	doPlayer();

	doEntities();
}

void GameStage::draw()
{
	drawEntities();
	blit(targetterTexture, mouse.x, mouse.y, 1);
}

void GameStage::initPlayer()
{
	
	entityTail->next = player;
	entityTail = player;
	
	player->texture = loadTexture("gfx/donk.png");
	player->health = 5;
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
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
}

void GameStage::doEntities()
{
	Entity *e;
	
	for (e = entityHead.next ; e != NULL ; e = e->next)
	{
		e->x += e->dx;
		e->y += e->dy;
		
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