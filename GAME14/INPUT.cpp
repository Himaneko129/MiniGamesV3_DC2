#include"INPUT.h"
#include <cstring> 
namespace GAME14 {
    void INPUT::INIT() {
        const char* hiraList[KEY_NUM] = {
         "ん","わ","ら","や","ま","は","な","た","さ","か","あ",
          "" ,"ゐ","り", "" ,"み","ひ","に","ち","し","き","い",
          "" , "" ,"る","ゆ","む","ふ","ぬ","つ","す","く","う",
          "" ,"ゑ","れ", "" ,"め","へ","ね","て","せ","け","え",
          "" ,"を","ろ","よ","も","ほ","の","と","そ","こ","お",
          "Back","Enter"
        };
        int index = 0;
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 11; col++) {
                if (index >= KEY_NUM - 2) break;
                key[index]->Hira = hiraList[index];
                key[index]->x = KEY_START_X + col * KEY::Key_Size;
                key[index]->y = KEY_START_Y + row * KEY::Key_Size;
                index++;
            }
        }
        key[KEY_NUM - 2]->Hira = hiraList[KEY_NUM - 2];
        key[KEY_NUM - 2]->x = KEY_START_X + 11 * KEY::Key_Size;
        key[KEY_NUM - 2]->y = KEY_START_Y;// + 6 * KEY::Key_Size;
        key[KEY_NUM - 1]->Hira = hiraList[KEY_NUM - 1];
        key[KEY_NUM - 1]->x = KEY_START_X + 11 * KEY::Key_Size;
        key[KEY_NUM - 1]->y = KEY_START_Y + 1 * KEY::Key_Size;
        //inputText = '_';
        for (int i = 0; i < 5; i++) {
            select_key[i]->x = KEY_START_X + i * SELECT_KEY::Key_Size_X;
            select_key[i]->y = KEY_START_Y;
                //+ i * SELECT_KEY::Key_Size_Y;
        }

    }
    void INPUT::DRAWRECT(int mouseX, int mouseY) {
        for (int i = 0; i < KEY_NUM; i++) {
            // 仮の描画処理
            rectMode(CORNER);
            if (strcmp(key[i]->Hira, "") == 0) {
                continue;
            }
            /*
            bool over = (mouseX >= key[i]->x && mouseX <= key[i]->x + KEY::Key_Size &&
                mouseY >= key[i]->y && mouseY <= key[i]->y - KEY::Key_Size);
            key[i]->overlap = over;
            */
            // 色の決定
            if (key[i]->press)
                fill(255, 255, 50); // 押されたキー → オレンジ
            else
                fill(255);
            if (i == KEY_NUM - 2 || i == KEY_NUM - 1) {
                rect(key[i]->x, key[i]->y - KEY::Key_Size, KEY::Key_Size * 2, KEY::Key_Size);
            }
            else {
                rect(key[i]->x, key[i]->y - KEY::Key_Size, KEY::Key_Size, KEY::Key_Size);
            }
        }
    }
    void INPUT::DRAWTEXT() {
        for (int i = 0; i < KEY_NUM; i++) {
            if (strcmp(key[i]->Hira, "") == 0) {
                continue;
            }
            fill(0);
            textSize(32);
            // text(key[i]->Hira, key[i]->x+20, key[i]->y+20);
            text(key[i]->Hira, key[i]->x + KEY::Key_Size / 3, key[i]->y - KEY::Key_Size / 3);
        }
    }
    void INPUT::KEYBOARD(int mouseX, int mouseY) {
        DRAWRECT(mouseX, mouseY);
        DRAWTEXT();
    }
    void INPUT::MOUSE_INPUT(int mouseX, int mouseY) {
        for (int i = 0; i < KEY_NUM; i++) {
            key[i]->press = false; // 全てリセット
        }
        for (int i = 0; i < KEY_NUM; i++) {
            // 空欄キーはスキップ
            if (strcmp(key[i]->Hira, "") == 0)
                continue;

            int x = key[i]->x;
            int y = key[i]->y - KEY::Key_Size; // rect()に合わせる
            sent_text.clear();
            // マウスがこのキーの範囲に入っているか判定
            if (i == KEY_NUM - 1 || i == KEY_NUM - 2) {
                if (mouseX >= x && mouseX <= x + KEY::Key_Size * 2 && mouseY >= y && mouseY <= y + KEY::Key_Size) {
                    key[i]->press = true;
                    // 押されたキーの文字を追加
                    if (isTrigger(MOUSE_LBUTTON)) {
                        if (strcmp(key[i]->Hira, "Back") == 0) {
                            //  Backspace機能
                            if (!inputText.empty()) {
                                inputText.pop_back();
                                if (!inputText.empty()) {
                                    inputText.pop_back();
                                }
                            }
                        }
                        else if (strcmp(key[i]->Hira, "Enter") == 0) {
                            sent_text = sent_text = inputText;
                            inputText.clear();
                        }
                        else {
                            inputText += key[i]->Hira;
                        }
                    }
                    break; // 1キーだけ判定
                }
            }
            else {
                if (mouseX >= x && mouseX <= x + KEY::Key_Size && mouseY >= y && mouseY <= y + KEY::Key_Size) {
                    key[i]->press = true;
                    // 押されたキーの文字を追加
                    if (isTrigger(MOUSE_LBUTTON)) {
                        if (strcmp(key[i]->Hira, "Back") == 0) {
                            //  Backspace機能
                            if (!inputText.empty()) {
                                inputText.pop_back();
                                if (!inputText.empty()) {
                                    inputText.pop_back();
                                }
                            }
                        }
                        else if (strcmp(key[i]->Hira, "Enter") == 0) {
                            // Enter機能（改行を追加）
                            //inputText += '\n';
                            sent_text = inputText;
                            inputText.clear();
                        }
                        else {
                            inputText += key[i]->Hira;
                        }
                    }
                    break; // 1キーだけ判定
                }
            }
        }
    }
    const char* INPUT:: Sent_text() {
        return sent_text.c_str();
    }
    void INPUT::SHOW_INPUT() {
        fill(255);
        textSize(100);
        text(inputText.c_str(), KEY_START_X, KEY_START_Y-60);
       // text(sent_text.c_str(), KEY_START_X, (Tate / 2)+100);//デバック.
    }
    void INPUT::DRAW_SELECT(int mouseX, int mouseY) {
        for (int i = 0; i < SELECT_KEY_NUM; i++) {
            // 仮の描画処理
            rectMode(CORNER);
            /*
            bool over = (mouseX >= key[i]->x && mouseX <= key[i]->x + KEY::Key_Size &&
                mouseY >= key[i]->y && mouseY <= key[i]->y - KEY::Key_Size);
            key[i]->overlap = over;
            */
            // 色の決定
            if (select_key[i]->press)
                fill(255, 255, 50); // 押されたキー → オレンジ
            else
                fill(255);

            rect(select_key[i]->x-SELECT_KEY::Key_Size_X, select_key[i]->y - SELECT_KEY::Key_Size_Y, SELECT_KEY::Key_Size_X, SELECT_KEY::Key_Size_Y);
          
            fill(0);
            textSize(100);
            text("段  段  段  段  段", 450, 540);
            text("階  階  階  階  階", 450, 640);
            text("１  ２  ３  ４  ５", 450, 740);
            textSize(200);
            text("あ＋あ＝い", 450, 340);
        }
    }
    int INPUT::SELECT_MOUSE_INPUT(int mouseX, int mouseY) {
        int result = -1;
        for (int i = 0; i < SELECT_KEY_NUM; i++) {
            select_key[i]->press = false; // 全てリセット
        }
        for (int i = 0; i < SELECT_KEY_NUM; i++) {

            int x = select_key[i]->x;
            int y = select_key[i]->y - SELECT_KEY::Key_Size_Y; // rect()に合わせる

            // マウスがこのキーの範囲に入っているか判定

            if (mouseX >= x - SELECT_KEY::Key_Size_X && mouseX <= x  && mouseY >= y && mouseY <= y + SELECT_KEY::Key_Size_Y) {
                select_key[i]->press = true;
                // 押されたキーの文字を追加
                if (isTrigger(MOUSE_LBUTTON)) {
                    result = i;
                }
                break; // 1キーだけ判定
            }
        }
        return result;
    }
    bool INPUT::BACK_SCENE(int mouseX,int mouseY) {
        fill(255);
        textSize(100);
        if ((0 < mouseX && mouseX < 300 )&&( 0 < mouseY && mouseY < 100)) {
            fill(255, 255, 0);
            if (isTrigger(MOUSE_LBUTTON)) {
                inputText.clear();
            return true;
            }
        }
        text("<-BACK", 0, 100);
    }
}