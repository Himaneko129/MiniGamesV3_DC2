#pragma once
#include <vector>
#include "INVADER.h"
#include "ENEMY_BULLET.h"
#include "BULLET.h"
#include"ITEM.h"
#include"PLAYER.h"
  
class INVADER_MANAGER {
private:
    std::vector<INVADER> invaders;  
    std::vector<ENEMY_BULLET> enemyBullets;
    std::vector<ITEM> items;
    int img;
    int fastImg;
    int se_hit;
    int itemImg;
    int phase = 1;
    float invaderSpead = 1.0f;
    
    const int ROW = 5;  // çsêî
    const int COL = 7; // óÒêî

    void createInvaders();

public:
    void load();
    void reset();
    void update(PLAYER& player,std::vector<BULLET>& bullets, float playerX, float playerY, bool& gameOver, bool& gameClear, int& score);

    void preparePhase(int newPhase);
    void startPhase();

    void nextPhase();
    void draw();
    bool isAllDead();
    
    std::vector<INVADER>& getInvaders() { return invaders; }     
    std::vector<ENEMY_BULLET>& getEnemyBullets() { return enemyBullets; }
};
