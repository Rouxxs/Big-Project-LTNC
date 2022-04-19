#include "GameStage.h"

void GameStage::initStage()
{
	targetterTexture = loadTexture("gfx/targetter.png");
}

void GameStage::logic()
{
	
}

void GameStage::draw()
{
	blit(targetterTexture, mouse.x, mouse.y, 1);
}

