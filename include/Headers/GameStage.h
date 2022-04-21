#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include "common.h"

class GameStage : public Game
{
public: 
    SDL_Texture *targetterTexture;
    Entity entityHead, *entityTail;
    Entity *player = new Entity;

    void initStage();
    void logic();
    void draw();
    void initPlayer();
    void doPlayer();
    void doEntities();
    void drawEntities();
};

#endif