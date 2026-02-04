#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include <math.h>
#include "GAME04.h"
#include <sstream> 
#include <cstdlib>  
#include <ctime>   
#include <cmath>
#include <string>
namespace GAME04
{
  
   
    const float CLEAR_X = 3000;
    float scrollX = 0;
    int endStateTimer = 0;       // ゲーム終了状態表示用のタイマー
    enum GameState {
        TITLE,
        PLAY,
        GAME_OVER,
        GAME_CLEAR
    };
    GameState state = TITLE;


    float distance(float x1, float y1, float x2, float y2)
    {
        float dx = x2 - x1;
        float dy = y2 - y1;
        return sqrtf(dx * dx + dy * dy);
    }
    int GAME::create()
    {
        score = 0;
        player = new PLAYER();

        enemies.clear();
        enemies.push_back(new ENEMY(800));
        enemies.push_back(new ENEMY(1200));
        enemies.push_back(new ENEMY(1600));
        enemies.push_back(new ENEMY(2000));
        enemies.push_back(new ENEMY(2400));
        enemies.push_back(new ENEMY(1600, FLY));
        enemies.push_back(new ENEMY(1700, FLY));
        enemies.push_back(new ENEMY(2100, FLY));
        enemies.push_back(new ENEMY(600, FLY));
        /*enemies.push_back(new ENEMY(1800, RANDOM));
        enemies.back()->wy = 500;

        enemies.push_back(new ENEMY(2400, RANDOM));
        enemies.back()->wy = 350;
        enemies.back()->wy = 400;*/

        steps.clear();

        // 地面より少し高い段差
        steps.push_back(new STEP(600, 750, 100, 30));
        steps.push_back(new STEP(800, 700, 100, 30));
        steps.push_back(new STEP(1000, 650, 100, 30));
        steps.push_back(new STEP(1200, 750, 100, 30));
        return 0;
    }

    
    void GAME::destroy()
    {
        delete player;
        player = nullptr;

        for (auto e : enemies) delete e;
        enemies.clear();
    }

    void GAME::move()
    {
        //  プレイヤー
        player->move();
      

        //  敵の移動
        for (auto e : enemies)
        {
            e->move(player->wx, player->wy);

        }
      

        //  プレイヤー vs 敵 当たり判定
        for (auto e : enemies)
        {
            if (!e->active) continue;

            float d = distance(
                player->wx, player->wy,
                e->wx, e->wy
            );

            if (d < player->pr + e->pr)
            {
                float playerFootY = player->wy + player->pr;
                float enemyHeadY = e->wy - e->pr;

                // 踏みつけ
                if (player->vy > 0 && playerFootY < enemyHeadY + 10)
                {
                    e->active = false;
                    player->vy = -15;
                    player->score += 2000;
                }
                else
                {
                    if (player->wx < e->wx)
                        player->wx = e->wx - (player->pr + e->pr);
                    else
                        player->wx = e->wx + (player->pr + e->pr);

                    player->vx = (player->wx < e->wx) ? -10 : 10;
                    player->vy = -8;
                    player->knockTimer = 15;

                    player->hp--;
                    player->score -= 1000;
                    player->invincibleTimer = 60;
                }
            }
        }
        for (auto s : steps)
        {
            // プレイヤーの足元（前フレーム）
            float footY = player->wy + player->pr;
            float prevFootY = footY - player->vy;

            // 横判定
            bool hitX =
                player->wx + player->pr > s->x &&
                player->wx - player->pr < s->x + s->w;

            // 上からだけ乗れる
            if (hitX &&
                prevFootY <= s->y &&
                footY >= s->y &&
                player->vy > 0)
            {
                player->wy = s->y - player->pr;
                player->vy = 0;
                player->onGround = true;
            }
        }

        //  ゲームオーバー判定
        if (player->hp <= 0 && state != GAME_OVER)
        {
            state = GAME_OVER;
            endStateTimer = 0;
        }

        //  クリア判定
        if (scrollX >= 3000 && state == PLAY)
        {
            state = GAME_CLEAR;
            endStateTimer = 0;
        }
        if (player->wx >= CLEAR_X - 10 && player->wx <= CLEAR_X + 10)
        {
            state = GAME_CLEAR;
            endStateTimer = 0;
        }
      
      
      
    }
    void GAME::drawClearBackground()
    {

        float x = CLEAR_X - scrollX;

        // 画面外なら描かない（軽量化）
        if (x < -200 || x > 1280) return;

        // ゴールの背景（建物・門っぽく）
        rect(x - 100, 600, 200, 300);   // 柱
        rect(x - 150, 550, 300, 50);    // 上部

        // 地面の強調
        rect(x - 200, 830, 400, 250);
        static int t = 0;
        t++;

        if ((t / 20) % 2 == 0)
        {
            rect(x - 120, 520, 240, 20);
        }
    }
    void GAME::drawClearLight()
    {
        static int t = 0;
        t++;

        float x = CLEAR_X - scrollX;

        // 画面外なら描かない
        if (x < -100 || x > 1380) return;

        // 点滅サイズ
        float r = 30 + 10 * sin(t * 0.1f);

        // 光（重ね描きで強調）
        circle(x, 780, r);
        circle(x, 780, r * 0.7f);
        circle(x, 780, r * 0.4f);
    }
   
