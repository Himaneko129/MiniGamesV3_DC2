#pragma once
#include "Piece.h"

namespace GAME08
{
    class Board {
    public:
        // 定数・基本状態
        static const int SIZE = 8;

        // 描画関連
        static constexpr float CELL_SIZE = 100.0f;
        static constexpr float BOARD_X = 200.0f;
        static constexpr float BOARD_Y = 100.0f;

        // UI表示位置
        static constexpr float UI_X = 900.0f;
        static constexpr float UI_Y = 100.0f;

        // 中央演出用
        int statusAnimFrame = 0;
        bool statusAnimActive = false;

        struct InputEvent {
            bool leftClick = false;
            bool rightClick = false;
            int bx = -1;
            int by = -1;
        };

        Board();

        // メインループ
        void update();
        void draw();

        // 描画系
        void drawBoard();
        void drawMoveHint();
        void drawPieces();
        void drawHelpUI();

        // UI系
        void drawUI();

        void drawStatusText();
        void drawCheckKingHighlight();
        void drawPromotionUI();
        void drawCenterStatusText();

        // 入力・選択
        bool hasSelection() const;
        bool isInsideBoard(int mx, int my, int& bx, int& by);
        InputEvent pollInput();

        void handleInputEvent(const InputEvent& ev);
        void handleSelect(const InputEvent& ev);
        void handleAction(const InputEvent& ev);
        void finalizeMove();

        // 状態表示用
        bool inCheck;
        bool inCheckmate;
        bool inStalemate;

        // プロモーション状態
        bool promotionPending;
        int promotionX;
        int promotionY;
        PieceColor promotionColor;

    private:
        int pieceImageId[3][7];
        // 盤面
        Piece squares[SIZE][SIZE];
        PieceColor currentTurn;

        // 選択状態
        int selectedX;
        int selectedY;

        // ヒント管理
        bool moveHint[SIZE][SIZE];        // 通常移動
        bool doubleStepHint[SIZE][SIZE];  // ポーン2歩
        bool specialMoveHint[SIZE][SIZE]; // キャスリング・アンパッサン

        void clearMoveHint();
        void resetSelection();

        // アンパッサン
        int enPassantX = 0;
        int enPassantY = 0;
        bool enPassantAvailable;

        // 共通ユーティリティ
        bool isInside(int x, int y) const;
        bool isEmpty(int x, int y) const;
        bool isEnemy(int x, int y, PieceColor myColor) const;

        bool canMoveStraight(int sx, int sy, int dx, int dy);
        bool canMoveDiagonal(int sx, int sy, int dx, int dy);

        // ポーン
        void calcPawnMoveHint(int x, int y);
        bool canMovePawn(int sx, int sy, int dx, int dy);
        bool canPawnAttack(int sx, int sy, int tx, int ty);

        // ルーク
        void calcRookMoveHint(int x, int y);
        bool canMoveRook(int sx, int sy, int dx, int dy);

        // ビショップ
        void calcBishopMoveHint(int x, int y);
        bool canMoveBishop(int sx, int sy, int dx, int dy);

        // クイーン
        void calcQueenMoveHint(int x, int y);
        bool canMoveQueen(int sx, int sy, int dx, int dy);

        // ナイト
        void calcKnightMoveHint(int x, int y);
        bool canMoveKnight(int sx, int sy, int dx, int dy);

        // キング
        void calcKingMoveHint(int x, int y);
        bool canMoveKing(int sx, int sy, int dx, int dy);

        // キャスリング
        bool executeCastle(int sx, int sy, int dx, int dy);
        void moveKing(int sx, int sy, int dx, int dy);

        bool canCastleKingSide(PieceColor color);
        bool canCastleQueenSide(PieceColor color);
        bool canCastle(PieceColor color, bool kingSide);
        bool canCastleCheckOnly(int sx, int sy, int dx, int dy);
        void calcCastlingHint(int x, int y);

        // アンパッサン
        bool executeEnPassant(int sx, int sy, int dx, int dy);
        void calcEnPassantHint(int x, int y);
        bool canEnPassantCheckOnly(int sx, int sy, int dx, int dy);

        // 実移動
        void movePiece(int sx, int sy, int dx, int dy);
        void executeMove(int sx, int sy, int dx, int dy);

        // 仮想移動
        struct MoveBackup;

        MoveBackup simulateMove(int sx, int sy, int dx, int dy);
        void undoSimulateMove(int sx, int sy, int dx, int dy, const MoveBackup& b);

        // チェック・勝利判定
        bool isKingInCheck(PieceColor kingColor);
        bool wouldBeInCheckAfterMove(
            int sx, int sy,
            int dx, int dy,
            PieceColor myColor
        );

        bool hasAnyLegalMove(int sx, int sy);
        bool isCheckmate(PieceColor color);
        bool isStalemate(PieceColor color);

        // プロモーション
        void handlePromotionInput();

        // まとめ
        void calcNormalMoveHint(const Piece& p, int x, int y);
        bool trySpecialMove(int sx, int sy, int dx, int dy);
        bool canMoveByType(int sx, int sy, int dx, int dy);
    };
}
