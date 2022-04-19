#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include "common.h"

class GameStage : public Game
{
public: 
    SDL_Texture *targetterTexture;

    GameStage() {}
    void initStage();
    void logic();
    void draw();
};

#endif