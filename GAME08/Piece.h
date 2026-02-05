#pragma once
#include "../../libOne/inc/libOne.h"

namespace GAME08
{
    // 駒の種類
    enum PieceType {
        NONE = 0,
        PAWN,
        ROOK,
        KNIGHT,
        BISHOP,
        QUEEN,
        KING
    };

    // 駒の色
    enum PieceColor {
        WHITE = 0,
        BLACK,
        NONE_COLOR
    };

    // 駒クラス
    class Piece {
    public:
        PieceType type;
        PieceColor color;
        bool hasMoved; // キャスリング用

        // 空マス用コンストラクタ
        Piece() : 
            type(NONE),
            color(NONE_COLOR), 
            hasMoved(false)
        {}

        // 通常駒用
        Piece(PieceType t, PieceColor c)
            : type(t),
            color(c), 
            hasMoved(false)
        {}

        bool isEmpty() const {
            return type == NONE;
        }

        char getChar() const {
            switch (type) {
            case PAWN:   return 'P';
            case ROOK:   return 'R';
            case KNIGHT: return 'N';
            case BISHOP: return 'B';
            case QUEEN:  return 'Q';
            case KING:   return 'K';
            default:     return ' ';
            }
        }
    };
}
