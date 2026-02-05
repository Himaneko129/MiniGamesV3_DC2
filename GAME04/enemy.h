#pragma once
namespace GAME04 {
    enum ENEMY_TYPE {
        GROUND,
        FLY,
        RANDOM
    };

    class ENEMY {
    public:
        float wx, wy;
        float vx, vy;
        float pr = 25;
        int hp = 3;
        bool active = true;
        ENEMY_TYPE type;
        int shootTimer = 0;
        ENEMY(float x, ENEMY_TYPE t = GROUND)
            : wx(x), wy(800), vx(-2), vy(0), type(t) {
            if (type == RANDOM)
                pr = 200;   // Åö ëÂÇ´Ç≠
            else
                pr = 25;   // í èÌ
        }
     
        void move(float px, float py);
        void draw();
        int changeTimer = 0;
    };
}