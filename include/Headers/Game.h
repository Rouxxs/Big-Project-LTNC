#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>


#include "const.h"

class Mouse
{
public:
    int x, y;
    int button[MAX_MOUSE_BUTTONS];
	int wheel;
    Mouse()
    {
        x = 0; y = 0; wheel = 0;
        for(int i = 0; i < MAX_MOUSE_BUTTONS; i++)
		    button[i] = 0;
    }
};

class Game
{
public:
    SDL_Renderer *renderer;
	SDL_Window *window;
    SDL_Texture *fontTexture;
    int keyboard[MAX_KEYBOARD_KEYS];
	Mouse mouse;
    bool check;
    bool running;
    std::string inputText;

    Game();
    void cleanup();
    void doInput();
    void prepareScene();
    void presentScene();
    SDL_Texture *loadTexture(const char* filename);
    void blit(SDL_Texture *texture, int x, int y, int center);
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
    void blitRotated(SDL_Texture *texture, int x, int y, float angle);
    void doMouseButtonUp(SDL_MouseButtonEvent *event);
    void doMouseButtonDown(SDL_MouseButtonEvent *event);
    void doKeyUp(SDL_KeyboardEvent *event);
    void doKeyDown(SDL_KeyboardEvent *event);
    void drawText1(int x, int y, int r, int g, int b, int align, const char* text, int w, int number);
    void drawText2(int x, int y, int r, int g, int b, int align, std::string text);
    void drawText3 (int x, int y, int r, int g, int b, int align, int i, std::string name, int score);
};



#endif