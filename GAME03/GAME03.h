#pragma once
#include <vector>
#include "../MAIN/GAME_BASE.h"
#include "MiniTemplate.h"
#include <Windows.h>

namespace GAME03 {

    class GAME : public GAME_BASE {
    public:
        GAME(class MAIN* main);

        int  create()  override;
        void proc()    override;
        void destroy() override;

        enum DIFFICULTY { EASY, NORMAL, HARD };

    private:
        // =============================
        // 基本定数
        // =============================
        static const int SIZE = 9;
        static const int EMPTY = 0;
        static const int BLOCK = 1;

        // =============================
        // 盤面
        // =============================
        int undoLeft = 0;

        int getUndoLimit() const {
            if (selectedDifficulty == EASY)   return 9999; // 実質無制限
            if (selectedDifficulty == NORMAL) return 15;
            return 5; // HARD
        }

        int  board[SIZE][SIZE];
        bool visited[SIZE][SIZE];
        DIR  arrow[SIZE][SIZE];
        DIR getTemplateDirection(int a, int b);
        int px = 0;
        int py = 0;
        int startPX = 0;
        int startPY = 0;

        int visitCount = 0;
        int totalEmpty = 0;
        bool gameClear = false;
        bool debugGenFailed = false;

        // =============================
        // 状態管理
        // =============================
        enum STATE { TITLE, PLAY, CLEAR };
        STATE State = TITLE;

        bool playInitFlg = false;
        bool prevEnterKey = false;
        bool showClearRoute = false;

        int selectedDifficulty = EASY;
        int countBlocks9x9() const;
        void makeSnakePath9x9(std::vector<std::pair<int, int>>& out);
        int getTargetBlocks() const;

        // =============================
        // テンプレート処理（★核）
        // =============================
        void decideTemplates(MiniTemplate placed[9]);
        bool canConnect(
            const MiniTemplate& from,
            const MiniTemplate& to,
            DIR dir
        );
        void applyMainPathToBoard();
        void createTemplateSnakePath();
        void build9x9FromTemplates(const MiniTemplate placed[9]);
        void createMainPath9x9FromTemplates(const MiniTemplate placed[9]);
        void setStartFromTemplate(const MiniTemplate placed[9]);
        //     void buildMainPath9x9FromTemplates(MiniTemplate placed[9]);
        bool buildMainPath9x9FromTemplates(MiniTemplate placed[9]);

        // =============================
        // 正解ルート
        // =============================
        std::vector<std::pair<int, int>> templateRoute; // (tx, ty)

        std::vector<std::pair<int, int>> mainPath9x9;
        std::vector<std::pair<int, int>> moveHistory;

        // =============================
        // 共通処理
        // =============================
        bool showRoute = false;
        void buildArrowFromMainPath9x9();

        void clearMap();
        void resetVisited();
        int  countEmptyCells() const;
        void generateMap();
        void drawBoard();
        void handleInput();
        void restartPlay();
        void buildArrowPath();

        // UI
        void drawCenteredText(
            const char* str,
            int centerX,
            int y,
            int size = 24
        );
    };

} // namespace GAME03
