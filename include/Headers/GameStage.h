#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include <fstream>
#include "common.h"
#include "Effect.h"
#include "Highscore.h"

class GameStage : public Game
{
public: 
    SDL_Texture *targetterTexture;
    SDL_Texture *background;
    SDL_Texture *playerTex1, *playerTex2;
    SDL_Texture *bullet;
    SDL_Texture *enemyBullet;
    SDL_Texture *healthTexture;
    SDL_Texture *uziTexture;
    SDL_Texture *shotgunTexture;
    SDL_Texture *gridTexture;
    SDL_Texture *enemyTexture[3];
    SDL_Texture *bonusPointTex;
    SDL_Texture *sqr16;
    SDL_Texture *sqr8;
    SDL_Texture *titleTex;

    Enemy enemyHead, *enemyTail;
    Bullet bulletHead, *bulletTail;
    Item itemHead, *itemTail;
    Effect effectHead, *effectTail;
    SDL_Point camera;

    Player *player;
    
    int enemySpawnTimer;
    int pointsSpawnTimer;
    int gameOverTimer;
    int score;
    bool check = false;

    bool titleFlag;
    float titleY;
    float titleDY;
    int timeout;

    Highscore highscores[8];
    bool highscoreFlag;
    int cursorBlink;
    Highscore *newHighscore;

    GameStage();

    void logic();
    void draw();
    void initStage();
    
    void doPlayer();
    void doEnemies();
    void doBullets();
    void doItems();
    void doCamera();
    void doEnemyEffect(Enemy* enemy);
    void bulletHitPlayerEffect();
    void doEffect();

    void drawEnemies();
    void drawBullets();
    void drawHud();
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

    void spawnEnemy();
    void addRandomItem(int x, int y);
    void addHealth(int x, int y);
    void addUziBullet(int x, int y);
    void addShotgunBullet(int x, int y);
    void addEnemyDeathEffect(Enemy* enemy);
    void addPlayerDeathEffect();
    void addBulletHitEffect(Enemy* enemy);
    void bulletHitEntity(Bullet* b);
    void addBonusPoints(int x, int y);
    void spawnPointsPowerup();

    Bullet* createBullet();

    void resetStage();
    void showTitle();
    void doTitle();

    void doHighscore();
    void showHighscore();
    void inputName();
    void drawInputName();
    void drawHighscores();
    void addHighscore(int score);

    Mix_Chunk *sounds[SND_MAX];
    Mix_Music *music;

    void initSounds();
    void loadMusic(const char *filename);
    void playMusic(int loop);
    void playSound(int id, int channel);
    void loadSounds();
};

#endif