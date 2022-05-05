#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity
{
public:
    float x;
	float y;
	int w;
	int h;
	float dx;
	float dy;
	int health;
	int angle;
	int reload;
	int weaponType;
	SDL_Texture *texture;
	Entity *next;

    Entity(float x_ = 0, float y_ = 0, int w_ = 0, int h_ = 0, float dx_ = 0, float dy_ = 0, int health_ = 0, int angle_ = 0, int wbt = 0, int reload_ = 0, SDL_Texture* tex = NULL, Entity *n = NULL)
    {x = x_; y = y_; w_ = w; h = h_; dx = dx_; dy = dy_; health = health_; angle = angle_; weaponType = wbt; reload = reload_; texture = tex; next = n;}
};


#endif