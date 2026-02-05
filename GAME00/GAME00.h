#pragma once
#include "../MAIN/GAME_BASE.h"
#include "Player.h"
#include "CourseManager.h"

namespace GAME00 {

    enum class GameState {
        TITLE,
        OPERATION,
        STAGE_SELECT,
        PLAYING,
        PAUSE_SETTINGS,
        FADE_OUT,
        RESULT_WAIT
    };

    class GAME : public GAME_BASE {
    public:
        GAME(class MAIN* main) : GAME_BASE(main) {}
        ~GAME() {}

        int create();
        void proc();
        void destroy();

    private:
        // ===== 状態 =====
        GameState state = GameState::TITLE;
        GameState prevState = GameState::TITLE;
        Player player;
        CourseManager courseManager;

        // ===== カメラ =====
        float camX = 0, camY = 0;
        float camOffsetY = 920;
        float targetOffsetY = 920;

        // ===== ゲーム進行 =====
        bool isMiss = false;
        bool nowMouse = false;
        float fadeAlpha = 0;
        float resultAlpha = 0;
        float goalTimer = 0;
        float startTimer = 0;


        // ===== スコア =====
        const float TIME_LIMIT = 5000.0f;
        float playTime = 0;
        float remainTime = 300;
        int score = 0;
        int fallCount = 0;

        // ===== 入力 =====
        bool prevMouse = false;

        // ===== 音 =====
        int soundVol;

        // ===== ステージ =====
        int selectedStage = 0;

        // ===== 定数 =====
        const float FALL_LIMIT_Y = 2000.0f;

        // 右上サウンドメニュー
        int menuX = 1700;
        int menuY = 20;
        int menuW = 180;
        int menuH = 80;

        // ===== 関数 =====
        void updateTitle();
        void drawTitle();
        void updateOperation();
        void drawOperation();
        void updateStageSelect();
        void drawStageSelect();
        void updatePlaying();
        void updateFadeOut();
        void updateResultWait();
        void drawWorld();
        void drawFade();
        void drawResultUI();
        void drawSettingButton();
        void updateSettingButton();
        void drawSettings();
        void updateSettings();
    };
}
