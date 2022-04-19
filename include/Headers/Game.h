#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>

#include "const.h"

class Texture 
{
public:
	std::string name;
	SDL_Texture *texture;
	Texture *next;
    Texture(std::string name_ = "", SDL_Texture *tex = NULL, Texture *n = NULL) {name = name_; texture = tex; next = n;}
};

struct Mouse
{
    int x, y;
};

class Game
{
public:
    SDL_Renderer *renderer;
	SDL_Window *window;
    int keyboard[MAX_KEYBOARD_KEYS];
	Mouse mouse;
	Texture textureHead, *textureTail;

    void initSDL();
    void initGame();
    void cleanup();
    void doInput();
    void prepareScene();
    void presentScene();
    SDL_Texture *getTexture(std::string name);
    void addTextureToCache(std::string name, SDL_Texture *Tex);
    SDL_Texture *loadTexture(const char* filename);
    void blit(SDL_Texture *texture, int x, int y, int center);
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
};



#endif