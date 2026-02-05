#include "../../libOne/inc/libOne.h"
#include "player.h"

namespace GAME04 {

    extern float scrollX;
    void PLAYER::move()
    {
        const float MOVE = 5;
        const float GRAVITY = 1.2f;

        // ノックバック中は操作不能
        if (knockTimer > 0)
        {
            knockTimer--;
        }
        else
        {
            if (isPress(KEY_D)) vx = MOVE;
            else if (isPress(KEY_A)) vx = -MOVE;
            else vx = 0;

            if (isTrigger(KEY_W) && onGround)
            {
                vy = -18;
                onGround = false;
            }
        }

        vy += GRAVITY;

        wx += vx;
        wy += vy;

        if (wy > 800)
        {
            wy = 800;
            vy = 0;
            onGround = true;
        }

        scrollX = wx - 400;
        if (scrollX < 0) scrollX = 0;

        if (invincibleTimer > 0)
            invincibleTimer--;

       

    }

    void PLAYER::draw()
    {
        circle(wx - scrollX, wy, pr);
    }
}