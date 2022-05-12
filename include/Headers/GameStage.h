#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include "common.h"
#include <sstream>
#include <iomanip>

class GameStage : public Game
{
public: 
    SDL_Texture *targetterTexture;
    SDL_Texture *bullet;
    SDL_Texture *fontTexture;
    SDL_Texture *healthTexture;
    SDL_Texture *uziTexture;
    SDL_Texture *shotgunTexture;

    Enemy enemyHead, *enemyTail;
    Bullet bulletHead, *bulletTail;
    Item itemHead, *itemTail;
    Player *player;
    int score;
    int enemySpawnTimer;

    void initStage();
    void logic();
    void draw();
    void initPlayer();
    void doPlayer();
    void doEnemies();
    void doBullets();
    void doItems();
    void drawEnemies();
    void drawBullets();
    void fireBullet();
    void fireUzi();
    void fireShotgun();
    void firePistol();
    void drawText(int x, int y, int r, int g, int b, int align, const char* text, int w, int number);
    void drawWeaponInfo(const char *name, int type, int x, int y);
    void drawHud();
    void addEnemy(int x, int y);
    void bulletHitEnemy(Bullet *b);
    void spawnEnemy();
    void addRandomItem(int x, int y);
    void addHealth(int x, int y);
    void addUziBullet(int x, int y);
    void addShotgunBullet(int x, int y);
    void drawItems();
};

#endif