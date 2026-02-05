#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME00.h"
#include "Player.h"
#include "CourseManager.h"
#include "CourseData.h"
#include "Rect.h"
#include "Sound.h"
#include <cmath>

namespace GAME00 {

    static bool hitRect(float ax, float ay, float aw, float ah,
        float bx, float by, float bw, float bh) {
        return ax < bx + bw && ax + aw > bx && ay < by + bh && ay + ah > by;
    }

    bool isOpenSettingsButton(float x, float y, float w, float h)
    {
        return isTrigger(MOUSE_LBUTTON) &&
            mouseX > x && mouseX < x + w &&
            mouseY > y && mouseY < y + h;
    }

    void Player::update(float dt, const std::vector<Platform>& platforms)
    {
        float prevX = x;
        float prevY = y;

        // ---------- 通常移動 ----------
        if (isPress(KEY_A)) vx -= 1.0f;
        if (isPress(KEY_D)) vx += 1.0f;

        // 横の最大速度制限
        if (vx > 9) vx = 9;
        if (vx < -9) vx = -9;

        // ジャンプ
        if (isTrigger(KEY_SPACE)) {

            // 通常ジャンプ
            if (onGround) {
                vy = -11.0f;
                onGround = false;
            }
            // 壁ジャンプ
            else if (onWallLeft) {
                vy = -9.0f;
                vx = 6.5f;   // 右へ跳ねる
            }
            else if (onWallRight) {
                vy = -9.0f;
                vx = -6.5f;  // 左へ跳ねる
            }
        }

        // 重力
        vy += 0.3f;
        if (vy > 18) vy = 18;

        if (!onGround && (onWallLeft || onWallRight)) {
            if (vy > 3.0f) vy = 3.0f;
        }

        // ---------- ダッシュ ----------
        if (dashCooldownTimer > 0) {
            dashCooldownTimer -= dt;
            if (dashCooldownTimer < 0) dashCooldownTimer = 0;
        }

        if (isPress(MOUSE_RBUTTON) && dashCooldownTimer <= 0) {
            isChargingDash = true;
            dashChargeTimer += dt;
            if (dashChargeTimer > DASH_CHARGE_MAX)
                dashChargeTimer = DASH_CHARGE_MAX;
        }

        if (isChargingDash && isRelease(MOUSE_RBUTTON)) {

            float dx = mouseX - x;
            float dy = mouseY - y;
            float len = sqrtf(dx * dx + dy * dy);
            if (len == 0) len = 1;

            dx /= len;
            dy /= len;

            float power = 10.0f + dashChargeTimer * 18.0f;

            vx += dx * power;
            vy += dy * power;

            dashChargeTimer = 0;
            dashCooldownTimer = DASH_COOLDOWN_MAX;
            isChargingDash = false;
        }

        // ---------- 摩擦 ----------
        vx *= 0.99f;

        // ---------- 移動 ----------
        x += vx * dt;
        y += vy * dt;

        onGround = false;
        onWallLeft = false;
        onWallRight = false;

        for (auto& p : platforms) {

            if (x - width / 2 >= p.x + p.w ||
                x + width / 2 <= p.x ||
                y <= p.y ||
                y - height >= p.y + p.h)
                continue;

            // 左右の壁
            if (prevX + width / 2 <= p.x) {
                x = p.x - width / 2;
                vx = 0;
                onWallRight = true;
            }
            else if (prevX - width / 2 >= p.x + p.w) {
                x = p.x + p.w + width / 2;
                vx = 0;
                onWallLeft = true;
            }

            // 上から着地
            if (prevY <= p.y && vy >= 0) {
                y = p.y;
                vy = 0;
                onGround = true;
            }

            // 下から頭ぶつけ
            if (prevY - height >= p.y + p.h && vy < 0) {
                y = p.y + p.h + height;
                vy = 0;
            }
        }
    }

    void Player::draw(float camX, float camY) {
        fill(255, 200, 0);
        rect(x - width / 2 - camX, y - height - camY, width, height);
    }

