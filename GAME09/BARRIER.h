#pragma once
#include "../../libOne/inc/libOne.h"
namespace GAME09 {
    class BARRIER {
    private:
        float x, y;
        int hp;
        static const int SIZE = 20; // 小さなブロック
    public:
        void set(float x, float y) {
            this->x = x;
            this->y = y;
            hp = 2;  // 耐久値
        }

        void update() {

        }

        void draw() {
            if (hp > 0) {
                if (hp == 3) fill(200, 255, 200);
                else if (hp == 2) fill(150, 255, 150);
                else fill(100, 200, 100);
                rect(x, y, SIZE, SIZE);
            }
        }

        void damage() {
            if (hp > 0) hp--;
        }

        bool isAlive() const {
            return hp > 0;
        }
        bool checkHit(float bx, float by) {
            if (!isAlive()) return false;

            float half = SIZE / 2;
            return (bx >= x - half && bx <= x + half &&
                by >= y - half && by <= y + half);
        }
        bool checkHitRect(float x, float y, float w, float h);

        float getX() const { return x; }
        float getY() const { return y; }
    };
}