    void GAME::draw() {
        player->draw();
        for (auto e : enemies) e->draw();
        drawClearBackground();
        drawClearLight();
        for (auto s : steps) s->draw();
        std::stringstream ss;
        ss << "Player HP: " << player->hp;
        text(ss.str().c_str(), 50, 50);
        ss.str("");
        std::stringstream pp;
        pp << "SCORE: " << player->score;
        text(pp.str().c_str(), 50, 200);
        pp.str("");
       
    }
    void GAME::drawTitle()
    {
        static int timer = 0;
        timer++;

        // タイトル背景
        textSize(80);
        text("横スクロール",600, 250);

        // PRESS SPACE 表示（点滅）
        if ((timer / 30) % 2 == 0)
        {
           text(" PRESS SPACE",680, 380);
        }

        // スペースで開始
        if (isTrigger(KEY_SPACE))
        {
            state = PLAY;
            scrollX = 0;
            timer = 0;
           
            create();
        }
       
    }


    void GAME::proc()
    {
        clear(0, 0, 100);
        fill(255);
        // ===== 背景（共通）=====
        	textSize(50);
			
			
        switch (state)
        {
        case TITLE:
            drawTitle();
            text("ENTERでメニューに戻る", 600, 700);
            if (isTrigger(KEY_ENTER)) {
                state = TITLE;
                destroy();
                main()->backToMenu();
            }
            break;

        case PLAY:
        rect(-fmod(scrollX, 800), 830, 800, 250);
        rect(800 - fmod(scrollX, 800), 830, 800, 250);
            move();
            draw();
            fill(255,0,0);
            textSize(30);
            text("W;上  A;左   D;右  Z: タイトルに戻る  ENTER; メニューに戻る", 0, 1080);
            if (isTrigger(KEY_ENTER)) {
                state = TITLE;
                destroy();
                main()->backToMenu();
            }
            if (isTrigger(KEY_Z)) {
                state = TITLE;
                destroy();

            }
            break;
        case GAME_OVER:
            textSize(80);
            fill(255);
            text("昇天した", 500, 500);
            text("SCORE:", 500, 600);
            text(player->score, 750, 600);
            textSize(40);
            fill(255);
            text("Zでタイトルへ戻る　ENTERでメニューに戻る", 500, 700);

            if (isTrigger(KEY_Z)) {
                state = TITLE;
                destroy();
            }
            if (isTrigger(KEY_ENTER)) {
                state = TITLE;
                destroy();
                main()->backToMenu();
            }
            break;

        case GAME_CLEAR:
           
           
            textSize(80);
            fill(255);
            text("GAME CLEAR!", 500, 500);
            text("SCORE:", 500, 600);
            text(player->score, 750, 600);
            textSize(40);
            fill(255);
            text("Zでタイトルへ戻る　ENTERでメニューに戻る", 500, 700);
            if (isTrigger(KEY_Z)) {
                state = TITLE;
                destroy();
            }
            if (isTrigger(KEY_ENTER)) {
                state = TITLE;
                destroy();
                main()->backToMenu();
            }
            break;
        }
    }
}
