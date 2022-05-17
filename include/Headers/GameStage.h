#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include "common.h"
#include <sstream>
#include <iomanip>
#include "Effect.h"

class GameStage : public Game
{
public: 
    SDL_Texture *targetterTexture;
    SDL_Texture *bullet;
    SDL_Texture *fontTexture;
    SDL_Texture *healthTexture;
    SDL_Texture *uziTexture;
    SDL_Texture *shotgunTexture;
    SDL_Texture *gridTexture[4];
    SDL_Texture *enemyTexture[3];
    SDL_Texture *sqr16;
    SDL_Texture *sqr8;

    int score;
    Enemy enemyHead, *enemyTail;
    Bullet bulletHead, *bulletTail;
    Item itemHead, *itemTail;
    Effect effectHead, *effectTail;
    SDL_Point camera;

    Player *player;
    
    int enemySpawnTimer;

    void initStage();
    void initPlayer();

    void logic();
    void draw();
    
    void doPlayer();
    void doEnemies();
    void doBullets();
    void doItems();
    void doCamera();
    void doEnemyEffect(Enemy* enemy);
    void doEffect();

    void drawEnemies();
    void drawBullets();
    void drawHud();
    void drawText(int x, int y, int r, int g, int b, int align, const char* text, int w, int number);
    void drawWeaponInfo(const char *name, int type, int x, int y);
    void drawItems();
    void drawGrid();
    void drawEffect();

    void fireBullet();
    void fireUzi();
    void fireShotgun();
    void firePistol();
    void enemyFire(Enemy* e);
    void fireType1(Enemy *e);
    void fireType2(Enemy *e);
    void fireType3(Enemy *e);

    void addEnemy(int x, int y);

    void bulletHitEnemy(Bullet *b);
    void spawnEnemy();
    void addRandomItem(int x, int y);
    void addHealth(int x, int y);
    void addUziBullet(int x, int y);
    void addShotgunBullet(int x, int y);
    void addEnemyDeathEffect(Enemy* enemy);
    void addPlayerDeathEffect();
    void addBulletHitEffect(Enemy* enemy);
    void bulletHitEntity(Bullet* b);

    Bullet* createBullet();
};

#endif