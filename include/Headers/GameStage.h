#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include "common.h"
#include <sstream>
#include <iomanip>

class GameStage : public Game
{
public: 
    SDL_Texture *targetterTexture;
    SDL_Texture *Bullet;
    SDL_Texture *fontTexture;

    Entity entityHead, *entityTail;
    Entity bulletHead, *bulletTail;
    Entity *player = new Entity;
    int ammo[WPN_MAX];

    void initStage();
    void logic();
    void draw();
    void initPlayer();
    void doPlayer();
    void doEntities();
    void doBullets();
    void drawEntities();
    void drawBullets();
    void fireBullet();
    void fireUzi();
    void fireShotgun();
    void firePistol();
    void drawText(int x, int y, int r, int g, int b, int align, const char* text, int w, int number);
    void drawWeaponInfo(const char *name, int type, int x, int y);
    void drawHud();

};

#endif