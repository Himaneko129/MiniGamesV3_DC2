#pragma once
#include "GAME12.h"
namespace GAME12 {
    class MARIO {
        struct FILE_ {
            const char* file_title = 0;
            const char* file_play = 0;
            const char* file_play2 = 0;
            int blockImg = 0;
            int itemblockImg = 0;
            int goalblockImg = 0;
            int fileSize = 0;
            int images_stand = 0;
            const int numImages = 8;
            int image_No = 0;
            int counter = 0;
            int interval = 0;
            //[numImages].
            int images_move[8] = { 0 };
            int images_move_reverse[8] = { 0 };
            char fileName_move[64] = { 0 };
            char fileName_move_reverse[64] = { 0 };
        };
        struct MAP {
            char* title = 0;
            char* map = 0;
            char* map_2 = 0;
            int title_count = 0;
            int play_count = 0;
            int play_2_count = 0;
            int title_cols = 0;
            int play_cols = 0;
            int play_2_cols = 0;
            int title_rows = 0;
            int play_rows = 0;
            int play_2_rows = 0;
            int index = 0;
            int start_Cols = 0;
            int title_display_Cols = 0;
            int play_display_Cols = 0;
            int play_2_display_Cols = 0;
            int title_end_Cols = 0;
            int play_end_Cols = 0;
            int play_2_end_Cols = 0;
        };
        struct PLAYER {
            float player_x = 0;
            float player_y = 0;
            float player_width = 0;
            float player_height = 0;
            float last_player_x = 0;
            float last_player_y = 0;
            float angle = 0;
            float scale = 0.7f;
            char walk_speed = 5;
            char dash_speed = 8;
            char JUMP = 0;
            bool STOP = 0;
            bool DIRECTION = 0;
            float jump_potition_y = 0;
            const float MAX_JUMP = 250;
        };
        struct BLOCK {
            float block_x = 0;
            float block_y = 0;
            float size = 100;
            float collision_x = 0;
            float collision_y = 0;
            float goal_x = 0;
        };
        struct WORLD {
            float worldX = 0;
            float title_endWorldX = 0;
            float play_endWorldX = 0;
            float play_2_endWorldX = 0;
        };
        struct GAME {
            const enum {
                init, title, play, over, clear
            };
            char game_state = init;
            bool death_Flag = 0;
        };
        FILE* fp = 0;
        struct FILE_ f;
        struct MAP m;
        struct PLAYER p;
        struct BLOCK b;
        struct WORLD w;
        struct GAME g;
    public:
        int Select_Stage = 0;
        ~MARIO() {
            FILE_free(&m);
        }
        bool Back_Scene = false;
        void assets_road(struct FILE_* f_pointer);
        void TITLE_FILE_OPEN_etc_MEMORY_ALLOCATION(struct FILE_* f_pointer, struct MAP* m_pointer, FILE** fp_pointer);
        void PLAY_FILE_OPEN_etc_MEMORY_ALLOCATION(struct FILE_* f_pointer, struct MAP* m_pointer, FILE** fp_pointer);
        void PLAY2_FILE_OPEN_etc_MEMORY_ALLOCATION(struct FILE_* f_pointer, struct MAP* m_pointer, FILE** fp_pointer);
        void init_for_TITLE(struct MAP* m_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer);
        void init_for_PLAY(struct MAP* m_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer);
        void init_for_PLAY2(struct MAP* m_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer);
        void INIT(struct GAME* g_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer, struct FILE_* f_pointer, struct MAP* m_pointer, FILE** fp_pointer);
        void TITLE_gimmick(struct GAME* g_pointer, struct MAP* m_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer, struct FILE_* f_pointer, FILE** fp_pointer);
        void TITLE_MAP_DRAW(struct FILE_* f_pointer, struct MAP* m_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer);
        void PLAY_MAP_DRAW(struct FILE_* f_pointer, struct MAP* m_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer);
        void PLAY2_MAP_DRAW(struct FILE_* f_pointer, struct MAP* m_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer);
        void TITLE_WORLD_SCROLL(struct GAME* g_pointer, struct WORLD* w_pointer, struct PLAYER* p_pointer);
        void PLAY_WORLD_SCROLL(struct GAME* g_pointer, struct WORLD* w_pointer, struct PLAYER* p_pointer);
        void PLAY_2_WORLD_SCROLL(struct GAME* g_pointer, struct WORLD* w_pointer, struct PLAYER* p_pointer);
        void PLAYER_DRAW(struct FILE_* f_pointer, struct PLAYER* p_pointer);
        void PLAYER_MOVE(struct FILE_* f_pointer, struct PLAYER* p_pointer);
        void collision(struct MAP* m_pointer, struct FILE_* f_pointer, struct BLOCK* b_pointer, struct PLAYER* p_pointer, struct WORLD* w_pointer);
        void collision2(struct MAP* m_pointer, struct FILE_* f_pointer, struct BLOCK* b_pointer, struct PLAYER* p_pointer, struct WORLD* w_pointer);
        void remain_player_potition(struct PLAYER* p_pointer);
        void JUMP_and_FALL(struct PLAYER* p_pointer);
        void Damage_gudgment(struct GAME* g_pointer, struct PLAYER* p_pointer);
        void Clear_gudgment(struct GAME* g_pointer, struct PLAYER* p_pointer, struct MAP* m_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer);
        void GAME_OVER_Gimmick(struct GAME* g_pointer, struct MAP* m_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer);
        void GAME_CLEAR_Gimmick(struct GAME* g_pointer, struct MAP* m_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer);
        void TITLE(struct GAME* g_pointer, struct FILE_* f_pointer, struct MAP* m_pointer, FILE** fp_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer);
        void SELECT();
        void PLAY(struct GAME* g_pointer, struct FILE_* f_pointer, struct MAP* m_pointer, FILE** fp_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer);
        void PLAY2(struct GAME* g_pointer, struct FILE_* f_pointer, struct MAP* m_pointer, FILE** fp_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer);
        void OVER(struct GAME* g_pointer, struct FILE_* f_pointer, struct MAP* m_pointer, FILE** fp_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer);
        void CLEAR(struct GAME* g_pointer, struct FILE_* f_pointer, struct MAP* m_pointer, FILE** fp_pointer, struct PLAYER* p_pointer, struct BLOCK* b_pointer, struct WORLD* w_pointer);
        void game_console();
        void FILE_free(struct MAP* m_pointer);

    };
}