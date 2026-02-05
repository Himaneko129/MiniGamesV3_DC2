#pragma once
#include <vector>

namespace GAME00 {

    class Platform;

    class Player {
    public:
        float x = 0;
        float y = 0;
        float vx = 0;
        float vy = 0;
        float width = 40;
        float height = 60;

        bool onGround = false;
        bool onWallLeft = false;
        bool onWallRight = false;

        // ダッシュ関連
        bool isChargingDash = false;
        float dashChargeTimer = 0.6f;
        float dashCooldownTimer = 0.0f;

        // 定数
        static constexpr float DASH_CHARGE_MAX = 1.0f;
        static constexpr float DASH_COOLDOWN_MAX = 1.5f;

        void update(float dt, const std::vector<Platform>& platforms);
        void draw(float camX, float camY);
        void drawDashArrow(float camX, float camY);
    };
}