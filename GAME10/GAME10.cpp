//HIGH＆LOW
//#include "../../libOne/inc/libOne.h"
//#include "../MAIN/MAIN.h"
//#include "GAME10.h"
//#include <cstdlib>
//#include <ctime>
//
//namespace GAME10 {
//
//    const int CARD_COUNT = 13;
//    int cardImgs[CARD_COUNT];
//    int soundBGM;
//    int a, b;
//    int streak = 0;
//    int maxStreak = 0;
//    int score = 0;
//    int maxScore = 0;
//    int state = -1;  // -1:ルール説明, 0:待機中, 1:結果表示
//    char resultStr[64] = "";
//
//    int GAME::create() {
//        for (int i = 0; i < CARD_COUNT; i++) {
//            char filename[64];
//            sprintf_s(filename, sizeof(filename), "../MAIN/assets/game10/%d.png", i + 1);
//            cardImgs[i] = loadImage(filename);
//            soundBGM = loadSound("../MAIN/assets/game10/14.wav");
//                                                                             //playLoopSound ...BGM
//                                                                             //playSound...SE
//        }                                                                    //stopSound...BGMを止める　
//                                                                             //volume
//                                                                             //pan 
//
//        srand((unsigned)time(NULL));
//        a = rand() % CARD_COUNT + 1;
//        return 0;
//    }
//
//    void GAME::destroy() {}
//
//    void GAME::proc() {
//        clear(0, 0, 64);
//
//        // ルール説明画面
//        if (state == -1) {
//            textSize(50);
//            fill(255, 255, 0);
//            text("【ルール説明】", 700, 100);
//
//            textSize(40);
//            fill(255);
//            text("表示されたカードより次のカードが", 100, 250);
//            text("High（↑）か Low（↓）かを予想してください。", 100, 310);
//            text("当たると連続正解・スコアが加算されます。", 100, 370);
//            text("3回目以降の連続正解はスコアが倍になります！", 100, 430);
//            text("外れるとスコアは0になります。", 100, 490);
//
//            fill(255, 255, 255);
//            text("スペースキーでゲームスタート", 100, 600);
//            text("Enterキーでメニューに戻る", 100, 700);
//
//            if (isTrigger(KEY_SPACE)) {
//                state = 0;
//                playLoopSound(soundBGM);
//            }
//            if (isTrigger(KEY_ENTER)) main()->backToMenu();
//            return;
//        }
//
//        // スコア・連続表示
//        textSize(50);
//        fill(255, 255, 255);
//        char streakStr[64];
//        sprintf_s(streakStr, sizeof(streakStr), "連続正解: %d 回", streak);
//        text(streakStr, 50, 50);
//
//        char maxStr[64];
//        sprintf_s(maxStr, sizeof(maxStr), "最大連続: %d 回", maxStreak);
//        text(maxStr, 50, 110);
//
//        char scoreStr[64];
//        sprintf_s(scoreStr, sizeof(scoreStr), "スコア: %d 点", score);
//        text(scoreStr, 50, 170);
//
//        char maxScoreStr[64];
//        sprintf_s(maxScoreStr, sizeof(maxScoreStr), "最大スコア: %d 点", maxScore);
//        text(maxScoreStr, 50, 230);
//
//
//
//        float cardY = 40.0f;
//        int cardSpacing = 200;
//        int baseX = 1920 / 2 - 100;
//        float cardX1 = baseX - cardSpacing;
//        float cardX2 = baseX + cardSpacing;
//
//        image(cardImgs[a - 1], cardX1, cardY);
//
//        textSize(40);
//        fill(255);
//
//        if (state == 0) {
//            text("↑キー：High", 50, 850);
//            text("↓キー：Low", 50, 900);
//
//            if (isTrigger(KEY_UP) || isTrigger(KEY_DOWN)) {
//                bool isHigh = isTrigger(KEY_UP);
//                b = rand() % CARD_COUNT + 1;
//                bool correct = (isHigh && b > a) || (!isHigh && b < a);
//
//                if (correct) {
//                    streak++;
//                    if (streak > maxStreak) maxStreak = streak;
//                    int gain = (streak >= 3) ? 20 : 10;
//                    score += gain;
//                    if (score > maxScore) maxScore = score;
//                    sprintf_s(resultStr, sizeof(resultStr), "正解！+%d点 連続 %d 回", gain, streak);
//                }
//                else if (b == a) {
//                    sprintf_s(resultStr, sizeof(resultStr), "引き分け！カウントそのまま(%d回)", streak);
//                }
//                else {
//                    streak = 0;
//                    score = 0;
//                    sprintf_s(resultStr, sizeof(resultStr), "不正解!スコアリセット");
//                }
//                state = 1;
//            }
//        }
//        else if (state == 1) {
//            textSize(38);
//            image(cardImgs[b - 1], cardX2, cardY);
//            text(resultStr, 50, 850);
//            text("スペースキーで次のゲームへ", 50, 900);
//
//            if (isTrigger(KEY_SPACE)) {
//
//                a = b;
//                state = 0;
//            }
//        }
//
//        text("Enterキーでメニューに戻る", 50, 1000);
//        if (isTrigger(KEY_ENTER)) {
//            stopSound(soundBGM);
//            main()->backToMenu();
//        }
//    }
//
//}

//スネークゲーム
#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME10.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>

using namespace std::chrono;

namespace GAME10
{
    struct P { int x, y; };

    // ゲームデータ 
    std::vector<P> snake;
    P food;
    int dx = 1, dy = 0;
    int grid = 40;
    int timer = 0;
    int score = 0;
    bool gameOver = false;
    bool showIntro = true;
    int W, H;

    int moveT = 0;

