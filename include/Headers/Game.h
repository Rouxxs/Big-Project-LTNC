#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>

#include "const.h"

class Texture 
{
public:
	std::string name;
	SDL_Texture *texture;
	Texture *next;
    Texture(std::string name_ = "", SDL_Texture *tex = NULL, Texture *n = NULL) {name = name_; texture = tex; next = n;}
};

class Mouse
{
public:
    int x, y;
    int button[MAX_MOUSE_BUTTONS] = {0};
	int wheel;
    Mouse(){x = 0; y = 0;}
};

class Game
{
public:
    SDL_Renderer *renderer;
	SDL_Window *window;
    int keyboard[MAX_KEYBOARD_KEYS] = {0};
	Mouse mouse;
	Texture textureHead, *textureTail;

    Game()
    {}
    void initSDL();
    void cleanup();
    void doInput();
    void prepareScene();
    void presentScene();
    SDL_Texture *getTexture(std::string name);
    void addTextureToCache(std::string name, SDL_Texture *Tex);
    SDL_Texture *loadTexture(const char* filename);
    void blit(SDL_Texture *texture, int x, int y, int center);
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
    void blitRotated(SDL_Texture *texture, int x, int y, float angle);
    void doMouseButtonUp(SDL_MouseButtonEvent *event);
    void doMouseButtonDown(SDL_MouseButtonEvent *event);
    void doKeyUp(SDL_KeyboardEvent *event);
    void doKeyDown(SDL_KeyboardEvent *event);
};



#endif