    void Player::drawDashArrow(float camX, float camY)
    {
        if (!isChargingDash) return;

        float px = x - camX;
        float py = y - height * 0.5f - camY;

        float dx = mouseX - px;
        float dy = mouseY - py;
        float len = sqrtf(dx * dx + dy * dy);
        if (len == 0) len = 1;

        dx /= len;
        dy /= len;

        float rate = dashChargeTimer / DASH_CHARGE_MAX;

        float dist = 40 + rate * 40;
        float w = 14 + rate * 6;
        float h = 6;

        fill(255, 80, 80);

        for (int i = 0; i < 4; i++) {
            rect(
                px + dx * (dist + i * 6) - w / 2,
                py + dy * (dist + i * 6) - h / 2,
                w,
                h
            );
        }
    }

    int GAME::create() {
        initBGM();
        menuX = 1700;
        menuY = 20;
        menuW = 180;
        menuH = 80;
        soundVol = 20;
        setBGMVolume(soundVol);
        isMiss = 0;
        fallCount = 0;
        camX = camY = 0;
        startTimer = 0;
        camOffsetY = targetOffsetY = 920;
        fadeAlpha = 0;
        goalTimer = 0;
        state = GameState::TITLE;
        selectedStage = 0;
        playBGM(BGMType::TITLE);
        return 0;
    }

    void GAME::destroy() {
        stopBGM();
    }

    void GAME::updateTitle() {
        if (isOpenSettingsButton(1100, 20, 150, 50)) {
            prevState = state;
            state = GameState::PAUSE_SETTINGS;
            return;
        }

        if (isTrigger(KEY_ENTER)) {
            state = GameState::OPERATION;
        }

        if (isTrigger(KEY_M)) {
            main()->backToMenu();
        }
    }

    void GAME::drawTitle() {
        fill(255);
        textSize(96);
        text("2D GAME", 520, 350);

        textSize(32);
        text("PRESS ENTER to START   PRESS M to main", 760, 520);
    }

    void GAME::updateOperation()
    {
        // ENTER → ステージセレクト
        if (isTrigger(KEY_ENTER)) {
            playBGM(BGMType::STAGE);
            state = GameState::STAGE_SELECT;
        }

        // B → タイトルへ戻る
        if (isTrigger(KEY_B)) {
            state = GameState::TITLE;
        }

        // M → メインメニュー
        if (isTrigger(KEY_M)) {
            main()->backToMenu();
        }
    }

    void GAME::drawOperation()
    {
        fill(255);
        textSize(64);
        text("HOW TO PLAY", 620, 180);

        textSize(28);
        text("A / D        : MOVE", 620, 300);
        text("SPACE        : JUMP", 620, 350);
        text("RIGHT CLICK : DASH (HOLD) ※不具合有", 620, 400);
        text("MOUSE        : DASH DIRECTION", 620, 450);

        text("O            : SETTINGS", 620, 520);
        text("B            : BACK", 620, 570);

        textSize(24);
        text("PRESS ENTER TO CONTINUE", 620, 680);
    }

    void GAME::updateStageSelect() {

        if (isTrigger(KEY_UP)) selectedStage = (selectedStage + 2) % 3;
        if (isTrigger(KEY_DOWN)) selectedStage = (selectedStage + 1) % 3;

        if (isTrigger(KEY_ENTER)) {
            switch (selectedStage) {
            case 0: courseManager.load(COURSE_1, player); break;
            case 1: courseManager.load(COURSE_2, player); break;
            case 2: courseManager.load(COURSE_3, player); break;
            }

            playTime = 0.0f;
            remainTime = TIME_LIMIT;
            score = 0;
            resultAlpha = 0.0f;

            camX = camY = 0;
            camOffsetY = targetOffsetY = 920;
            fadeAlpha = 0; goalTimer = 0;
            state = GameState::PLAYING;
        }
        if (isTrigger(KEY_M)) {
            main()->backToMenu();
        }
    }

    void GAME::drawStageSelect() {
        fill(255); textSize(64);
        text("STAGE SELECT", 620, 200);

        const char* names[] = { "STAGE 1","STAGE 2","STAGE 3" };
        for (int i = 0; i < 3; i++) {
            if (i == selectedStage) { fill(255, 255, 0); text("> ", 650, 350 + i * 80); text(names[i], 690, 350 + i * 80); }
            else { fill(180); text(names[i], 680, 350 + i * 80); }
        }
        fill(200); textSize(28); text("UP/DOWN Select   ENTER Confirm   M main", 620, 650);
    }