    // 追加：制限時間関連
    static long long startTime = 0;
    static const int TIME_LIMIT_MS = 20000;
    static int timeBonus = 0;


    // ゲーム初期化 
    int GAME::create() {
        W = 1920;
        H = 1080;

        srand((unsigned)time(NULL));

        snake.clear();
        snake.push_back({ 5, 5 });

        food = { rand() % (W / grid), rand() % (H / grid) };
        dx = 1; dy = 0;
        timer = 0;
        score = 0;
        gameOver = false;
        timeBonus = 0;
        moveT = 0;

        //  追加：開始時間を記録
        startTime = duration_cast<milliseconds>(
            steady_clock::now().time_since_epoch()
        ).count();


        return 0;
    }

    void GAME::destroy() {}

    //メイン処理 
    void GAME::proc() {
        clear(255, 255, 255);
        if (showIntro) {
            fill(0);
            textSize(70);
            text("SNAKE GAME", W / 2 - 220, 200);

            textSize(32);
            text("操作方法", 200, 340);
            text("・WASD / 矢印キーで移動", 200, 390);
            text("・壁や自分の体に当たるとゲームオーバー", 200, 440);
            text("・エサを食べるとスコアUP & 時間が増える", 200, 490);
            text("・制限時間：20秒", 200, 540);

            fill(50, 120, 255);
            textSize(40);
            text("SPACEキーでスタート", W / 2 - 220, 700);

            if (isTrigger(KEY_SPACE)) {
                showIntro = false;

                //  ゲーム開始時刻をここで設定
                startTime = duration_cast<milliseconds>(
                    steady_clock::now().time_since_epoch()
                ).count();
            }
            return;
        }

        // 時間計測
        long long currentTime = duration_cast<milliseconds>(
            steady_clock::now().time_since_epoch()
        ).count();

        long long elapsed = currentTime - startTime;
        long long limit = TIME_LIMIT_MS + timeBonus;
        int remainingTime = max(0, (limit - (int)elapsed) / 1000);

        // ゲームオーバー画面
        if (gameOver) {
            textSize(60);
            fill(255, 0, 0);

            if (elapsed >= limit)
                text("TIME UP!", W / 2 - 150, H / 2 - 120);
            else
                text("GAME OVER", W / 2 - 180, H / 2 - 120);

            textSize(40);
            fill(0);
            text((std::string("SCORE: ") + std::to_string(score)).c_str(), 50, 50);

            text("Press SPACE to Restart", W / 2 - 200, H / 2 + 100);

            if (isTrigger(KEY_SPACE)) {
                create();
            }
            // メニューに戻る
            textSize(30);
            fill(100);
            text("Press ENTER to return menu", 50, H - 50);
            if (isTrigger(KEY_ENTER)) {
                main()->backToMenu();
                return;
            }
            return;
        }


        // 時間切れチェック
        if (elapsed >= limit) {
            gameOver = true;
            return;
        }


        // 入力処理（WASD）

        if (isTrigger(KEY_W) && dy == 0) { dx = 0; dy = -1; }
        if (isTrigger(KEY_S) && dy == 0) { dx = 0; dy = 1; }
        if (isTrigger(KEY_A) && dx == 0) { dx = -1; dy = 0; }
        if (isTrigger(KEY_D) && dx == 0) { dx = 1; dy = 0; }
        if (isTrigger(KEY_UP) && dy == 0) { dx = 0; dy = -1; }
        if (isTrigger(KEY_DOWN) && dy == 0) { dx = 0; dy = 1; }
        if (isTrigger(KEY_LEFT) && dx == 0) { dx = -1; dy = 0; }
        if (isTrigger(KEY_RIGHT) && dx == 0) { dx = 1; dy = 0; }


        // 移動処理
        timer++;

        moveT++;
        if (moveT >= 5) {
            moveT = 0;
            P head = snake[0];
            P newHead = { head.x + dx, head.y + dy };

            // 壁チェック
            if (newHead.x < 0 || newHead.x >= W / grid || newHead.y < 0 || newHead.y >= H / grid) {
                gameOver = true;
                return;
            }

            // 自分の体に当たったか
            for (size_t i = 1; i < snake.size(); i++) {
                if (newHead.x == snake[i].x && newHead.y == snake[i].y) {
                    gameOver = true;
                    return;
                }

            }

            // エサを食べた
            if (newHead.x == food.x && newHead.y == food.y) {
                snake.insert(snake.begin(), newHead);
                score += 10;
                timeBonus += 3000;
                food = { rand() % (W / grid), rand() % (H / grid) };
            }
            else {
                snake.insert(snake.begin(), newHead);
                snake.pop_back();
            }
        }






        // グリッド
        fill(255, 0, 0);
        strokeWeight(0.2);
        for (int x = 0; x < W; x += grid) line(x, 0, x, H);
        for (int y = 0; y < H; y += grid) line(0, y, W, y);
        noStroke();

        // エサ
        fill(255, 100, 100);
        rect(food.x * grid, food.y * grid, grid, grid);
    

        // スネーク
        fill(0, 200, 0);
        for (auto& p : snake) {
            rect(p.x * grid, p.y * grid, grid, grid);
        }


        // スコア
        fill(0);
        textSize(40);
        text((std::string("SCORE: ") + std::to_string(score)).c_str(), 50, 50);

        //  追加：残り時間表示 
        text((std::string("TIME: ") + std::to_string(remainingTime) + " 秒").c_str(), 50, 100);

        // メニューに戻る
        textSize(30);
        fill(100);
        text("Press ENTER to return menu", 50, H - 50);
        if (isTrigger(KEY_ENTER)) {
            main()->backToMenu();
            return;
        }
    }
}