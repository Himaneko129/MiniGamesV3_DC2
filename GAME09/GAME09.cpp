#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME09.h"
#include"PLAYER.h"
#include "../MAIN/GAME_BASE.h"
#include <string>
#include <fstream>
#include <algorithm>
namespace GAME09
{
    void drawBackground(int img)
    {
        float sx = (float)width / 1920.0f;
        float sy = (float)height / 1080.0f;
        float scale = (sx > sy) ? sx : sy;

        image(img, VECTOR(0, 0), 0.0f, scale);
    }


    int GAME::create()
    {
        rectMode(CENTER);
        hideCursor();
        bgm = loadSound("../MAIN/assets/GAME09/BGM.wav");
        titleBgm = loadSound("../MAIN/assets/GAME09/TITLEBGM.wav");
        backImg = loadImage("../MAIN/assets/GAME09/backImg.png");

        // ハイスコア読み込み
        std::ifstream in("../MAIN/assets/GAME09/highscore.txt");
        if (in.is_open()) {
            in >> highScore;
            in.close();
        }
        else {
            highScore = 0;
        }
        loadRanking();
        state = STATE_TITLE;  //タイトル画面
        return 0;
    }
    void GAME::saveRanking()
    {
        std::ofstream out("../MAIN/assets/GAME09/ranking.txt");
        for (int s : scoreHistory) {
            out << s << std::endl;
        }
    }
    void GAME::loadRanking()
    {
        scoreHistory.clear();

        std::ifstream in("../MAIN/assets/GAME09/ranking.txt");
        int s;
        while (in >> s) {
            scoreHistory.push_back(s);
        }

        std::sort(scoreHistory.begin(), scoreHistory.end(), std::greater<int>());

        if (scoreHistory.size() > 10) {
            scoreHistory.resize(10);
        }
    }

    void GAME::destroy()
    {
        stopSound(bgm);
    }

    void GAME::resetGame() {
        player.load();
        invaderManager.reset();
        barrierManager.create();
        score = 0;
        gameOver = false;
        gameClear = false;
        saved = false;
        currentPhase = 1;
        phaseChanging = false;
        phaseStartTimer = 0;
        playTime = 0.0f;
        clearBonus = 0;
    }

