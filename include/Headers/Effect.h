#ifndef EFFECT_H
#define EFFECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Effect{
public:
    float x;
	float y;
	float dx;
	float dy;
	int life;
	SDL_Color color;
	SDL_Texture *texture;
	Effect *next;

	Effect(float x_ = 0, float y_ = 0, float dx_ = 0, float dy_ = 0, int life_ = 0, SDL_Color color_ = {255, 255, 255}, SDL_Texture *t = NULL, Effect* n = NULL)
	{x = x_; y = y_; dx = dx_; dy = dy_; life = life_; color = color_; texture = t; next = n;}

};

#endif