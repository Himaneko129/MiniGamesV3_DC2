#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME06.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>
#include <windows.h>

bool isMouseLeftPressed() {
    return isPress(MOUSE_LBUTTON);
}

int getMouseX() {
#if 0
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(GetForegroundWindow(), &p);
    return p.x;
#else
    return mouseX;
#endif
}
int getMouseY() {
#if 0
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(GetForegroundWindow(), &p);
    return p.y;
#else
    return mouseY;
#endif
}

using namespace std::chrono;

namespace GAME06 {

    static int circleX, circleY;
    static int radius = 50;

    static int score = 0;
    static int highScore = 0;

    static long long lastUpdateTime = 0;
    static long long startTime = 0;

    static const int TIME_LIMIT_MS = 60000;

    static const int MAX_LIFE = 3;
    static int life = MAX_LIFE;

    static bool prevMouse = false;

    // GREAT表示
    static bool showGreat = false;
    static long long greatTime = 0;
    static const int GREAT_DISPLAY_MS = 500;

    // MISS表示
    static bool showMiss = false;
    static long long missTime = 0;
    static const int MISS_DISPLAY_MS = 500;

    static bool gameStarted = false;

    int GAME::create() {
        srand((unsigned int)time(nullptr));

        radius = rand() % 71 + 30;
        circleX = rand() % (1920 - 2 * radius) + radius;
        circleY = rand() % (1080 - 2 * radius) + radius;

        score = 0;
        life = MAX_LIFE;

        showGreat = false;
        showMiss = false;
        gameStarted = false;
        prevMouse = false;

        return 0;
    }

    void GAME::destroy() {}

    void GAME::proc() {

        clear(0,0,0);

        // スタート画面
        if (!gameStarted) {
            fill(255, 255, 0);
            textSize(48);
            text("出現する緑の円をクリックして", 520, 340);
            text("スコアを加算しよう！", 600, 400);
            text("ミスするとライフが減るぞ！", 560, 460);

            textSize(32);
            text("Aキーでゲームスタート", 650, 540);

            if (isTrigger(KEY_A)) {
                gameStarted = true;
                long long now = duration_cast<milliseconds>(
                    steady_clock::now().time_since_epoch()).count();
                startTime = now;
                lastUpdateTime = now;
            }
            return;
        }

        long long currentTime = duration_cast<milliseconds>(
            steady_clock::now().time_since_epoch()).count();

        long long elapsed = currentTime - startTime;
        int remainingTime = max(0, (TIME_LIMIT_MS - (int)elapsed) / 1000);

        // リザルト
        if (elapsed >= TIME_LIMIT_MS || life <= 0) {
            if (score > highScore) highScore = score;

            clear(0,0,0);
            fill(255);
            textSize(64);

            if (life <= 0)
                text("GAME OVER", 720, 260);
            else
                text("TIME UP", 760, 260);

            textSize(36);
            text(("最終スコア: " + std::to_string(score)).c_str(), 700, 340);
            text(("ハイスコア: " + std::to_string(highScore)).c_str(), 700, 390);

            textSize(28);
            text("ENTERキーでメニューに戻る", 650, 460);
            text("Zキーで再プレイ", 650, 500);

            if (isTrigger(KEY_ENTER)) main()->backToMenu();
            if (isTrigger(KEY_Z)) create();
            return;
        }

        // UI
        fill(255);
        textSize(32);
        text(("スコア: " + std::to_string(score)).c_str(), 50, 50);
        text(("残り時間: " + std::to_string(remainingTime) + "秒").c_str(), 50, 90);
        text(("LIFE: " + std::to_string(life)).c_str(), 50, 130);

        // 円移動
        if (currentTime - lastUpdateTime >= 3000) {
            radius = rand() % 71 + 30;
            circleX = rand() % (1920 - 2 * radius) + radius;
            circleY = rand() % (1080 - 2 * radius) + radius;
            lastUpdateTime = currentTime;
        }

        // 円描画
        fill(0, 255, 0);
        circle((float)circleX, (float)circleY, (float)radius);

        // GREAT表示
        if (showGreat) {
            if (currentTime - greatTime <= GREAT_DISPLAY_MS) {
                fill(255, 255, 0);
                textSize(48);
                text("GREAT!", circleX - 70, circleY - radius - 20);
            }
            else {
                showGreat = false;
            }
        }

        // MISS表示
        if (showMiss) {
            if (currentTime - missTime <= MISS_DISPLAY_MS) {
                fill(128, 128, 128); 
                textSize(48);
                text("MISS", circleX - 50, circleY - radius - 20);
            }
            else {
                showMiss = false;
            }
        }

        // クリック判定
        bool nowMouse = isMouseLeftPressed();

        if (nowMouse && !prevMouse) {
            int mx = getMouseX();
            int my = getMouseY();
            int dx = mx - circleX;
            int dy = my - circleY;

            if (dx * dx + dy * dy <= radius * radius) {
                // 当たり
                if (radius >= 70) score += 1;
                else if (radius >= 50) score += 2;
                else score += 3;

                showGreat = true;
                greatTime = currentTime;

                radius = rand() % 71 + 30;
                circleX = rand() % (1920 - 2 * radius) + radius;
                circleY = rand() % (1080 - 2 * radius) + radius;
                lastUpdateTime = currentTime;
            }
            else {
                // ハズレ
                life--;
                showMiss = true;
                missTime = currentTime;
            }
        }

        prevMouse = nowMouse;
    }
}

