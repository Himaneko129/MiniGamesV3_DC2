#include "../../libOne/inc/libOne.h"
#include "Board.h"
#include <math.h>

namespace GAME08
{     
    // 仮想移動用
    struct Board::MoveBackup {
        Piece from;
        Piece to;

        // 特殊手用
        bool hadExtra = false;
        int ex = -1;
        int ey = -1;
        Piece extra;
    };
    
    //コンストラクタ
    Board::Board()
        : currentTurn(WHITE),
        selectedX(-1),
        selectedY(-1),
        enPassantX(0),
        enPassantY(0),
        enPassantAvailable(false),
        inCheck(false),
        inCheckmate(false),
        inStalemate(false),
        promotionPending(false),
        promotionColor(WHITE),
        promotionX(0),
        promotionY(0)
    {
        // ===== 白駒 =====
        pieceImageId[WHITE][PAWN] = loadImage("../MAIN/assets/game08/white_pawn.png");
        pieceImageId[WHITE][ROOK] = loadImage("../MAIN/assets/game08/white_rook.png");
        pieceImageId[WHITE][KNIGHT] = loadImage("../MAIN/assets/game08/white_knight.png");
        pieceImageId[WHITE][BISHOP] = loadImage("../MAIN/assets/game08/white_bishop.png");
        pieceImageId[WHITE][QUEEN] = loadImage("../MAIN/assets/game08/white_queen.png");
        pieceImageId[WHITE][KING] = loadImage("../MAIN/assets/game08/white_king.png");

        // ===== 黒駒 =====
        pieceImageId[BLACK][PAWN] = loadImage("../MAIN/assets/game08/black_pawn.png");
        pieceImageId[BLACK][ROOK] = loadImage("../MAIN/assets/game08/black_rook.png");
        pieceImageId[BLACK][KNIGHT] = loadImage("../MAIN/assets/game08/black_knight.png");
        pieceImageId[BLACK][BISHOP] = loadImage("../MAIN/assets/game08/black_bishop.png");
        pieceImageId[BLACK][QUEEN] = loadImage("../MAIN/assets/game08/black_queen.png");
        pieceImageId[BLACK][KING] = loadImage("../MAIN/assets/game08/black_king.png");
        // 盤面初期化
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                squares[y][x] = Piece();
                moveHint[y][x] = false;
                doubleStepHint[y][x] = false;
                specialMoveHint[y][x] = false;
            }
        }

        // 駒の初期配置
        
        // ポーン
        for (int x = 0; x < SIZE; x++) {
            squares[1][x] = Piece(PAWN, BLACK);
            squares[6][x] = Piece(PAWN, WHITE);
        }

        // ルーク
        squares[0][0] = squares[0][7] = Piece(ROOK, BLACK);
        squares[7][0] = squares[7][7] = Piece(ROOK, WHITE);

        // ナイト
        squares[0][1] = squares[0][6] = Piece(KNIGHT, BLACK);
        squares[7][1] = squares[7][6] = Piece(KNIGHT, WHITE);

        // ビショップ
        squares[0][2] = squares[0][5] = Piece(BISHOP, BLACK);
        squares[7][2] = squares[7][5] = Piece(BISHOP, WHITE);

        // クイーン
        squares[0][3] = Piece(QUEEN, BLACK);
        squares[7][3] = Piece(QUEEN, WHITE);

        // キング
        squares[0][4] = Piece(KING, BLACK);
        squares[7][4] = Piece(KING, WHITE);
    }

    // メインループ
    void Board::update()
    {
        if (inCheckmate) return;

        if (promotionPending) {
            handlePromotionInput();
            return;
        }

        InputEvent ev = pollInput();
        if (!ev.leftClick && !ev.rightClick) return;

        handleInputEvent(ev);
    }
    void Board::draw()
    {
        drawBoard();
        drawMoveHint();
        drawPieces();
        drawUI();
        if (promotionPending) {
            drawPromotionUI();
        }
        drawCenterStatusText();
    }

    // 描画系
    void Board::drawBoard()
    {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {

                // 通常マス
                if ((x + y) % 2 == 0) fill(200);
                else fill(100);

                // 選択中マス
                if (x == selectedX && y == selectedY) {
                    fill(255, 200, 0);
                }

                rect(
                    BOARD_X + x * CELL_SIZE,
                    BOARD_Y + y * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE
                );
            }
        }
    }
    void Board::drawMoveHint()
    {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {

                if (moveHint[y][x]) {
                    fill(0, 255, 0, 80); // 通常移動：緑
                }

                else if (doubleStepHint[y][x]) {
                    fill(0, 150, 255, 100); // 初回2マス：青
                }

                else if (specialMoveHint[y][x]) {
                    fill(255, 0, 255, 120); // 紫
                }

                else {
                    noFill();
                    continue;
                }

                rect(
                    BOARD_X + x * CELL_SIZE,
                    BOARD_Y + y * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE
                );
            }
        }
    }
    void Board::drawPieces()
    {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {

                const Piece& p = squares[y][x];
                if (p.isEmpty()) continue;

                int imgId = pieceImageId[p.color][p.type];

                image(
                    imgId,
                    BOARD_X + x * CELL_SIZE,
                    BOARD_Y + y * CELL_SIZE,
                    0,
                    0.19f
                );
            }
        }
    }


    // UI系
    void Board::drawUI() 
    {
        drawStatusText();
        drawCheckKingHighlight();
        drawHelpUI();

    }

    void Board::drawStatusText()
    {
        float x = 30.0f;
        float y = 40.0f;

        // 手番表示
        fill(255);
        textSize(28);

        if (currentTurn == WHITE) {
            text("Turn : WHITE", x, y);
        }
        else {
            text("Turn : BLACK", x, y);
        }

        y += 40;

        // チェック表示
        if (inCheck) {
            fill(255, 0, 0);   
            textSize(32);
            text("CHECK!", x, y);
            y += 45;
        }

        // チェックメイト表示
        if (inCheckmate) {
            fill(255, 215, 0);
            textSize(36);
            text("CHECKMATE!", x, y);
        }

        // ステイルメイト表示
        if (inStalemate) {
            fill(180, 180, 255);
            textSize(32);
            text("STALEMATE", x, y);
        }
    }
    void Board::drawCheckKingHighlight()
    {
        // 王手じゃなければ何もしない
        if (!inCheck) return;

        PieceColor kingColor = currentTurn;

        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {

                Piece& p = squares[y][x];
                if (p.type == KING && p.color == kingColor) {

                    float px = BOARD_X + x * CELL_SIZE;
                    float py = BOARD_Y + y * CELL_SIZE;

                    noFill();
                    stroke(255, 0, 0);
                    strokeWeight(4);
                    rect(px, py, CELL_SIZE, CELL_SIZE);
                    strokeWeight(1);
                    noStroke();

                    return;
                }
            }
        }
    }
    void Board::drawHelpUI()
    {
        // ===== 右側UIエリア =====
        float panelX = BOARD_X + CELL_SIZE * SIZE + 30;
        float panelY = BOARD_Y;
        float panelW = 340;
        float panelH = CELL_SIZE * SIZE;

        // 背景
        fill(30, 30, 30, 220);
        rect(panelX, panelY, panelW, panelH);

        float x = panelX + 20;
        float y = panelY + 40;

        fill(255);
        textSize(30);
        text("操作説明", x, y);

        y += 50;
        textSize(22);

        text("■ 左クリック", x, y);
        y += 30;
        text("  ・駒を選択", x, y);
        y += 26;
        text("  ・移動を実行", x, y);

        y += 36;
        text("■ 右クリック", x, y);
        y += 30;
        text("  ・特殊手の表示", x, y);
        y += 26;
        text("  ・キャスリング", x, y);
        y += 26;
        text("  ・アンパッサン", x, y);

        y += 40;
        text("■ プロモーション", x, y);
        y += 30;
        text("  ・出現した駒を選択", x, y);

        y += 40;
        fill(200, 200, 255);
        text("ENTER : メニューに戻る", x, y);
    }
    void Board::drawPromotionUI()
    {
        // 画面暗転
        fill(0, 0, 0, 150);
        rect(0, 0, Width, Height);

        // UIサイズ
        const float ICON_SIZE = 80.0f;
        const float ICON_MARGIN = 12.0f;

        // 表示基準位置
        float baseX = BOARD_X + promotionX * CELL_SIZE + CELL_SIZE;
        float baseY = BOARD_Y + promotionY * CELL_SIZE;

        // 画面外にはみ出ない調整
        if (baseX + ICON_SIZE > Width)
            baseX = BOARD_X + promotionX * CELL_SIZE - ICON_SIZE - 10;

        if (baseY + ICON_SIZE * 4 > Height)
            baseY = Height - ICON_SIZE * 4 - 20;

        // 説明テキスト
        fill(255);
        textSize(28);
        text("昇格先を選択してください", baseX - 110, baseY - 30);

        // 選択肢
        PieceType choices[4] = {
            QUEEN,
            ROOK,
            BISHOP,
            KNIGHT
        };

        int mx = MouseX;
        int my = MouseY;

        for (int i = 0; i < 4; i++) {
            float x = baseX;
            float y = baseY + i * (ICON_SIZE + ICON_MARGIN);

            bool hover =
                mx >= x && mx <= x + ICON_SIZE &&
                my >= y && my <= y + ICON_SIZE;

            // 外枠（ホバー強調）
            if (hover) {
                fill(255, 220, 0);
                rect(x - 4, y-24, ICON_SIZE + 8, ICON_SIZE + 8);
            }
            else {
                fill(255);
                rect(x - 2, y-22, ICON_SIZE + 4, ICON_SIZE + 4);
            }

            // 背景
            fill(60);
            rect(x, y-20, ICON_SIZE, ICON_SIZE);

            // 駒画像
            int img = pieceImageId[promotionColor][choices[i]];
            image(
                img,
                x-10,
                y-32,
                0,
                0.19
            );
        }
    }
    void Board::drawCenterStatusText()
    {
        const char* msg = nullptr;

        if (inCheckmate)      msg = "CHECKMATE";
        else if (inStalemate) msg = "STALEMATE";
        else if (inCheck)     msg = "CHECK";
        else {
            statusAnimFrame = -1;
            return;
        }

        // 盤面中央
        float cx = BOARD_X + CELL_SIZE * SIZE * 0.5f;
        float cy = BOARD_Y + CELL_SIZE * SIZE * 0.5f;

        // 自前フレームカウンタ
        if (statusAnimFrame < 0) statusAnimFrame = 0;
        statusAnimFrame++;

        int elapsed = statusAnimFrame;

        // アニメーション制御
        float scale = 1.0f;
        int alpha = 255;

        if (elapsed < 30) {
            // フェードイン＋拡大
            scale = 0.7f + elapsed * 0.02f;
            alpha = elapsed * 8;
        }
        else if (elapsed < 120) {
            // 安定表示
            scale = 1.3f;
            alpha = 255;
        }
        else {
            // フェードアウト
            alpha = 255 - (elapsed - 120) * 5;
            if (alpha < 0) alpha = 0;
        }

        // 文字サイズ
        int baseSize = inCheckmate ? 96 : 72;
        int size = (int)(baseSize * scale);
        textSize(size);

        // 色
        if (inCheckmate)      fill(240, 220, 120, alpha); // 金
        else if (inCheck)     fill(220, 80, 80, alpha);   // 赤
        else                  fill(200, 200, 200, alpha); // グレー

        // 中央寄せ
        float approxWidth = strlen(msg) * size * 0.6f;

        text(
            msg,
            cx - approxWidth * 0.4f,
            cy - size * 0.4f
        );
    }


    // 入力・選択
    bool Board::hasSelection() const {
        return selectedX != -1 && selectedY != -1;
    }
    bool Board::isInsideBoard(int mx, int my, int& bx, int& by)
    {
        if (mx < BOARD_X || my < BOARD_Y) return false;
        if (mx >= BOARD_X + CELL_SIZE * SIZE) return false;
        if (my >= BOARD_Y + CELL_SIZE * SIZE) return false;

        bx = (int)((mx - BOARD_X) / CELL_SIZE);
        by = (int)((my - BOARD_Y) / CELL_SIZE);

        return true;
    }
    Board::InputEvent Board::pollInput()
    {
        InputEvent ev;

        ev.leftClick = isTrigger(MOUSE_LBUTTON);
        ev.rightClick = isTrigger(MOUSE_RBUTTON);

        if (!ev.leftClick && !ev.rightClick) return ev;

        int mx = (int)mouseX;
        int my = (int)mouseY;

        if (!isInsideBoard(mx, my, ev.bx, ev.by)) {
            ev.bx = ev.by = -1;
        }

        return ev;
    }

    void Board::handleInputEvent(const InputEvent& ev)
    {
        if (ev.bx < 0 || ev.by < 0) return;

        if (!hasSelection()) {
            handleSelect(ev);
        }
        else {
            handleAction(ev);
        }
    }
    void Board::handleSelect(const InputEvent& ev)
    {
        Piece& p = squares[ev.by][ev.bx];
        if (p.isEmpty()) return;
        if (p.color != currentTurn) return;

        selectedX = ev.bx;
        selectedY = ev.by;

        clearMoveHint();

        if (ev.rightClick) {
            if (p.type == KING)  calcCastlingHint(ev.bx, ev.by);
            if (p.type == PAWN)  calcEnPassantHint(ev.bx, ev.by);
            return;
        }

        calcNormalMoveHint(p, ev.bx, ev.by);
    }
    void Board::handleAction(const InputEvent& ev)
    {
        int sx = selectedX;
        int sy = selectedY;

        Piece& p = squares[sy][sx];

        // 選び直し
        if (!squares[ev.by][ev.bx].isEmpty() &&
            squares[ev.by][ev.bx].color == currentTurn) {

            selectedX = ev.bx;
            selectedY = ev.by;

            clearMoveHint();
            calcNormalMoveHint(squares[ev.by][ev.bx], ev.bx, ev.by);
            return;
        }

        // 特殊手
        if (ev.rightClick && specialMoveHint[ev.by][ev.bx]) {
            if (trySpecialMove(sx, sy, ev.bx, ev.by)) {
                finalizeMove();
            }
            return;
        }

        // 通常手
        if (canMoveByType(sx, sy, ev.bx, ev.by)) {
            if (wouldBeInCheckAfterMove(sx, sy, ev.bx, ev.by, currentTurn)) return;

            executeMove(sx, sy, ev.bx, ev.by);
            if (!promotionPending) {
                finalizeMove();
            }
        }
    }
    void Board::finalizeMove()
    {
        resetSelection();
        currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;

        inCheck = isKingInCheck(currentTurn);
        inCheckmate = isCheckmate(currentTurn);
        inStalemate = isStalemate(currentTurn);

        // 演出開始
        if (inCheck || inCheckmate || inStalemate) {
            statusAnimFrame = 0;
            statusAnimActive = true;
        }
    }

    // 共通ユーティリティ
    bool Board::isInside(int x, int y) const {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }
    bool Board::isEmpty(int x, int y) const {
        return isInside(x, y) && squares[y][x].isEmpty();
    }
    bool Board::isEnemy(int x, int y, PieceColor myColor) const {
        return isInside(x, y)
            && !squares[y][x].isEmpty()
            && squares[y][x].color != myColor;
    }

    void Board::clearMoveHint()
    {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                moveHint[y][x] = false;
                doubleStepHint[y][x] = false;
                specialMoveHint[y][x] = false;
            }
        }
    }
    void Board::resetSelection()
    {
        clearMoveHint();
        selectedX = selectedY = -1;
    }

    // 駒ごとの移動

    // ポーン
    void Board::calcPawnMoveHint(int x, int y)
    {
        Piece& p = squares[y][x];
        if (p.type != PAWN) return;

        int dir = (p.color == WHITE) ? -1 : 1;
        int ny = y + dir;

        // 1マス前進
        if (isInside(x, ny) && isEmpty(x, ny)) {
            if (!wouldBeInCheckAfterMove(x, y, x, ny, p.color)) {
                moveHint[ny][x] = true;
            }

            // 初期位置なら2マス前進
            int startRow = (p.color == WHITE) ? 6 : 1;
            int ny2 = y + dir * 2;

            if (y == startRow && isInside(x, ny2) && isEmpty(x, ny2)) {
                if (!wouldBeInCheckAfterMove(x, y, x, ny2, p.color)) {
                    doubleStepHint[ny2][x] = true;
                }
            }
        }

        // 斜め攻撃
        for (int dx = -1; dx <= 1; dx += 2) {
            int nx = x + dx;
            if (isInside(nx, ny) && isEnemy(nx, ny, p.color)) {
                if (!wouldBeInCheckAfterMove(x, y, nx, ny, p.color)) {
                    moveHint[ny][nx] = true;
                }
            }
        }
    }
    bool Board::canMovePawn(int sx, int sy, int dx, int dy)
    {
        // 範囲外は即NG
        if (!isInside(dx, dy)) return false;

        Piece& pawn = squares[sy][sx];
        if (pawn.type != PAWN) return false;

        int dir = (pawn.color == WHITE) ? -1 : 1;

        // === 前に1マス ===
        if (dx == sx && dy == sy + dir) {
            if (isEmpty(dx, dy)) {
                return true;
            }
        }

        // === 初期位置から2マス ===
        int startRow = (pawn.color == WHITE) ? 6 : 1;
        if (sy == startRow && dx == sx && dy == sy + dir * 2) {
            if (isEmpty(sx, sy + dir) && isEmpty(dx, dy)) {
                return true;
            }
        }

        // === 斜め取り ===
        if (dy == sy + dir && (dx == sx - 1 || dx == sx + 1)) {
            if (isEnemy(dx, dy, pawn.color)) {
                return true;
            }
        }

        return false;
    }
    bool Board::canPawnAttack(int sx, int sy, int tx, int ty)
    {
        Piece& pawn = squares[sy][sx];
        if (pawn.type != PAWN) return false;

        int dir = (pawn.color == WHITE) ? -1 : 1;

        return (ty == sy + dir) &&
            (tx == sx - 1 || tx == sx + 1);
    }

    // ルーク
    void Board::calcRookMoveHint(int x, int y)
    {
        Piece& p = squares[y][x];
        if (p.type != ROOK) return;

        // 4方向：右・左・下・上
        const int dirs[4][2] = {
            { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }
        };

        for (int d = 0; d < 4; d++) {
            int dx = dirs[d][0];
            int dy = dirs[d][1];

            int cx = x + dx;
            int cy = y + dy;

            while (isInside(cx, cy)) {

                if (isEmpty(cx, cy)) {
                    if (!wouldBeInCheckAfterMove(x, y, cx, cy, p.color)) {
                        moveHint[cy][cx] = true;
                    }
                }
                else {
                    if (isEnemy(cx, cy, p.color)) {
                        if (!wouldBeInCheckAfterMove(x, y, cx, cy, p.color)) {
                            moveHint[cy][cx] = true;
                        }
                    }
                    break; // ★ ここ超重要
                }

                cx += dx;
                cy += dy;
            }
        }
    }
    bool Board::canMoveRook(int sx, int sy, int dx, int dy)
    {
        Piece& r = squares[sy][sx];
        if (r.type != ROOK) return false;

        return canMoveStraight(sx, sy, dx, dy);
    }

    // ビショップ
    void Board::calcBishopMoveHint(int x, int y)
    {
        Piece& p = squares[y][x];
        if (p.type != BISHOP) return;

        // 4方向の斜め
        const int dx[4] = { -1,  1, -1,  1 };
        const int dy[4] = { -1, -1,  1,  1 };

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            while (isInside(nx, ny)) {

                // 空マス → 移動可
                if (isEmpty(nx, ny)) {
                    if (!wouldBeInCheckAfterMove(x, y, nx, ny, p.color)) {
                        moveHint[ny][nx] = true;
                    }
                }
                // 敵 → 取れるが、そこで終了
                else if (isEnemy(nx, ny, p.color)) {
                    if (!wouldBeInCheckAfterMove(x, y, nx, ny, p.color)) {
                        moveHint[ny][nx] = true;
                    }
                    break;
                }
                // 味方 → そこで終了
                else {
                    break;
                }

                nx += dx[dir];
                ny += dy[dir];
            }
        }
    }
    bool Board::canMoveBishop(int sx, int sy, int dx, int dy)
    {
        Piece& b = squares[sy][sx];
        if (b.type != BISHOP) return false;

        return canMoveDiagonal(sx, sy, dx, dy);
    }

    // クイーン 
    void Board::calcQueenMoveHint(int x, int y)
    {
        Piece& q = squares[y][x];
        if (q.type != QUEEN) return;

        PieceColor myColor = q.color;

        // =========================
        // ルーク方向（縦横）
        // =========================
        const int rookDir[4][2] = {
            { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }
        };

        for (auto& d : rookDir) {
            int nx = x + d[0];
            int ny = y + d[1];

            while (isInside(nx, ny)) {
                if (isEmpty(nx, ny)) {
                    if (!wouldBeInCheckAfterMove(x, y, nx, ny, myColor)) {
                        moveHint[ny][nx] = true;
                    }
                }
                else {
                    if (isEnemy(nx, ny, myColor)) {
                        if (!wouldBeInCheckAfterMove(x, y, nx, ny, myColor)) {
                            moveHint[ny][nx] = true;
                        }
                    }
                    break;
                }
                nx += d[0];
                ny += d[1];
            }
        }

        // =========================
        // ビショップ方向（斜め）
        // =========================
        const int bishopDir[4][2] = {
            { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 }
        };

        for (auto& d : bishopDir) {
            int nx = x + d[0];
            int ny = y + d[1];

            while (isInside(nx, ny)) {
                if (isEmpty(nx, ny)) {
                    if (!wouldBeInCheckAfterMove(x, y, nx, ny, myColor)) {
                        moveHint[ny][nx] = true;
                    }
                }
                else {
                    if (isEnemy(nx, ny, myColor)) {
                        if (!wouldBeInCheckAfterMove(x, y, nx, ny, myColor)) {
                            moveHint[ny][nx] = true;
                        }
                    }
                    break;
                }
                nx += d[0];
                ny += d[1];
            }
        }
    }
    bool Board::canMoveQueen(int sx, int sy, int dx, int dy)
    {
        Piece& q = squares[sy][sx];
        if (q.type != QUEEN) return false;

        // 縦横 or 斜め
        if (sx == dx || sy == dy) {
            return canMoveStraight(sx, sy, dx, dy);
        }
        else {
            return canMoveDiagonal(sx, sy, dx, dy);
        }
    }

    // ナイト 
    void Board::calcKnightMoveHint(int x, int y)
    {
        Piece& n = squares[y][x];
        if (n.type != KNIGHT) return;

        const int dx[8] = { 1,  2,  2,  1, -1, -2, -2, -1 };
        const int dy[8] = { -2, -1,  1,  2,  2,  1, -1, -2 };

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (!isInside(nx, ny)) continue;

            // 空 or 敵ならOK
            if (isEmpty(nx, ny) || isEnemy(nx, ny, n.color)) {
                if (!wouldBeInCheckAfterMove(x, y, nx, ny, n.color)) {
                    moveHint[ny][nx] = true;
                }
            }
        }
    }
    bool Board::canMoveKnight(int sx, int sy, int dx, int dy)
    {
        if (!isInside(dx, dy)) return false;

        Piece& n = squares[sy][sx];
        if (n.type != KNIGHT) return false;

        int dxAbs = abs(dx - sx);
        int dyAbs = abs(dy - sy);

        // L字判定
        if (!((dxAbs == 1 && dyAbs == 2) ||
            (dxAbs == 2 && dyAbs == 1))) {
            return false;
        }

        // 行き先が味方ならNG
        if (!isEmpty(dx, dy) && squares[dy][dx].color == n.color) {
            return false;
        }

        return true;
    }

    // キング 
    void Board::calcKingMoveHint(int x, int y)
    {
        Piece& k = squares[y][x];
        if (k.type != KING) return;

        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {

                if (dx == 0 && dy == 0) continue;

                int nx = x + dx;
                int ny = y + dy;

                if (!isInside(nx, ny)) continue;

                if (isEmpty(nx, ny) || isEnemy(nx, ny, k.color)) {
                    if (!wouldBeInCheckAfterMove(x, y, nx, ny, k.color)) {
                        moveHint[ny][nx] = true;
                    }
                }
            }
        }
    }
    bool Board::canMoveKing(int sx, int sy, int dx, int dy)
    {
        if (!isInside(dx, dy)) return false;

        Piece& k = squares[sy][sx];
        if (k.type != KING) return false;

        int dxAbs = abs(dx - sx);
        int dyAbs = abs(dy - sy);

        if (dxAbs <= 1 && dyAbs <= 1) {
            if (isEmpty(dx, dy) || isEnemy(dx, dy, k.color)) {
                if (!wouldBeInCheckAfterMove(sx, sy, dx, dy, k.color))
                    return true;
            }
        }

        return false;
    }

    // 共通移動ロジック
    bool Board::canMoveStraight(int sx, int sy, int dx, int dy)
    {
        if (!isInside(dx, dy)) return false;

        // 縦でも横でもない
        if (sx != dx && sy != dy) return false;

        int stepX = (dx > sx) ? 1 : (dx < sx ? -1 : 0);
        int stepY = (dy > sy) ? 1 : (dy < sy ? -1 : 0);

        int cx = sx + stepX;
        int cy = sy + stepY;

        while (cx != dx || cy != dy) {
            if (!isEmpty(cx, cy)) return false;
            cx += stepX;
            cy += stepY;
        }

        // 行き先が味方ならNG
        if (!isEmpty(dx, dy) &&
            squares[dy][dx].color == squares[sy][sx].color) {
            return false;
        }

        return true;
    }
    bool Board::canMoveDiagonal(int sx, int sy, int dx, int dy)
    {
        if (!isInside(dx, dy)) return false;

        int dxDir = dx - sx;
        int dyDir = dy - sy;

        if (abs(dxDir) != abs(dyDir)) return false;

        int stepX = (dxDir > 0) ? 1 : -1;
        int stepY = (dyDir > 0) ? 1 : -1;

        int x = sx + stepX;
        int y = sy + stepY;

        while (x != dx) {
            if (!isEmpty(x, y)) return false;
            x += stepX;
            y += stepY;
        }

        // 行き先が味方ならNG
        if (!isEmpty(dx, dy) &&
            squares[dy][dx].color == squares[sy][sx].color)
            return false;

        return true;
    }

    // 特殊ルール

    // キャスリング
    bool Board::executeCastle(int sx, int sy, int dx, int dy)
    {
        Piece& k = squares[sy][sx];
        if (k.type != KING) return false;

        if (abs(dx - sx) != 2 || dy != sy) return false;

        bool kingSide = (dx > sx);

        if (!canCastle(k.color, kingSide)) return false;

        moveKing(sx, sy, dx, dy);
        return true;
    }
    bool Board::canCastle(PieceColor color, bool kingSide)
    {
        // 共通：今チェックされていたら不可
        if (isKingInCheck(color))
            return false;

        if (kingSide)
            return canCastleKingSide(color);
        else
            return canCastleQueenSide(color);
    }
    void Board::calcCastlingHint(int x, int y)
    {
        Piece& king = squares[y][x];
        if (king.type != KING) return;

        // すでにチェック中なら不可
        if (isKingInCheck(king.color)) return;

        int row = (king.color == WHITE) ? 7 : 0;

        // キング側
        if (canCastleKingSide(king.color)) {
            specialMoveHint[row][6] = true;
        }

        // クイーン側
        if (canCastleQueenSide(king.color)) {
            specialMoveHint[row][2] = true;
        }
    }
    bool Board::canCastleKingSide(PieceColor color)
    {
        int row = (color == WHITE) ? 7 : 0;

        //キング確認
        if (squares[row][4].type != KING ||
            squares[row][4].hasMoved)
            return false;

        // ルーク確認
        if (squares[row][7].type != ROOK ||
            squares[row][7].color != color ||
            squares[row][7].hasMoved)
            return false;

        // 間が空いているか
        if (!isEmpty(5, row) || !isEmpty(6, row)) return false;

        // 通過マスが安全か
        if (wouldBeInCheckAfterMove(4, row, 5, row, color)) return false;
        if (wouldBeInCheckAfterMove(4, row, 6, row, color)) return false;

        return true;
    }
    bool Board::canCastleQueenSide(PieceColor color)
    {
        int row = (color == WHITE) ? 7 : 0;

        // クイーン側ルークがいるか
        if (squares[row][0].type != ROOK ||
            squares[row][0].color != color ||
            squares[row][0].hasMoved)
            return false;

        // キング側も確認
        if (squares[row][4].type != KING ||
            squares[row][4].hasMoved)
            return false;

        // 間のマスが空か（b,c,d）
        if (!isEmpty(1, row) || !isEmpty(2, row) || !isEmpty(3, row))
            return false;

        // キングが通過・到達するマスが安全か
        // e → d
        if (wouldBeInCheckAfterMove(4, row, 3, row, color))
            return false;

        // e → c
        if (wouldBeInCheckAfterMove(4, row, 2, row, color))
            return false;

        return true;

    }
    bool Board::canCastleCheckOnly(int sx, int sy, int dx, int dy)
    {
        Piece& k = squares[sy][sx];
        if (k.type != KING) return false;

        // キングの2マス移動か？
        if (abs(dx - sx) != 2 || dy != sy) return false;

        bool kingSide = (dx > sx);

        // ルール上キャスリング可能か
        if (!canCastle(k.color, kingSide)) return false;

        // 仮想的に動かして王手にならないか
        if (wouldBeInCheckAfterMove(sx, sy, dx, dy, k.color))
            return false;

        return true;
    }

    // アンパッサン
    bool Board::executeEnPassant(int sx, int sy, int dx, int dy)
    {
        if (!enPassantAvailable) return false;

        Piece& pawn = squares[sy][sx];
        if (pawn.type != PAWN) return false;

        int dir = (pawn.color == WHITE) ? -1 : 1;

        // 移動先チェック
        if (dx != enPassantX || dy != sy + dir)
            return false;

        // 取られるポーン確認
        Piece& target = squares[sy][dx];
        if (target.type != PAWN || target.color == pawn.color)
            return false;

        // 実行
        squares[sy][dx] = Piece();   // 敵ポーン除去
        movePiece(sx, sy, dx, dy);

        enPassantAvailable = false;
        return true;
    }
    void Board::calcEnPassantHint(int x, int y)
    {
        if (!enPassantAvailable) return;

        Piece& pawn = squares[y][x];
        if (pawn.type != PAWN) return;

        int dir = (pawn.color == WHITE) ? -1 : 1;

        // ★ ここが修正点
        if (abs(enPassantX - x) == 1 && enPassantY == y + dir) {
            specialMoveHint[y + dir][enPassantX] = true;
        }
    }
    bool Board::canEnPassantCheckOnly(int sx, int sy, int dx, int dy)
    {
        if (!enPassantAvailable) return false;

        Piece& p = squares[sy][sx];
        if (p.type != PAWN) return false;

        int dir = (p.color == WHITE) ? -1 : 1;

        // アンパッサンの移動先か？
        if (dx != enPassantX || dy != sy + dir)
            return false;

        // 仮想的に動かして王手にならないか
        if (wouldBeInCheckAfterMove(sx, sy, dx, dy, p.color))
            return false;

        return true;
    }

    // 実移動・仮想移動

    // 実移動
    void Board::movePiece(int sx, int sy, int dx, int dy)
    {
        Piece& p = squares[sy][sx];

        // デフォルトでアンパッサン無効
        enPassantAvailable = false;

        // ポーンの2マス前進を検知
        if (p.type == PAWN && abs(dy - sy) == 2) {
            enPassantAvailable = true;
            enPassantX = dx;
            enPassantY = (sy + dy) / 2; // 通過マス
        }

        squares[dy][dx] = p;
        squares[dy][dx].hasMoved = true;
        squares[sy][sx] = Piece();
    }
    void Board::moveKing(int sx, int sy, int dx, int dy) {
        bool isCastling = (abs(dx - sx) == 2);

        if (isCastling) {
            int step = (dx > sx) ? 1 : -1;
            int rookFromX = (step == 1) ? 7 : 0;
            int rookToX = sx + step;

            // ルーク移動
            squares[sy][rookToX] = squares[sy][rookFromX];
            squares[sy][rookToX].hasMoved = true;
            squares[sy][rookFromX] = Piece();
        }

        // キング移動
        squares[dy][dx] = squares[sy][sx];
        squares[dy][dx].hasMoved = true;
        squares[sy][sx] = Piece();
    }
    void Board::executeMove(int sx, int sy, int dx, int dy)
    {
        Piece moved = squares[sy][sx];

        if (moved.type == KING) {
            moveKing(sx, sy, dx, dy);
        }
        else {
            movePiece(sx, sy, dx, dy);
        }

        // プロモーション判定
        if (moved.type == PAWN && (dy == 0 || dy == 7)) {
            promotionPending = true;
            promotionX = dx;
            promotionY = dy;
            promotionColor = moved.color;
        }
    }

    // 仮想移動
    Board::MoveBackup Board::simulateMove(int sx, int sy, int dx, int dy)
    {
        MoveBackup b;

        b.from = squares[sy][sx];
        b.to = squares[dy][dx];

        Piece& p = squares[sy][sx];

        // ---- アンパッサン ----
        int dir = (p.color == WHITE) ? -1 : 1;

        if (p.type == PAWN &&
            enPassantAvailable &&
            dx == enPassantX &&
            dy == sy + dir)
        {
            int capY = sy;
            b.hadExtra = true;
            b.ex = dx;
            b.ey = capY;
            b.extra = squares[capY][dx];

            squares[capY][dx] = Piece();
        }

        // ---- 本体移動 ----
        squares[dy][dx] = p;
        squares[sy][sx] = Piece();

        return b;
    }
    void Board::undoSimulateMove(
        int sx, int sy,
        int dx, int dy,
        const MoveBackup& b
    ) {
        squares[sy][sx] = b.from;
        squares[dy][dx] = b.to;

        if (b.hadExtra) {
            squares[b.ey][b.ex] = b.extra;
        }
    }

    // チェック・勝敗判定
    bool Board::isKingInCheck(PieceColor kingColor)
    {
        int kingX = -1;
        int kingY = -1;

        //キングの位置を探す
        bool found = false;
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                Piece& p = squares[y][x];
                if (p.type == KING && p.color == kingColor) {
                    kingX = x;
                    kingY = y;
                    found = true;
                    break;
                }
            }
            if (found)break;
        }

        if (kingX == -1) return false;

        //敵の駒がキングを取れるか？
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                Piece& enemy = squares[y][x];

                if (enemy.isEmpty()) continue;
                if (enemy.color == kingColor) continue;

                bool canAttack = false;

                switch (enemy.type) {
                case PAWN:
                    canAttack = canPawnAttack(x, y, kingX, kingY);
                    break;
                case ROOK:
                    canAttack = canMoveRook(x, y, kingX, kingY);
                    break;
                case BISHOP:
                    canAttack = canMoveBishop(x, y, kingX, kingY);
                    break;
                case QUEEN:
                    canAttack = canMoveQueen(x, y, kingX, kingY);
                    break;
                case KNIGHT:
                    canAttack = canMoveKnight(x, y, kingX, kingY);
                    break;
                case KING:
                    canAttack = abs(x - kingX) <= 1 && abs(y - kingY) <= 1;
                    break;
                }

                if (canAttack) {
                    return true; // チェック！
                }
            }
        }

        return false;
    }
    bool Board::wouldBeInCheckAfterMove(
        int sx, int sy,
        int dx, int dy,
        PieceColor color
    ) {
        MoveBackup backup = simulateMove(sx, sy, dx, dy);

        bool inCheck = isKingInCheck(color);

        undoSimulateMove(sx, sy, dx, dy, backup);

        return inCheck;
    }
    bool Board::hasAnyLegalMove(int sx, int sy)
    {
        Piece& p = squares[sy][sx];

        for (int dy = 0; dy < SIZE; dy++) {
            for (int dx = 0; dx < SIZE; dx++) {

                // 通常手
                if (canMoveByType(sx, sy, dx, dy) &&
                    !wouldBeInCheckAfterMove(sx, sy, dx, dy, p.color))
                {
                    return true;
                }

                // キャスリング
                if (p.type == KING &&
                    canCastleCheckOnly(sx, sy, dx, dy))
                {
                    return true;
                }

                // アンパッサン
                if (p.type == PAWN &&
                    canEnPassantCheckOnly(sx, sy, dx, dy))
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool Board::isCheckmate(PieceColor color)
    {
        //チェックかどうか
        if (!isKingInCheck(color)) return false;

        //いずれかの駒に合法手があるか
        for (int sy = 0; sy < SIZE; sy++) {
            for (int sx = 0; sx < SIZE; sx++) {

                Piece& p = squares[sy][sx];
                if (p.isEmpty() || p.color != color) continue;

                //その駒の合法手を1つでも試す
                if (hasAnyLegalMove(sx, sy)) {
                    return false; //合法手あり → メイトじゃない
                }
            }
        }

        //チェックメイト
        return true;
    }
    bool Board::isStalemate(PieceColor color)
    {
        // チェックされていたらステイルメイトではない
        if (isKingInCheck(color)) return false;

        // 自分の駒すべてを調べる
        for (int sy = 0; sy < SIZE; sy++) {
            for (int sx = 0; sx < SIZE; sx++) {

                Piece& p = squares[sy][sx];
                if (p.isEmpty() || p.color != color) continue;

                // 1つでも合法手があれば継続
                if (hasAnyLegalMove(sx, sy)) {
                    return false;
                }
            }
        }

        // チェックされてない & 合法手ゼロ
        return true;
    }

    // プロモーション 
    void Board::handlePromotionInput()
    {
        if (!isTrigger(MOUSE_LBUTTON)) return;

        int mx = (int)mouseX;
        int my = (int)mouseY;

        // === drawPromotionUI と完全一致させる ===
        const float ICON_SIZE = 80.0f;
        const float ICON_MARGIN = 12.0f;

        float baseX = BOARD_X + promotionX * CELL_SIZE + CELL_SIZE;
        float baseY = BOARD_Y + promotionY * CELL_SIZE;

        // 横はみ出し補正
        if (baseX + ICON_SIZE > Width)
            baseX = BOARD_X + promotionX * CELL_SIZE - ICON_SIZE - 10;

        // 縦はみ出し補正
        if (baseY + ICON_SIZE * 4 > Height)
            baseY = Height - ICON_SIZE * 4 - 20;

        PieceType choices[4] = {
            QUEEN,
            ROOK,
            BISHOP,
            KNIGHT
        };

        for (int i = 0; i < 4; i++) {

            float x = baseX;
            float y = baseY + i * (ICON_SIZE + ICON_MARGIN);

            // drawPromotionUI の「背景 rect」と一致
            float rx = x;
            float ry = y - 20;

            if (mx >= rx && mx <= rx + ICON_SIZE &&
                my >= ry && my <= ry + ICON_SIZE)
            {
                // 昇格
                squares[promotionY][promotionX] =
                    Piece(choices[i], promotionColor);

                squares[promotionY][promotionX].hasMoved = true;

                resetSelection();
                promotionPending = false;

                // ターン交代
                currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;

                // 状態更新
                inCheck = isKingInCheck(currentTurn);
                inCheckmate = isCheckmate(currentTurn);
                inStalemate = isStalemate(currentTurn);

                return;
            }
        }
    }

    // まとめ関数
    void Board::calcNormalMoveHint(const Piece& p, int x, int y)
    {
        switch (p.type) {
        case PAWN:   calcPawnMoveHint(x, y);   break;
        case ROOK:   calcRookMoveHint(x, y);   break;
        case BISHOP: calcBishopMoveHint(x, y); break;
        case QUEEN:  calcQueenMoveHint(x, y);  break;
        case KNIGHT: calcKnightMoveHint(x, y); break;
        case KING:   calcKingMoveHint(x, y);   break;
        default: break;
        }
    }
    bool Board::trySpecialMove(int sx, int sy, int dx, int dy)
    {
        Piece& p = squares[sy][sx];

        if (p.type == KING) {
            return executeCastle(sx, sy, dx, dy);
        }
        if (p.type == PAWN) {
            return executeEnPassant(sx, sy, dx, dy);
        }
        return false;
    }
    bool Board::canMoveByType(int sx, int sy, int dx, int dy)
    {
        Piece& p = squares[sy][sx];

        switch (p.type) {
        case PAWN:   return canMovePawn(sx, sy, dx, dy);
        case ROOK:   return canMoveRook(sx, sy, dx, dy);
        case BISHOP: return canMoveBishop(sx, sy, dx, dy);
        case QUEEN:  return canMoveQueen(sx, sy, dx, dy);
        case KNIGHT: return canMoveKnight(sx, sy, dx, dy);
        case KING:   return canMoveKing(sx, sy, dx, dy);
        default:     return false;
        }
    }
}