    void GAME::updateHighScore() {
        if (score > highScore) {
            highScore = score;

            std::ofstream out("../MAIN/assets/GAME09/highscore.txt");
            if (out.is_open()) {
                out << highScore;
                out.close();
            }
        }
    }
    void GAME::proc() {

        switch (state) {
        case STATE_TITLE:
            if (!titleBgmPlaying) {
                playSound(titleBgm);
                titleBgmPlaying = true;
                titleBgmTimer = TITLE_BGM_LENGTH;
            }
            if (titleBgmPlaying) {
                titleBgmTimer--;
                if (titleBgmTimer <= 0) {
                    playSound(titleBgm);
                    titleBgmTimer = TITLE_BGM_LENGTH;
                }
            }

            clear(0, 0, 64);
            drawBackground(backImg);

            showRanking = isPress(KEY_SHIFT);
            if (!showRanking) {
                fill(255);
                textSize(150);
                text("SPACE INVADERS", 450, 300);
                textSize(50);
                text(("HIGHSCORE : " + std::to_string(highScore)).c_str(), 1400, 50);


                textSize(60);
                text("Press ENTER to Start", 500, 600);

                textSize(40);
                text("SHIFTキーでランキング", 500, 680);

                textSize(40);
                text("操作説明:", 200, 750);
                text("← → : 移動", 200, 800);
                text("SPACE : ショット", 200, 850);
                text("赤い弾 ：連射アイテム・・・時間制限あり", 200, 900);
                text("青い弾 ：加速アイテム・・・時間制限あり", 200, 950);
                text("Mキーでメニュー画面に戻る", 200, 1000);
                if (isTrigger(KEY_M)) {
                    main()->backToMenu();
                    return;
                }
                if (isTrigger(KEY_ENTER)) {
                    stopSound(titleBgm);
                    titleBgmPlaying = false;

                    playSound(bgm);
                    bgmPlaying = true;

                    resetGame();
                    playSound(bgm);
                    bgmPlaying = true;
                    bgmTimer = BGM_LENGTH;
                    state = STATE_PLAY;
                }
            }
            else {
                // ===== ランキング画面 =====
                fill(255);
                textSize(120);
                text("RANKING", 650, 200);

                textSize(50);
                for (int i = 0; i < scoreHistory.size(); i++) {
                    std::string line =
                        std::to_string(i + 1) + ". " +
                        std::to_string(scoreHistory[i]);
                    text(line.c_str(), 650, 300 + i * 60);
                }

            }
            break;

        case STATE_PLAY:
            clear(0, 0, 64);
            drawBackground(backImg);
            if (!gameOver && !gameClear) {
                playTime += 1.0f / 60.0f;
                if (bgmPlaying) {
                    bgmTimer--;
                    if (bgmTimer <= 0) {
                        playSound(bgm);
                        bgmTimer = BGM_LENGTH;
                    }
                }
                player.update();
                invaderManager.update(player, player.getBullets(),
                    player.getX(), player.getY(),
                    gameOver, gameClear, score);
                barrierManager.update(invaderManager.getEnemyBullets(),
                    player.getBullets(),
                    invaderManager.getInvaders());

                // 敵が全滅したら次フェーズへ
                if (!phaseChanging && invaderManager.isAllDead()) {
                    if (currentPhase == 3) {
                        gameClear = true;
                        // ボーナス計算
                        const float BEST_TIME = 150.0f;
                        const int MAX_BONUS = 5000;

                        float diff = playTime - BEST_TIME;

                        if (diff <= 0) {
                            clearBonus = MAX_BONUS;
                        }
                        else {
                            clearBonus = (int)(MAX_BONUS - diff * 20);
                            if (clearBonus < 0) clearBonus = 0;
                        }
                        score += clearBonus;
                        updateHighScore();
                        state = STATE_CLEAR;
                        return;
                    }
                    updateHighScore();
                    currentPhase++;
                    phaseChanging = true;
                    invaderManager.preparePhase(currentPhase);
                    state = STATE_PHASE_START;
                    phaseStartTimer = 180;
                    return;
                }
                player.draw();
                invaderManager.draw();
                barrierManager.draw();


                // スコア表示
                fill(255);
                textSize(40);
                text(("TIME: " + std::to_string((int)playTime)).c_str(), 1600, 50);
                text(("SCORE: " + std::to_string(score)).c_str(), 1600, 100);
                text(("HIGHSCORE: " + std::to_string(highScore)).c_str(), 1600, 150);

                // 終了チェック
                if (gameOver) {
                    updateHighScore();
                    state = STATE_GAMEOVER;
                }
                else if (gameClear) {
                    updateHighScore();
                    state = STATE_CLEAR;
                }
                break;

        case STATE_GAMEOVER:
            stopSound(bgm);
            bgmPlaying = false;

            clear(0, 0, 64);
            drawBackground(backImg);

            fill(255, 0, 0);
            textSize(200);
            text("GAME OVER", 480, 540);

            textSize(60);
            fill(255);
            text("Press ENTER to Title", 500, 800);

            if (isTrigger(KEY_ENTER)) {
                resetGame();
                state = STATE_TITLE;
            }
            break;

        case STATE_CLEAR:
            stopSound(bgm);
            bgmPlaying = false;
            if (!saved) {
                scoreHistory.push_back(score);
                std::sort(scoreHistory.begin(), scoreHistory.end(), std::greater<int>());

                if (scoreHistory.size() > 10) {
                    scoreHistory.resize(10);   
                }

                saveRanking();   
                saved = true;
            }
            clear(0, 0, 64);
            drawBackground(backImg);

            textSize(50);
            fill(255);
            text(("TIME : " + std::to_string(playTime) + " sec").c_str(), 650, 700);
            text(("BONUS : " + std::to_string(clearBonus)).c_str(), 650, 760);
            text(("TOTAL SCORE : " + std::to_string(score)).c_str(), 650, 820);

            fill(0, 255, 0);
            textSize(200);
            text("GAME CLEAR!", 540, 540);

            textSize(60);
            fill(255);
            text("Press ENTER to Title", 500, 900);

            if (isTrigger(KEY_ENTER)) {
                state = STATE_TITLE;
            }
            break;
        case STATE_PHASE_START:
            clear(0, 0, 64);
            drawBackground(backImg);

            player.draw();
            invaderManager.draw();
            barrierManager.draw();


            fill(255, 255, 0);
            textSize(150);
            std::string phaseMsg = "PHASE " + std::to_string(currentPhase) + " START!!";
            float x = width / 2 - 300;
            float y = height / 2;
            text(phaseMsg.c_str(), x, y);


            if (phaseStartTimer > 0) {
                phaseStartTimer--;
            }
            else {
                phaseChanging = false;
                state = STATE_PLAY;
            }
            break;
            }
        }
    }
}