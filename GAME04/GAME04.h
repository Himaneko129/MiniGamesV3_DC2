#include <vector>
#pragma once
#include "../MAIN/GAME_BASE.h"
#include "player.h"
#include "enemy.h"
#include "STEP.h"
namespace GAME04
{
    class GAME :
        public GAME_BASE {

    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() { destroy(); };
        int create();
        void proc();
        void destroy();
        void move();
        void draw();
        void drawTitle();
        void drawClearBackground();
        void drawClearLight();
        int score = 0;
      
        class PLAYER* player = nullptr;
        class ENEMY* enemy = nullptr;
       
        std::vector<ENEMY*> enemies;
        std::vector<STEP*> steps;
    };
}
