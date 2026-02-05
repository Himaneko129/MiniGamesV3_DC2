#pragma once
namespace GAME04 {

    class STEP {
    public:
        float x, y;
        float w, h;

        STEP(float _x, float _y, float _w, float _h)
            : x(_x), y(_y), w(_w), h(_h) {
        }

        void draw();
    };

}

