#pragma once
namespace GAME05 {
    class MAP3 :public PLAYER {
        int StageImage = 0;
        int BackImage = 0;
        int GoalImage = 0;
        int StageMusic = 0;
        const char* fileName = 0;
        int fileSize = 0;
        char* map = 0;
        int count = 0;
        int cols = 0;
        int rows = 0;
        int index = 0;
        float blockSize = 0;
        float Block_X = 0;
        float Block_Y = 0;
        float Collision_X = 0;
        float Collision_Y = 0;
        float worldX = 0;
        float endWorldX = 0;
        int start_Cols = 0;
        int display_Cols = 0;
        int end_Cols = 0;
        float distance_x = 0;
        float distance_y = 0;
        float Sq_distance_x = 0;
        float Sq_distance_y = 0;
        float distance = 0;
    public:
        void setImage(int Img, int gImg);
        void setMusic(int Music);
        void playMusic();
        void stopMusic();
        void for_MAP3_INIT();
        void for_MAP3_LOAD();
        void MAP3FILE_OPEN_etc_MEMORY_ALLOCATION(FILE** fp_pointer);
        void MAP3WORLD_SCROLL();
        void MAP3_DRAW();
        void PLAYER_MAP3_COLLISION(class PLAYER* p_pointer, class GAME_STRUCT* g_pointer);
        void MAP3_Free();
        void RESTART_MAP3();
    };
}