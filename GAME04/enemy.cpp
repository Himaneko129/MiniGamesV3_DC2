#include "../../libOne/inc/libOne.h"
#include "enemy.h"
#include <cstdlib>
#include <cmath>
namespace GAME04 {


    extern float scrollX;

    void ENEMY::move(float px, float py)
    {
        if (!active) return;

        if (type == GROUND)
        {
            wx += vx;
        }
        else if (type == FLY)
        {
            float dx = px - wx;
            float dy = py - wy;

            float len = sqrt(dx * dx + dy * dy);
            if (len != 0)
            {
                dx /= len;
                dy /= len;
            }

            float speed = 3.0f;
            wx += dx * speed;
            wy += dy * speed;
        }
        else if (type == RANDOM)
        {
            changeTimer++;

            // ˆê’èŽžŠÔ‚²‚Æ‚És“®•ÏX
            if (changeTimer > 60)
            {
                changeTimer = 0;

                // ƒ‰ƒ“ƒ_ƒ€•ûŒü
                float angle = (rand() % 360) * 3.14159f / 180.0f;
                float speed = (rand() % 4) + 2; // 2?5

                vx = cos(angle) * speed;
                vy = sin(angle) * speed;
            }

            wx += vx;
            wy += vy;
        }
    }
    void ENEMY::draw()
    {
        if (!active) return;
        circle(wx - scrollX, wy, pr);
    }
}