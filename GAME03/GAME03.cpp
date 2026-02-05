#define NOMINMAX
#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME03.h"
#include <algorithm>
#include <random>
#include <queue>
#include <cstdio> 
#include "MiniTemplate.h"

namespace GAME03 {

    const int placeOrder[9] = {
    0,1,2,
    5,4,3,
    6,7,8
    };
    GAME::GAME(MAIN* main) : GAME_BASE(main) {

    }


    int GAME::create()
    {
        // 難易度選択（0=EASY）
        selectedDifficulty = 0;

        // 旧ブロック数制御は使わない
        // numBlocks = 0; ← 削除！

        gameClear = false;
        playInitFlg = false;

        // 最初は必ずタイトル
        State = TITLE;

        return 0;
    }


    int GAME::countEmptyCells() const
    {
        int count = 0;
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                if (board[y][x] == EMPTY)
                    count++;
            }
        }
        return count;
    }

    void GAME::clearMap()
    {
        for (int y = 0; y < 9; ++y)
            for (int x = 0; x < 9; ++x)
                board[y][x] = EMPTY;
    }
    void GAME::resetVisited()
    {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                visited[y][x] = false;
            }
        }
    }
    int countDegree(const MiniTemplate& t, int x, int y)
    {
        int d = 0;
        const int dx[4] = { 1, -1, 0, 0 };
        const int dy[4] = { 0, 0, 1, -1 };

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3) continue;
            if (t.cell[ny][nx] == 0) d++;
        }
        return d;
    }
    // 接続点を固定（超重要：ここを固定すると安定する）

    // 3x3で「指定 start→end で EMPTY 全踏破」する mainPath を探す
    static bool dfsSolve3x3(
        const MiniTemplate& src,
        int x, int y,
        int ex, int ey,
        int emptyCount,
        bool used[3][3],
        std::vector<std::pair<int, int>>& path,
        int depth
    ) {
        used[y][x] = true;
        path.push_back({ x,y });

        if (depth == emptyCount) {
            if (x == ex && y == ey) return true;
            path.pop_back();
            used[y][x] = false;
            return false;
        }

        const int dx[4] = { 1,-1,0,0 };
        const int dy[4] = { 0,0,1,-1 };

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3) continue;
            if (used[ny][nx]) continue;
            if (src.cell[ny][nx] != 0) continue;

            if (dfsSolve3x3(src, nx, ny, ex, ey, emptyCount, used, path, depth + 1))
                return true;
        }

        path.pop_back();
        used[y][x] = false;
        return false;
    }

    static bool SolvePath3x3(
        const MiniTemplate& src,
        int sx, int sy,
        int ex, int ey,
        std::vector<std::pair<int, int>>& outPath
    ) {
        int emptyCount = 0;
        for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
                if (src.cell[y][x] == 0) emptyCount++;

        if (emptyCount == 0) return false;
        if (sx < 0 || sx >= 3 || sy < 0 || sy >= 3) return false;
        if (ex < 0 || ex >= 3 || ey < 0 || ey >= 3) return false;
        if (src.cell[sy][sx] != 0) return false;
        if (src.cell[ey][ex] != 0) return false;

        bool used[3][3] = {};
        std::vector<std::pair<int, int>> path;
        path.reserve(emptyCount);

        if (!dfsSolve3x3(src, sx, sy, ex, ey, emptyCount, used, path, 1))
            return false;

        outPath = std::move(path);
        return true;
    }

    static int countEmptyMini(const MiniTemplate& t)
    {
        int c = 0;
        for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
                if (t.cell[y][x] == 0) c++;
        return c;
    }

    static std::pair<int, int> Port(DIR d) {
        if (d == RIGHT) return { 2, 1 };
        if (d == LEFT)  return { 0, 1 };
        if (d == DOWN)  return { 1, 2 };
        if (d == UP)    return { 1, 0 };
        return { 1, 1 };
    }

    static DIR Opp(DIR d) {
        if (d == RIGHT) return LEFT;
        if (d == LEFT)  return RIGHT;
        if (d == DOWN)  return UP;
        if (d == UP)    return DOWN;
        return NONE;
    }

    static void finalizeTemplate(MiniTemplate& t)
    {
        if (t.mainPath.empty()) return;
        t.startX = t.mainPath.front().first;
        t.startY = t.mainPath.front().second;
        t.goalX = t.mainPath.back().first;
        t.goalY = t.mainPath.back().second;
        buildArrowFromPath(t);
    }

    int GAME::getTargetBlocks() const
    {
        switch (selectedDifficulty) {
        case EASY:   return 16;
        case NORMAL: return 16;
        case HARD:   return 16;
        }
        return 7;
    }

    int GAME::countBlocks9x9() const
    {
        int c = 0;
        for (int y = 0; y < SIZE; ++y)
            for (int x = 0; x < SIZE; ++x)
                if (board[y][x] == BLOCK) c++;
        return c;
    }

    // ---- 端点で接続判定（前のgoal と 次のstart が隣接）----
    static bool canConnectByEndpoints(const MiniTemplate& from, const MiniTemplate& to, DIR dir)
    {
        if (dir == RIGHT) return (from.goalX == 2 && to.startX == 0 && from.goalY == to.startY);
        if (dir == LEFT)  return (from.goalX == 0 && to.startX == 2 && from.goalY == to.startY);
        if (dir == DOWN)  return (from.goalY == 2 && to.startY == 0 && from.goalX == to.startX);
        if (dir == UP)    return (from.goalY == 0 && to.startY == 2 && from.goalX == to.startX);
        return false;
    }
    void GAME::generateMap()
    {
        const int targetBlocks = getTargetBlocks();
        const int order[9] = { 0,1,2, 5,4,3, 6,7,8 };

        auto nextDirOf = [&](int k)->DIR {
            if (k == 8) return NONE; // 最後は出口なし
            int a = order[k];
            int b = order[k + 1];
            if (b == a + 1) return RIGHT;
            if (b == a - 1) return LEFT;
            if (b == a + 3) return DOWN;
            if (b == a - 3) return UP;
            return NONE;
            };
        auto prevDirOf = [&](int k)->DIR {
            if (k == 0) return NONE; // 最初は入口なし
            int a = order[k - 1];
            int b = order[k];
            if (b == a + 1) return RIGHT;
            if (b == a - 1) return LEFT;
            if (b == a + 3) return DOWN;
            if (b == a - 3) return UP;
            return NONE;
            };

        // 成功率が必要なので回数は多め
        for (int retry = 0; retry < 3000; ++retry)
        {
            clearMap();
            resetVisited();
            mainPath9x9.clear();
            moveHistory.clear();
            visitCount = 0;
            gameClear = false;

            MiniTemplate placed[9];
            bool allOK = true;

            // ===== 9枚を順に作る（各3x3で SolvePath3x3 する）=====
            for (int k = 0; k < 9 && allOK; ++k)
            {
                int idx = order[k];
                DIR inDir = prevDirOf(k); // prev -> idx の方向
                DIR outDir = nextDirOf(k); // idx -> next の方向

                // inPort / outPort を決める
                int sx, sy, ex, ey;

                if (k == 0) {
                    // 左上はスタート固定
                    sx = 0; sy = 0;
                }
                else {
                    // 入口は「prevから来る方向の反対側ポート」
                    auto p = Port(Opp(inDir));
                    sx = p.first; sy = p.second;
                }

                // 出口（最後だけ特別）
                bool needFixedExit = (k != 8);
                if (needFixedExit) {
                    auto p = Port(outDir);
                    ex = p.first; ey = p.second;
                }

                bool placedOK = false;

                for (int trial = 0; trial < 400 && !placedOK; ++trial)
                {
                    MiniTemplate base = g_miniTemplates[rand() % g_miniTemplates.size()];
                    auto vars = generateVariants(base);

                    for (auto v : vars)
                    {
                        std::vector<std::pair<int, int>> path;

                        if (needFixedExit) {
                            // 入口→出口を固定して解く
                            if (!SolvePath3x3(v, sx, sy, ex, ey, path)) continue;
                        }
                        else {
                            // 最後のブロックは「入口→どこでも」で成功する終点を探す
                            bool ok = false;
                            for (int ty = 0; ty < 3 && !ok; ++ty) {
                                for (int tx = 0; tx < 3 && !ok; ++tx) {
                                    if (v.cell[ty][tx] != 0) continue;
                                    if (SolvePath3x3(v, sx, sy, tx, ty, path)) ok = true;
                                }
                            }
                            if (!ok) continue;
                        }

                        // ここまで来たらこの向きで確定（mainPathを埋める）
                        v.mainPath = path;
                        v.startX = v.mainPath.front().first;
                        v.startY = v.mainPath.front().second;
                        v.goalX = v.mainPath.back().first;
                        v.goalY = v.mainPath.back().second;
                        buildArrowFromPath(v);

                        placed[idx] = v;
                        placedOK = true;
                        break;
                    }
                }

                if (!placedOK) allOK = false;
            }

            if (!allOK) continue;

            // ===== 9x9に貼る =====
            for (int i = 0; i < 9; i++)
            {
                int baseX = (i % 3) * 3;
                int baseY = (i / 3) * 3;

                const MiniTemplate& t = placed[i];
                for (int y = 0; y < 3; y++)
                    for (int x = 0; x < 3; x++)
                        board[baseY + y][baseX + x] = (t.cell[y][x] == 0) ? EMPTY : BLOCK;
            }

            // ★難易度：ブロック数が一致したものだけ採用
            int blocks = countBlocks9x9();
            if (blocks != targetBlocks) continue;

            // ===== mainPath9x9を結合 =====
            mainPath9x9.clear();
            mainPath9x9.reserve(81);

            for (int k = 0; k < 9; k++)
            {
                int id = order[k];
                int bx = (id % 3) * 3;
                int by = (id / 3) * 3;

                for (auto& p : placed[id].mainPath)
                    mainPath9x9.emplace_back(bx + p.first, by + p.second);
            }

            if (mainPath9x9.empty()) continue;
            if (mainPath9x9.front().first != 0 || mainPath9x9.front().second != 0) continue;

            // ===== 成功：初期化 =====
            applyMainPathToBoard();
            buildArrowFromMainPath9x9();

            totalEmpty = countEmptyCells();
            px = 0; py = 0;
            resetVisited();
            visited[py][px] = true;
            visitCount = 1;

            moveHistory.clear();

            playInitFlg = true;
            debugGenFailed = false;
            return;
        }

        // ===== 失敗フォールバック =====
        clearMap();
        resetVisited();
        debugGenFailed = true;

        for (int y = 0; y < SIZE; y++)
            for (int x = 0; x < SIZE; x++)
                board[y][x] = EMPTY;

        mainPath9x9.clear();
        mainPath9x9.push_back({ 0,0 });

        totalEmpty = countEmptyCells();
        px = 0; py = 0;
        visited[0][0] = true;
        visitCount = 1;
        startPX = 0; startPY = 0;
        playInitFlg = true;
    }

    void GAME::build9x9FromTemplates(const MiniTemplate placed[9]) {
        for (int ty = 0; ty < 3; ty++) {
            for (int tx = 0; tx < 3; tx++) {
                const MiniTemplate& t = placed[ty * 3 + tx];

                for (int y = 0; y < 3; y++) {
                    for (int x = 0; x < 3; x++) {
                        int gx = tx * 3 + x;
                        int gy = ty * 3 + y;

                        board[gy][gx] = (t.cell[y][x] == 0) ? EMPTY : BLOCK;

                    }
                }
            }
        }
    }
    void GAME::applyMainPathToBoard()
    {
        // ★盤面は step3 の貼り付け結果を残す
        // その上で、正解ルート上は必ず通路にする（保険）
        for (auto& p : mainPath9x9) {
            board[p.second][p.first] = EMPTY;
        }
    }

    DIR GAME::getTemplateDirection(int a, int b)
    {
        int ax = a % 3, ay = a / 3;
        int bx = b % 3, by = b / 3;

        if (bx == ax + 1) return DIR::RIGHT;
        if (bx == ax - 1) return DIR::LEFT;
        if (by == ay + 1) return DIR::DOWN;
        return DIR::UP;
    }
    void GAME::buildArrowFromMainPath9x9()
    {
        for (int y = 0; y < SIZE; y++)
            for (int x = 0; x < SIZE; x++)
                arrow[y][x] = NONE;

        for (int i = 0; i + 1 < (int)mainPath9x9.size(); i++)
        {
            int x1 = mainPath9x9[i].first;
            int y1 = mainPath9x9[i].second;
            int x2 = mainPath9x9[i + 1].first;
            int y2 = mainPath9x9[i + 1].second;

            if (x2 == x1 + 1)      arrow[y1][x1] = RIGHT;
            else if (x2 == x1 - 1) arrow[y1][x1] = LEFT;
            else if (y2 == y1 + 1) arrow[y1][x1] = DOWN;
            else if (y2 == y1 - 1) arrow[y1][x1] = UP;
        }
    }
    void GAME::handleInput()
    {
        static bool prevA = false, prevD = false, prevW = false, prevS = false, prevR = false;

        bool a = inValue(KEY_A);
        bool d = inValue(KEY_D);
        bool w = inValue(KEY_W);
        bool s = inValue(KEY_S);
        bool r = inValue(KEY_R);

        // =====================
        // ① 戻る処理（最優先）
        // =====================
        if (r && !prevR && !moveHistory.empty() && undoLeft > 0)
        {
            // 昔のそのまま
            if (!(px == startPX && py == startPY) && visited[py][px] && visitCount > 1) {
                visited[py][px] = false;
                visitCount--;
            }

            auto prev = moveHistory.back();
            moveHistory.pop_back();
            px = prev.first;
            py = prev.second;

            undoLeft--; 
        }
        else
        {
            // =====================
            // ② 移動処理
            // =====================
            int nx = px;
            int ny = py;

            if (a && !prevA) nx--;
            else if (d && !prevD) nx++;
            else if (w && !prevW) ny--;
            else if (s && !prevS) ny++;

            if (nx != px || ny != py)
            {
                if (nx >= 0 && nx < SIZE &&
                    ny >= 0 && ny < SIZE &&
                    board[ny][nx] != BLOCK &&
                    !visited[ny][nx])
                {
                    // ★移動前を履歴に保存（この方式を維持）
                    moveHistory.push_back({ px, py });

                    px = nx;
                    py = ny;

                    visited[py][px] = true;
                    visitCount++;
                }
            }
        }

        // 入力更新
        prevA = a;
        prevD = d;
        prevW = w;
        prevS = s;
        prevR = r;

        // ヒント表示
        if (isTrigger(KEY_F)) {
            showRoute = !showRoute;
        }

        // =====================
        // ③ CLEAR判定
        // =====================
        if (visitCount == totalEmpty) {
            gameClear = true;
            State = CLEAR;
        }
    }

    void GAME::drawBoard() {
        clear(0, 0, 0);

        const int cellSize = 40;
        const int margin = 4;
        const int boardSize = SIZE * cellSize;

        const int offsetX = (1920 - boardSize) / 2;
        const int offsetY = (1080 - boardSize) / 2 - 50;

        for (int y = 0; y < SIZE; ++y) {
            for (int x = 0; x < SIZE; ++x) {
                int cx = x * cellSize + offsetX;
                int cy = y * cellSize + offsetY;

                // --- マスの色 ---
                if (board[y][x] == BLOCK) fill(100, 100, 100);
                else if (visited[y][x])   fill(0, 200, 0);
                else                      fill(255, 255, 255);

                rect(cx, cy, cellSize - margin, cellSize - margin);

                // --- ルート矢印（ここはforの中！）---
                if (showRoute && arrow[y][x] != NONE && board[y][x] != BLOCK) {
                    fill(0, 0, 0);

                    int cxm = cx + (cellSize - margin) / 2;
                    int cym = cy + (cellSize - margin) / 2;

                    const char* s = "?";
                    if (arrow[y][x] == UP) s = "↑";
                    else if (arrow[y][x] == DOWN) s = "↓";
                    else if (arrow[y][x] == LEFT) s = "←";
                    else if (arrow[y][x] == RIGHT) s = "→";

                    textSize(20);
                    text(s, cxm - 6, cym + 6);
                }

                // --- プレイヤー ---
                if (x == px && y == py) {
                    fill(255, 0, 0);
                    circle(cx + (cellSize - margin) / 2,
                        cy + (cellSize - margin) / 2, 10);
                }
            }
        }


        // --- UI ---
        const int textY = offsetY + boardSize + 30;
        fill(255, 255, 255);
        textSize(24);
        text("移動: A/D/W/S", offsetX, textY);
        text("Z: リスタート R: 1マス戻る  B: タイトルへ  F:　クリアルート", offsetX, textY + 30);

        char buf[64];
        sprintf_s(buf, "訪問マス: %d / %d", visitCount, totalEmpty);
        fill(200, 200, 0);
        textSize(24);
        text(buf, offsetX, textY + 70);

        char u[64];
        sprintf_s(u, "戻る残り: %d", undoLeft);
        fill(200, 200, 200);
        textSize(24);
        text(u, offsetX, textY + 100);  // 既存表示と被るなら+130などに




        if (debugGenFailed) {
            fill(255, 0, 0);
            textSize(30);
            text("TEMPLATE GENERATION FAILED", 200, 200);
        }


    }
    void GAME::restartPlay() {
        // スタート位置に戻す
        px = 0;
        py = 0;

        // 訪問情報リセット
        resetVisited();
        visited[py][px] = true;


        // ★重要：移動履歴を完全に破棄

        visitCount = 1;
        gameClear = false;
        showClearRoute = false;
        moveHistory.clear();
        undoLeft = getUndoLimit();

    }


    void GAME::drawCenteredText(const char* str, int centerX, int y, int size) {
        textSize(size);
        int width = strlen(str) * 10;
        text(str, centerX - width / 2, y);
    }

    void GAME::proc() {


        bool currentEnter = inValue(KEY_SPACE);

        switch (State) {
        case TITLE: {
            clear(0, 0, 0);
            textSize(32);
            drawCenteredText("迷路ゲーム", 960, 100);
            textSize(24);
            drawCenteredText("難易度を選んでください", 960, 180);

            text("ENTERキーでメニューに戻る", 0, 1080);
            if (isTrigger(KEY_ENTER)) {
                main()->backToMenu();
            }
            const char* diff[] = { "簡単　", "普通　", "難しい" };

            static int keyWait = 0;
            if (keyWait > 0) keyWait--;
            if (keyWait == 0) {
                if (isTrigger(KEY_UP)) {
                    selectedDifficulty = (selectedDifficulty + 2) % 3;
                    keyWait = 10;
                }
                if (isTrigger(KEY_DOWN)) {
                    selectedDifficulty = (selectedDifficulty + 1) % 3;
                    keyWait = 10;
                }
            }
            for (int i = 0; i < 3; ++i) {
                if (i == selectedDifficulty) fill(255, 255, 0);
                else                         fill(200, 200, 200);

                drawCenteredText(diff[i], 960, 240 + i * 40);
            }

            // 選択矢印
            fill(255, 255, 255);
            textSize(24);
            text(">", 960 - 120, 240 + selectedDifficulty * 40);





            drawCenteredText("↑↓ : マップ選択   SPACE : 決定", 960, 460, 20);

            if (currentEnter && !prevEnterKey) {


                State = PLAY;
                playInitFlg = false;
            }
            break;
        }


        case PLAY: {
            clear(0, 0, 0);

            if (!playInitFlg) {
                generateMap();
                undoLeft = getUndoLimit();// ← ここで px/py/visited/visitCount まで完成させる
                moveHistory.clear();
                playInitFlg = true;
            }

            drawBoard();
            handleInput();

            if (isTrigger(KEY_Z)) {
                restartPlay();
            }

            if (isTrigger(KEY_B)) {
                State = TITLE;
                playInitFlg = false;
            }
            break;
        }

        case CLEAR: {
            clear(0, 0, 0);
            fill(255, 255, 0);
            drawCenteredText("CLEAR!", 960, 300, 32);

            fill(200, 200, 200);
            drawCenteredText("Rキーでタイトルへ", 960, 360, 20);

            if (isTrigger(KEY_R)) {
                State = TITLE;

                // ===== 次回プレイ用に初期化フラグを戻す =====
                playInitFlg = false;
            }
            break;
        }
        }

        prevEnterKey = currentEnter;
    }

    void GAME::destroy() {}

} // namespace GAME03