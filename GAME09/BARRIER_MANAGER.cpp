
#include "BARRIER_MANAGER.h"
constexpr float INVADER_W = 32.0f;
constexpr float INVADER_H = 32.0f;

void BARRIER_MANAGER::create() {
    barriers.clear();
    const int numBarriers = 4;           
    const float spacing = 300.0f;        
    const float barrierWidth = 4 * 20.0f;  
    const float totalWidth = numBarriers * barrierWidth + (numBarriers - 1) * spacing;
    const float startX = (1920 - totalWidth) / 2.0f;  
    const float y = 800.0f;

    for (int i = 0; i < numBarriers; i++) {
        float baseX = startX + i * (barrierWidth + spacing);
        for (int bx = 0; bx < 4; ++bx) {
            for (int by = 0; by < 3; ++by) {
                GAME09::BARRIER b;
                b.set(baseX + bx * 20, y + by * 20);
                barriers.push_back(b);
            }
        }
    }
}

void BARRIER_MANAGER::update(std::vector<ENEMY_BULLET>& enemyBullets, std::vector<BULLET>& playerBullets, std::vector<INVADER>& invaders) {
	for (auto& b : enemyBullets) {
		if (b.isDead()) continue;
		for (auto& barrier : barriers) {
			if (barrier.checkHit(b.getX(), b.getY())){
                barrier.damage();
				b.setDead();
				break;
			}
		}
	}
    for (auto& b : playerBullets) {
        if (b.isDead()) continue;
        for (auto& barrier : barriers) {
            if (barrier.checkHit(b.getX(), b.getY())) {
                b.setDead();   // 弾だけ消す（バリアは削らない）
                break;
            }
        }
    }
    //for (auto& inv : invaders) {
    //    if (!inv.isAlive()) continue;
    //    for (auto& barrier : barriers) {
    //        if (barrier.checkHit(inv.getX(), inv.getY())) {
    //            barrier.damage();   // 敵は通過、バリアだけ削れる
    //            break;
    //        }
    //    }
    //}
    for (auto& inv : invaders) {
        if (!inv.isAlive()) continue;

        for (auto& barrier : barriers) {
            if (barrier.checkHitRect(
                inv.getX(),
                inv.getY(),
                INVADER_W,
                INVADER_H))
            {
                barrier.damage();
                break;
            }
        }
    }

}

void BARRIER_MANAGER::draw() {
	for (auto& barrier : barriers) {
		barrier.draw();
	}
}
