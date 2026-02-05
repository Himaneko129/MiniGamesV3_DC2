#include "../../libOne/inc/libOne.h"
//#include<rand.h>
#include<time.h>
#include"Minesweeper.h"
#include<random>
namespace GAME13 {
    void MINESWEEPER::TITLE(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer) {
        rectMode(CORNER);
        clear(0);
        fill(255);
        textSize(215);
        text("マインスイーパー", 100, 400);
        textSize(150);
        text("Start to Press SPACE", 210, 700);
        text("Enter to Press SELECT", 210, 900);
        if (isTrigger(KEY_SPACE)) {
            g_pointer->game_state = g_pointer->SELECT;
        }
        if (isTrigger(KEY_ENTER)) {
            Back_Scene = true;
        }
    }
    void MINESWEEPER::set_block_Size(struct BLOCK* b_pointer, struct NUMBER* n_pointer) {
        b_pointer->block_Size = Height / n_pointer->input_Row;
    }
    void MINESWEEPER::set_mine(struct BLOCK* b_pointer, struct NUMBER* n_pointer) {
        int judgment_mine = 0;
        srand((unsigned int)time(0));
        n_pointer->Square_input_Row = n_pointer->input_Row * n_pointer->input_Row;
        for (int x = 0; x < n_pointer->Square_input_Row; x++) {
            judgment_mine = rand() % n_pointer->input_level;
            if (judgment_mine == 0) {
                b_pointer[x].bomb_Flag = 1;
            }
        }
    }
    void MINESWEEPER::Text(struct GAME* g_pointer, struct NUMBER* n_pointer, struct SELECT_PLAYER* s_pointer) {
        textSize(100);
        fill(255);
        if (g_pointer->game_state == g_pointer->SELECT) {
            fill(125);
            rect(1150, 50, 750, 550);
            fill(255);
            text("Q:詳しく", 0, Tate);
            if (s_pointer->Quest_Flag) {
                textSize(50);
                text("?×?マス", 1200, 150);
                text("?マスに一つ地雷", 1200,250);
                text("?マスに一つ開ける", 1200, 350);
                text("Playまでカーソルを", 1200, 500);
                text("合わせてSpaceで開始", 1200, 550);
                textSize(100);
                text("Enter : TITLE", 1200, 1080);
            }
            else {
                text("  W   :  ↑", 1200, 150);
                text("A S D :←↓→", 1200, 250);
                text("   難易度", 1200, 500);
                text(" ←低：高→", 1200, 600);
                text("Enter : TITLE", 1200, 1080);
            }
        }
        textSize(100);
        fill(255);
        if (g_pointer->game_state == g_pointer->PLAY) {
            text(n_pointer->input_Row, height + 100, 100);
            text("×", height + 200, 100);
            text(n_pointer->input_Row, height + 300, 100);
            text("level;", height + 100, 200);
            text(n_pointer->input_level, height + 500, 200);
            text("  W   :  ↑", height + 100, 400);
            text("A S D :←↓→", height + 100, 500);
            text("SPACE : 決定", height + 100, 700);
            text("Press E : DASH", height + 100, 800);
            text("Press Q :　予想", height + 100, 900);
            text("Enter : TITLE", 1200, 1080);
        }
        textSize(100);
        fill(255);
        if (g_pointer->game_state == g_pointer->OVER) {
            text("GAME_OVER", height + 200, 300);
            text("Press_SPACE", height + 150, 700);
            text("Restart", height + 150, 900);
        }
        textSize(100);
        fill(255);
        if (g_pointer->game_state == g_pointer->CLEAR) {
            text("GAME_CLEAR", height + 200, 300);
            text("Press_SPACE", height + 150, 700);
            text("Restart", height + 150, 900);
        }
    }
    void MINESWEEPER::SELECT(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer, struct SELECT_PLAYER* s_pointer) {
        clear(0);
        Text(g_pointer, n_pointer,s_pointer);
        textSize(100);
        if (isTrigger(KEY_W)) { s_pointer->select_state -= 1; }
        if (isTrigger(KEY_S)) { s_pointer->select_state += 1; }
        s_pointer->select_state %= 4;
        if (s_pointer->select_state == -1) {
            s_pointer->select_state = 3;
        }
        if (isTrigger(KEY_Q)) {
            if (s_pointer->Quest_Flag == true) {
                s_pointer->Quest_Flag = false;
            }
            else {
                s_pointer->Quest_Flag = true;
            }
        }
        if (s_pointer->select_state == s_pointer->SELECT_ROW) {
            text("→Select Row", 200, 200);
            if (isTrigger(KEY_A)) { n_pointer->input_Row--; }
            if (isTrigger(KEY_D)) { n_pointer->input_Row++; }
            if (n_pointer->input_Row > 30) {
                n_pointer->input_Row %= 27;
            }
            if (n_pointer->input_Row < 4) {
                n_pointer->input_Row += 27;
            }
            s_pointer->select_level = n_pointer->input_Row;
            text(n_pointer->input_Row, 950, 200);
            fill(255);
            text("Select Level", 200, 400);
            if (n_pointer->input_level > n_pointer->input_Row / 2 + 1) {
                n_pointer->input_level -= 1;
            }
            text(n_pointer->input_level, 950, 400);
            text("Cell-Open", 200, 600);
            n_pointer->input_disclose = n_pointer->input_Row;
            if (s_pointer->Disclose_Flag) {
                text(n_pointer->input_disclose, 950, 600);
            }
            else {
                text("None", 950, 600);
            }            fill(255);
            rect((width / 2) - 300, height - 400, 600, 200);
            fill(0);
            // text("Press_SPACE", (width / 2) - 275, height - 300);
            text("Play", (width / 2) - 100, height - 250);
        }
        else if (s_pointer->select_state == s_pointer->SELECT_LEVEL) {
            fill(255);
            text("Select Row", 200, 200);
            text(n_pointer->input_Row, 950, 200);
            text("→Select Level", 200, 400);
            if (isTrigger(KEY_A)) { n_pointer->input_level++; }
            if (isTrigger(KEY_D)) { n_pointer->input_level--; }
            if (n_pointer->input_level > n_pointer->input_Row / 2 + 1) {
                n_pointer->input_level -= 1;
            }
            if (n_pointer->input_level < 2) {
                n_pointer->input_level++;
            }
            if (n_pointer->input_level == 1) {
                n_pointer->input_level++;
            }
            text(n_pointer->input_level, 950, 400);
            text("Cell-Open", 200, 600);
            if (s_pointer->Disclose_Flag) {
                text(n_pointer->input_disclose, 950, 600);
            }
            else {
                text("None", 950, 600);
            }            fill(255);
            rect((width / 2) - 300, height - 400, 600, 200);
            fill(0);
            //text("Press_SPACE", (width / 2) - 275, height - 300);
            text("Play", (width / 2) - 100, height - 250);
            s_pointer->select_level = n_pointer->input_level;
        }
        else if (s_pointer->select_state == s_pointer->SELECT_DISCLOSE) {
            fill(255);
            text("Select Row", 200, 200);
            text(n_pointer->input_Row, 950, 200);
            text("Select Level", 200, 400);
            text(n_pointer->input_level, 950, 400);
            text("→Cell-Open", 200, 600);
            if (isTrigger(KEY_D)) { n_pointer->input_disclose++; }
            if (isTrigger(KEY_A)) { n_pointer->input_disclose--; }
            if (n_pointer->input_disclose > n_pointer->input_Row + 1) {
                n_pointer->input_disclose=2;
            }
            if (n_pointer->input_disclose <= 1) {
                n_pointer->input_disclose = n_pointer->input_Row+1;
            }
            if (n_pointer->input_disclose < n_pointer->input_Row+1) {
                s_pointer->Disclose_Flag = true;
            }
            else {
                s_pointer->Disclose_Flag = false;
            }
            if (s_pointer->Disclose_Flag) {
                text(n_pointer->input_disclose, 950, 600);
            }
            else {
                text("None", 950, 600);
            }
            n_pointer->Start_Not_Mine = n_pointer->input_disclose;
            fill(255);
            rect((width / 2) - 300, height - 400, 600, 200);
            fill(0);
            //text("Press_SPACE", (width / 2) - 275, height - 300);
            text("Play", (width / 2) - 100, height - 250);
            s_pointer->select_level = n_pointer->input_level;
        }
        else if (s_pointer->select_state == s_pointer->GO_PLAY) {
            fill(255);
            text("Select Row", 200, 200);
            text(n_pointer->input_Row, 950, 200);
            fill(255);
            text("Select Level", 200, 400);
            text(n_pointer->input_level, 950, 400);
            fill(255);
            text("Cell-Open", 200, 600);
            if (s_pointer->Disclose_Flag) {
                text(n_pointer->input_disclose, 950, 600);
            }
            else {
                text("None", 950, 600);
            }            rect((width / 2) - 300, height - 400, 600, 200);
            fill(0);
            text("Press_SPACE", (width / 2) - 275, height - 300);
            text("Play", (width / 2) - 100, height - 200);
        }
        if (s_pointer->select_state == s_pointer->GO_PLAY && isTrigger(KEY_SPACE)) {
            INIT_stage(b_pointer, n_pointer, p_pointer, s_pointer);
            set_block_Size(b_pointer, n_pointer);
            set_mine(b_pointer, n_pointer);
            if (s_pointer->Disclose_Flag) {
                Start_Safe_Block(b_pointer, n_pointer, p_pointer);
            }
            p_pointer->position = 0;
            g_pointer->game_state = g_pointer->PLAY;
        }
    }
    void MINESWEEPER::stage_draw(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer) {
        int i = 0;
        textSize(b_pointer->block_Size);

        for (int y = 0; y < n_pointer->input_Row; y++) {
                fill(123, 255, 123);
                strokeWeight(1);
                line(0, b_pointer->block_Size * y, n_pointer->input_Row * b_pointer->block_Size, n_pointer->input_Row * b_pointer->block_Size);
            for (int x = 0; x < n_pointer->input_Row; x++) {
                fill(0, 255, 0);
                rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
                if (b_pointer[i].bomb_Flag == 0) {
                    fill(0, 255, 0);
                    rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
                }
                else if (b_pointer[i].bomb_Flag == 2) {
                    fill(123, 123, 123);
                    rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
                    fill(255, 255, 255);
                    textSize(b_pointer->block_Size);
                    text(b_pointer[i].memory_mine, (b_pointer->block_Size * x) + (b_pointer->block_Size / 4), b_pointer->block_Size * (y + 1));
                }
                if (b_pointer[i].player_flag == 1) {
                    fill(0, 0, 0);
                    rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size / 3, b_pointer->block_Size / 3);
                }
                if (b_pointer[i].bomb_prediction == 1) {
                    fill(255, 0, 0);
                    rect((b_pointer->block_Size * x) + (b_pointer->block_Size / 3), (b_pointer->block_Size * y) + (b_pointer->block_Size / 3), b_pointer->block_Size / 3, b_pointer->block_Size / 3);
                }
                /*debug
                else if (b_pointer[i].bomb_Flag == 1) {
                    fill(255, 0, 0);
                    rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
                }
                else if (b_pointer[i].bomb_Flag == 3) {
                    fill(255, 0, 0);
                    rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
                }
                */
                i++;
            }
        }
    }
    void MINESWEEPER::clear_decision(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer) {
        int sum = 0;
        for (int i = 0; i < n_pointer->Square_input_Row; i++) {
            if (b_pointer[i].bomb_Flag == 0) {
                sum++;
            }
        }
        if (sum == 0) {
            g_pointer->game_state = g_pointer->CLEAR;
        }
    }
    void MINESWEEPER::serect_block(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer) {
        if (p_pointer->start_position == 0) {
            b_pointer[p_pointer->position].player_flag = 1;
            p_pointer->start_position = 1;
        }
        if (isTrigger(KEY_W)) {
            b_pointer[p_pointer->position].player_flag = 0;
            p_pointer->position -= n_pointer->input_Row;
            if (p_pointer->position < 0) {
                p_pointer->position = n_pointer->Square_input_Row + p_pointer->position;
            }
            b_pointer[p_pointer->position].player_flag = 1;
        }
        if (isTrigger(KEY_A)) {
            b_pointer[p_pointer->position].player_flag = 0;
            p_pointer->position -= 1;
            if (p_pointer->position < 0) {
                p_pointer->position = n_pointer->Square_input_Row + p_pointer->position;
            }
            b_pointer[p_pointer->position].player_flag = 1;
        }
        if (isTrigger(KEY_S)) {
            b_pointer[p_pointer->position].player_flag = 0;
            p_pointer->position += n_pointer->input_Row;
            if (p_pointer->position >= n_pointer->Square_input_Row) {
                p_pointer->position = p_pointer->position % n_pointer->Square_input_Row;
            }
            b_pointer[p_pointer->position].player_flag = 1;
        }
        if (isTrigger(KEY_D)) {
            b_pointer[p_pointer->position].player_flag = 0;
            p_pointer->position += 1;
            if (p_pointer->position >= n_pointer->Square_input_Row) {
                p_pointer->position = p_pointer->position % n_pointer->Square_input_Row;
            }
            b_pointer[p_pointer->position].player_flag = 1;
        }
        if (isPress(KEY_E)) {
            if (isPress(KEY_W)) {
                b_pointer[p_pointer->position].player_flag = 0;
                p_pointer->position -= n_pointer->input_Row;
                if (p_pointer->position < 0) {
                    p_pointer->position = n_pointer->Square_input_Row + p_pointer->position;
                }
                b_pointer[p_pointer->position].player_flag = 1;
            }
            if (isPress(KEY_A)) {
                b_pointer[p_pointer->position].player_flag = 0;
                p_pointer->position -= 1;
                if (p_pointer->position < 0) {
                    p_pointer->position = n_pointer->Square_input_Row + p_pointer->position;
                }
                b_pointer[p_pointer->position].player_flag = 1;
            }
            if (isPress(KEY_S)) {
                b_pointer[p_pointer->position].player_flag = 0;
                p_pointer->position += n_pointer->input_Row;
                if (p_pointer->position >= n_pointer->Square_input_Row) {
                    p_pointer->position = p_pointer->position % n_pointer->Square_input_Row;
                }
                b_pointer[p_pointer->position].player_flag = 1;
            }
            if (isPress(KEY_D)) {
                b_pointer[p_pointer->position].player_flag = 0;
                p_pointer->position += 1;
                if (p_pointer->position >= n_pointer->Square_input_Row) {
                    p_pointer->position = p_pointer->position % n_pointer->Square_input_Row;
                }
                b_pointer[p_pointer->position].player_flag = 1;
            }

        }
    }
    void MINESWEEPER::Search_mine(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer) {
        b_pointer[p_pointer->position].memory_mine = 0;
        if (p_pointer->position == 0) {
            if (b_pointer[p_pointer->position + 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[p_pointer->position + n_pointer->input_Row].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[(p_pointer->position + n_pointer->input_Row) + 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
        }
        else if (p_pointer->position == n_pointer->input_Row - 1) {
            if (b_pointer[p_pointer->position - 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[p_pointer->position + n_pointer->input_Row].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[(p_pointer->position + n_pointer->input_Row) - 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
        }

        else if (p_pointer->position < n_pointer->input_Row) {
            if (b_pointer[p_pointer->position - 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[p_pointer->position + 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[p_pointer->position + n_pointer->input_Row].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[(p_pointer->position + n_pointer->input_Row) + 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[(p_pointer->position + n_pointer->input_Row) - 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
        }
        else if ((p_pointer->position % n_pointer->input_Row) == 0) {
            if (b_pointer[p_pointer->position + 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[p_pointer->position + n_pointer->input_Row].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[p_pointer->position - n_pointer->input_Row].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[(p_pointer->position + n_pointer->input_Row) + 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[(p_pointer->position - n_pointer->input_Row) + 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
        }
        else if (((p_pointer->position + 1) % n_pointer->input_Row) == 0) {
            if (b_pointer[p_pointer->position - 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[p_pointer->position + n_pointer->input_Row].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[p_pointer->position - n_pointer->input_Row].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[(p_pointer->position - n_pointer->input_Row) - 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[(p_pointer->position + n_pointer->input_Row) - 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
        }
        else {
            if (b_pointer[p_pointer->position + 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[p_pointer->position - 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[p_pointer->position + n_pointer->input_Row].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[p_pointer->position - n_pointer->input_Row].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[(p_pointer->position + n_pointer->input_Row) + 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[(p_pointer->position + n_pointer->input_Row) - 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[(p_pointer->position - n_pointer->input_Row) + 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
            if (b_pointer[(p_pointer->position - n_pointer->input_Row) - 1].bomb_Flag == 1) {
                b_pointer[p_pointer->position].memory_mine++;
            }
        }
    }
    void MINESWEEPER::Start_Safe_Block(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer) {
        /*
        if (n_pointer->input_Row >= 25) {
            n_pointer->Start_Not_Mine = 14;
        }
        else if (n_pointer->input_Row >= 20) {
            n_pointer->Start_Not_Mine = 11;
        }
        else if (n_pointer->input_Row >= 10) {
            n_pointer->Start_Not_Mine = 8;
        }
        else if (n_pointer->input_Row >= 10) {
            n_pointer->Start_Not_Mine = 8;
        }
        else {
            n_pointer->Start_Not_Mine = 5;
        }
        */
        int Num = 0;
        std::random_device random;
        std::mt19937 mt(random());
        std::uniform_int_distribution<int> rand(0, n_pointer->Start_Not_Mine);
        do {
            for (int i = 0; i < n_pointer->Square_input_Row; i++) {
                if (rand(mt) == 0) {
                        p_pointer->position = i;
                    if (b_pointer[p_pointer->position].bomb_Flag == 0) {
                        b_pointer[p_pointer->position].bomb_Flag = 2;
                        Search_mine(b_pointer, n_pointer, p_pointer);
                        Num++;
                    }
                }
            }
        } while (Num <= n_pointer->Start_Not_Mine);
    }

    void MINESWEEPER::Push_Block(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer) {
        if (isTrigger(KEY_SPACE)) {
            if (b_pointer[p_pointer->position].bomb_Flag == 0) {
                b_pointer[p_pointer->position].bomb_Flag = 2;
                Search_mine(b_pointer, n_pointer, p_pointer);
            }
            if (b_pointer[p_pointer->position].bomb_Flag == 1) {
                g_pointer->game_state = g_pointer->OVER;
            }
        }
        if (isTrigger(KEY_Q)) {
            if (b_pointer[p_pointer->position].bomb_prediction == 0) {
                b_pointer[p_pointer->position].bomb_prediction = 1;
            }
            else {
                b_pointer[p_pointer->position].bomb_prediction = 0;
            }
        }
    }
    void MINESWEEPER::PLAY(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer, struct SELECT_PLAYER* s_pointer) {
        serect_block(b_pointer, n_pointer, p_pointer);
        Push_Block(g_pointer, b_pointer, n_pointer, p_pointer);
        clear_decision(g_pointer, b_pointer, n_pointer, p_pointer);
        clear(0);
        stage_draw(b_pointer, n_pointer, p_pointer);
        Text(g_pointer, n_pointer,s_pointer);
        Debug_text(g_pointer, b_pointer, n_pointer, p_pointer);
    }
    void MINESWEEPER::Game_finish_stage_draw(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer) {
        int i = 0;
        for (int y = 0; y < n_pointer->input_Row; y++) {
            for (int x = 0; x < n_pointer->input_Row; x++) {
                if (b_pointer[i].bomb_Flag == 0) {
                    fill(0, 255, 0);
                    rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
                }
                else if (b_pointer[i].bomb_Flag == 1) {
                    fill(255, 0, 0);
                    rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
                }
                else if (b_pointer[i].bomb_Flag == 2) {
                    fill(123, 123, 123);
                    rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
                    fill(255, 255, 255);
                    textSize(b_pointer->block_Size);
                    text(b_pointer[i].memory_mine, (b_pointer->block_Size * x) + (b_pointer->block_Size / 4), b_pointer->block_Size * (y + 1));
                }
                i++;
            }
        }
    }
    void MINESWEEPER::INIT_stage(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer, struct SELECT_PLAYER* s_pointer) {
        for (int i = 0; i < n_pointer->Square_input_Row; i++) {
            b_pointer[i].bomb_Flag = 0;
        }
        for (int i = 0; i < n_pointer->Square_input_Row; i++) {
            b_pointer[i].bomb_prediction = 0;
        }
        b_pointer[p_pointer->position].player_flag = 0;
        p_pointer->start_position = 0;
        p_pointer->position = 0;
        s_pointer->select_state = s_pointer->SELECT_ROW;
    }
    void MINESWEEPER::OVER(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer, struct SELECT_PLAYER* s_pointer) {
        clear(0);
        Text(g_pointer, n_pointer,s_pointer);
        Game_finish_stage_draw(b_pointer, n_pointer, p_pointer);
        if (isTrigger(KEY_SPACE)) {
            INIT_stage(b_pointer, n_pointer, p_pointer, s_pointer);
            g_pointer->game_state = g_pointer->SELECT;
        }
    }
    void MINESWEEPER::CLEAR(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer, struct SELECT_PLAYER* s_pointer) {
        clear(0);
        Text(g_pointer, n_pointer,s_pointer);
        Game_finish_stage_draw(b_pointer, n_pointer, p_pointer);
        if (isTrigger(KEY_SPACE)) {
            INIT_stage(b_pointer, n_pointer, p_pointer, s_pointer);
            g_pointer->game_state = g_pointer->SELECT;
        }
    }
    void MINESWEEPER::Back_SCENE(struct GAME* g_pointer) {
        if (g_pointer->game_state == g_pointer->BACK) {
            Back_Scene = true;
        }
    }
    bool MINESWEEPER::Sent_Back_Scene() {
        return Back_Scene;
    }
    void MINESWEEPER::Debug_text(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer) {
        textSize(50);
       // text(n_pointer->Start_Not_Mine, height + 100, 950);

    }
    void MINESWEEPER::Game_console() {
        Back_Scene = false;
        if (game.game_state == game.TITLE) { TITLE(&game, block, &number); }
        else if (game.game_state == game.SELECT) {
            SELECT(&game, block, &number, &player, &select);
            if (isTrigger(KEY_ENTER)) {
                game.game_state = game.TITLE;
            }
        }
        else if (game.game_state == game.PLAY) {
            PLAY(&game, block, &number, &player,&select);
            if (isTrigger(KEY_ENTER)) {
                game.game_state = game.TITLE;
            }
        }
        else if (game.game_state == game.OVER) { OVER(&game, block, &number, &player, &select); }
        else if (game.game_state == game.CLEAR) { CLEAR(&game, block, &number, &player, &select); }
    }
}