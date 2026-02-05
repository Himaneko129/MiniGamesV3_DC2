#include "BARRIER.h"
#include <corecrt_math.h>
namespace GAME09{
    bool GAME09::BARRIER::checkHitRect(float x, float y, float w, float h)
    {
        if (!isAlive()) return false;

        float bw = SIZE;
        float bh = SIZE;

        return fabs(x - this->x) < (w / 2 + bw / 2) &&
            fabs(y - this->y) < (h / 2 + bh / 2);
    }

}