    void GAME::updatePlaying()
    {
        float dt = 1.0f;

        player.update(dt, courseManager.platforms);

        // カメラ追従
        camX += (player.x - 740 - camX) * 0.1f;
        camY += (player.y - 740 - camY) * 0.1f;

        playTime += dt;
        remainTime = (TIME_LIMIT - playTime) * 60;
        if (remainTime < 0) remainTime = 0;

        if (state != GameState::PLAYING) return;
        startTimer += 1.0f;

        // カメラ追従
        float targetCamX = player.x - 740;
        float targetCamY = player.y - camOffsetY;

        if (player.vy < 0) {
            targetOffsetY = 780;
        }
        else {
            targetOffsetY = 740;
        }

        camOffsetY += (targetOffsetY - camOffsetY) * 0.08f;

        camX += (targetCamX - camX) * 0.1f;
        camY += (targetCamY - camY) * 0.1f;

        if (
            startTimer > 30 &&
            player.x - player.width / 2 < courseManager.goal.x + courseManager.goal.w &&
            player.x + player.width / 2 > courseManager.goal.x &&
            player.y - player.height < courseManager.goal.y + courseManager.goal.h &&
            player.y > courseManager.goal.y
            ) {
            isMiss = false;
            // 残り時間スコア
            int timeScore = (int)remainTime * 10;
            // 落下ペナルティ
            int fallPenalty = fallCount * 500;

            score = timeScore - fallPenalty;
            if (score < 0) score = 0;

            state = GameState::FADE_OUT;
            fadeAlpha = 0.0f;

        }
        // 落下判定
        if (player.y > FALL_LIMIT_Y) {
            fallCount++;
            isMiss = true;
            state = GameState::FADE_OUT;
            fadeAlpha = 0.0f;
            return;
        }
        if (remainTime <= 0) {
            remainTime = 0;
            isMiss = true;
            state = GameState::FADE_OUT;
            fadeAlpha = 0.0f;
        }

    }

    void GAME::updateFadeOut() {
        fadeAlpha += 4.0f;
        if (fadeAlpha >= 255) {
            fadeAlpha = 255;

            if (isMiss) {
                courseManager.reload(player);

                isMiss = false;
                startTimer = 0;
                fadeAlpha = 0;
                playTime = 0.0f;
                remainTime = TIME_LIMIT;

                state = GameState::PLAYING;
            }
            else {
                resultAlpha = 0.0f;

                state = GameState::RESULT_WAIT;
            }
        }
    }

    void GAME::updateResultWait() {
        resultAlpha += 4.0f;
        if (resultAlpha > 255) resultAlpha = 255;

        if (isTrigger(KEY_ENTER)) {
            fadeAlpha = 0;
            playBGM(BGMType::STAGE);
            state = GameState::STAGE_SELECT;
        }

        if (isTrigger(KEY_M)) {
            fadeAlpha = 0;
            playBGM(BGMType::TITLE);
            main()->backToMenu();
        }
    }

    void GAME::drawResultUI() {
        if (state != GameState::RESULT_WAIT) return;

        int a = (int)resultAlpha;

        // CLEAR!!
        fill(255, 255, 0, a);
        textSize(96);
        text("CLEAR!!", 620, 300);

        // TIME
        fill(255, 255, 255, a);
        textSize(36);
        char buf[64];
        sprintf_s(buf, "TIME : %02d:%02d",
            (int)remainTime / 60,
            (int)remainTime % 60);
        text(buf, 620, 420);

        // SCORE
        sprintf_s(buf, "SCORE : %d", score);
        text(buf, 620, 470);

        // 操作案内
        fill(200, 200, 200, a);
        textSize(28);
        text("ENTER : ステージセレクト", 620, 560);
        text("M : メインメニュー", 620, 600);

        //落下回数
        char fallbuf[64];
        sprintf_s(fallbuf, "FALL : %d", fallCount);
        text(fallbuf, 580, 640);

    }

