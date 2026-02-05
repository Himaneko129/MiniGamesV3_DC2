#pragma once
#include"GAME13.h"
namespace GAME13 {
    class MINESWEEPER {
        struct GAME {
            const int TITLE = 0;
            const int SELECT = 1;
            const int PLAY = 2;
            const int CLEAR = 3;
            const int OVER = 4;
            const int BACK = 5;
            int game_state = TITLE;
        };
        struct BLOCK {
            float block_Size = 0;
            char bomb_Flag = 0;
            //0=未選択、NOT地雷.
            //1=未選択、地雷.
            //2=選択後、NOT地雷.
            //3=地雷予想.
            char memory_mine = 0;
            bool player_flag = false;
            bool bomb_prediction = false;
        };
        struct NUMBER {
            char input_Row = 15;
            int Square_input_Row = 0;
            char input_level = 7;
            char input_disclose = 0;
            char Start_Not_Mine = 0;
        };
        struct SELECT_PLAYER {
            const int SELECT_ROW = 0;
            const int SELECT_LEVEL = 1;
            const int SELECT_DISCLOSE = 2;
            const int GO_PLAY = 3;
            int select_state = SELECT_ROW;
            char select_number = 0;
            char select_level = 0;
            bool Disclose_Flag = false;
            bool Quest_Flag = false;
        };
        struct PLAYER {
            bool start_position = false;
            int position = 0;
            char Player_Size = 20;
        };

        struct GAME game;
        struct BLOCK block[930];
        struct NUMBER number;
        struct PLAYER player;
        struct SELECT_PLAYER select;
        bool Back_Scene = false;
        bool Debug_Flag = false;
    public:
        void TITLE(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer);
        void set_block_Size(struct BLOCK* b_pointer, struct NUMBER* n_pointer);
        void set_mine(struct BLOCK* b_pointer, struct NUMBER* n_pointer);
        void Text(struct GAME* g_pointer, struct NUMBER* n_pointer, struct SELECT_PLAYER* s_pointer);
        void SELECT(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer, struct SELECT_PLAYER* s_pointer);
        void stage_draw(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer);
        void clear_decision(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer);
        void  serect_block(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer);
        void  Search_mine(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer);
        void  Push_Block(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer);
        void PLAY(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer, struct SELECT_PLAYER* s_pointer);
        void Game_finish_stage_draw(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer);
        void INIT_stage(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer, struct SELECT_PLAYER* s_pointer);
        void OVER(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer, struct SELECT_PLAYER* s_pointer);
        void CLEAR(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer, struct SELECT_PLAYER* s_pointer);
        void Back_SCENE(struct GAME* g_pointer);
        bool Sent_Back_Scene();
        void Game_console();
        void Start_Safe_Block(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer);
            void Debug_text(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer);
    };
}