    void GAME::drawWorld()
    {
        // 足場
        for (auto& p : courseManager.platforms) {
            p.draw(camX, camY);
        }

        // ゴール
        fill(0, 255, 0);
        rect(courseManager.goal.x - camX,
            courseManager.goal.y - camY,
            courseManager.goal.w,
            courseManager.goal.h);

        // プレイヤー
        player.draw(camX, camY);

        // ダッシュ方向矢印
        player.drawDashArrow(camX, camY);

        // UI
        fill(255);
        textSize(28);

        int remainSec = (int)(remainTime / 60);
        if (remainSec < 0) remainSec = 0;

        int min = remainSec / 60;
        int sec = remainSec % 60;

        char timeBuf[32];
        sprintf_s(timeBuf, "TIME %02d:%02d", min, sec);
        text(timeBuf, 20, 40);

        char fallBuf[32];
        sprintf_s(fallBuf, "FALL %d", fallCount);
        text(fallBuf, 20, 70);
    }

    void GAME::drawFade() {
        if (fadeAlpha > 0) {
            fill(0, 0, 0, (int)fadeAlpha);
            rect(0, 0, 1920, 1080);
        }
    }

    void GAME::drawSettingButton()
    {
        fill(220);
        rect(menuX, menuY, menuW, menuH);

        fill(0);
        textSize(28);
        text("SET", menuX + 60, menuY + 45);
    }

    void GAME::updateSettingButton()
    {
        nowMouse = isPress(MOUSE_LBUTTON);

        if (nowMouse && !prevMouse) {
            if (MouseX > menuX && MouseX < menuX + menuW &&
                MouseY > menuY && MouseY < menuY + menuH) {

                state = GameState::PAUSE_SETTINGS;
            }
        }
        prevMouse = nowMouse;
    }

    void GAME::updateSettings()
    {
        // B：タイトルへ戻る
        if (isTrigger(KEY_B)) {
            stopBGM();
            playBGM(BGMType::TITLE);

            state = GameState::TITLE;
            return;
        }

        // 音量調整
        if (isTrigger(KEY_LEFT)) {
            soundVol -= 10;
            if (soundVol < 0) soundVol = 0;
            setBGMVolume(soundVol);
        }
        if (isTrigger(KEY_RIGHT)) {
            soundVol += 10;
            if (soundVol > 100) soundVol = 100;
            setBGMVolume(soundVol);
        }
    }

    void GAME::drawSettings()
    {
        // 背景暗転
        fill(0, 0, 0, 180);
        rect(0, 0, 1920, 1080);

        fill(255);
        rect(600, 300, 720, 360);

        fill(0);
        textSize(48);
        text("SETTINGS", 820, 360);

        textSize(32);
        char buf[32];
        sprintf_s(buf, "BGM VOLUME : %d%%", soundVol);
        text(buf, 740, 450);

        textSize(24);
        text("← / → : CHANGE", 820, 520);
        text("O  : BACK", 860, 570);
        text("B  : TITLE", 860, 620);
    }

    void GAME::proc()
    {
        clear(0, 0, 64);

        // Oキー：設定メニューの開閉
        if (isTrigger(KEY_O)) {
            if (state == GameState::PAUSE_SETTINGS) {
                state = prevState;
            }
            else {
                prevState = state;
                state = GameState::PAUSE_SETTINGS;
            }
        }
        updateSettingButton();
        drawSettingButton();

        setBGMVolume(soundVol);

        switch (state) {
        case GameState::TITLE:
            updateTitle();
            drawTitle();
            break;

        case GameState::OPERATION:      // ← 追加
            updateOperation();
            drawOperation();
            break;

        case GameState::STAGE_SELECT:
            updateStageSelect();
            drawStageSelect();
            break;

        case GameState::PLAYING:
            updatePlaying();
            drawWorld();
            break;

        case GameState::FADE_OUT:
            updateFadeOut();
            drawWorld();
            break;

        case GameState::RESULT_WAIT:
            updateResultWait();
            drawWorld();
            break;

        case GameState::PAUSE_SETTINGS:
            updateSettings();
            drawWorld();
            drawSettings();
            break;
        }

        drawFade();
        drawResultUI();
    }
}
