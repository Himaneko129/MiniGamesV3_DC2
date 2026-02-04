#include "../../libOne/inc/libOne.h"
//#include "../MAIN/MAIN.h"
//#include "GAME05.h"
#include<fstream>
#include"PLAYER.h"
#include"GAME_STRUCT.h"
#include"MAP.h"
namespace GAME05 {
    void MAP::setImage(int Img,int gImg) {
        StageImage = Img;
        GoalImage = gImg;
    }
    void MAP::setMusic(int Music) {
        Stage_Music = Music;
    }
    void MAP::playMusic() {
        playSound(Stage_Music);
    }
    void MAP::stopMusic() {
        stopSound(Stage_Music);
    }
    void MAP::for_MAP_LOAD() {
        fileName = "..\\MAIN\\assets\\game05\\stage_map.txt";
    }
    void MAP::for_MAP_INIT() {
        blockSize=100;
        display_Cols = (width / blockSize) + 1.0f;
        endWorldX = blockSize * (cols - 2) - width;
    }
    void MAP::RESTART_MAP() {
        start_Cols = worldX / blockSize;
        end_Cols = start_Cols + display_Cols;
        display_Cols = (width / blockSize) + 1.0f;
        endWorldX = blockSize * (cols - 2) - width;
        worldX = 0;
    }
    void MAP::FILE_OPEN_etc_MEMORY_ALLOCATION(FILE** fp_pointer) {
        fopen_s(fp_pointer, fileName, "rb");
        fseek(*fp_pointer, 0, SEEK_END);
        fileSize = ftell(*fp_pointer);
        fseek(*fp_pointer, 0, SEEK_SET);
        map = (char*)malloc(fileSize);
        if (map == NULL) {
            fclose(*fp_pointer);
            return;
        }
        fread(map, sizeof(char), fileSize, *fp_pointer);
        fclose(*fp_pointer);
        for (int i = 0; i < fileSize; i++) {
            count++;
            if (map[i] == '\n') {
                if (rows == 0) {
                    cols = count;
                }
                else if (cols != count) {
                    WARNING(1, "—ñ”‚ª‘µ‚Á‚Ä‚¢‚È‚¢.", "");
                }
                rows++;
                count = 0;
            }
        }
        if (fileSize % cols != 0) {
            WARNING(1, "‰üs‚µ‚Ä‚È‚¢.", "");
        }
    }

    void MAP::WORLD_SCROLL() {
        worldX += 4;
        if (worldX >= endWorldX) {
            worldX = endWorldX;
        }
    }
    void MAP::MAP_DRAW() {
        noStroke();
        fill(50, 0, 0);
        rect(0, 0, width, height);
        start_Cols = worldX / blockSize;
        end_Cols = start_Cols + display_Cols+1;
        for (int c = start_Cols; c < end_Cols; c++) {
            Block_X = -worldX + blockSize * c;
            for (int r = 0; r < rows; r++) {
                Block_Y = blockSize * r;
                index = r * cols + c;
                    if (map[index] == 'b') {
                        image(StageImage, Block_X, Block_Y-10);
                    }
                    if (map[index] == 'g') {
                        image(GoalImage, Block_X, Block_Y-10);
                    }
            }
        }

    }
    void MAP::PLAYER_MAP_COLLISION(class PLAYER* p_pointer, class GAME_STRUCT* g_pointer) {
        noStroke();
        start_Cols = worldX / blockSize;
        end_Cols = start_Cols + display_Cols;
        for (int c = start_Cols; c < end_Cols; c++) {
            Block_X = -worldX + blockSize * c;
            for (int r = 0; r < rows; r++) {
                Block_Y = blockSize * r;
                index = r * cols + c;
                if (map[index] == 'b') {
                    Collision_X = Block_X;
                    Collision_Y = Block_Y;
                    distance_x = Collision_X - p_pointer->Last_Player_X;
                    distance_y = Collision_Y - p_pointer->Last_Player_Y;
                    Sq_distance_x = distance_x * distance_x;
                    Sq_distance_y = distance_y * distance_y;
                    distance = Sqrt(Sq_distance_x + Sq_distance_y);
                    if (p_pointer->Last_Player_X >= Collision_X && p_pointer->Last_Player_X <= Collision_X + blockSize) {
                        if (p_pointer->Last_Player_Y <= Collision_Y + (blockSize) && p_pointer->Last_Player_Y >= Collision_Y) {
                            if (distance <= 160) {
                                g_pointer->game_state = g_pointer->OVER;
                            }
                        }
                    }
                    if (p_pointer->Last_Player_X+p_pointer->Player_Width >= Collision_X && p_pointer->Last_Player_X + p_pointer->Player_Width <= Collision_X + blockSize) {
                        if (p_pointer->Last_Player_Y <= Collision_Y + (blockSize) && p_pointer->Last_Player_Y >= Collision_Y) {
                            if (distance <= 160) {
                                g_pointer->game_state = g_pointer->OVER;
                            }
                        }
                    }
                    if (p_pointer->Last_Player_X >= Collision_X && p_pointer->Last_Player_X <= Collision_X + blockSize) {
                        if (p_pointer->Last_Player_Y + p_pointer->Player_Height <= Collision_Y + (blockSize - 5) && p_pointer->Last_Player_Y + p_pointer->Player_Height >= Collision_Y) {
                            if (distance <= 160) {
                                g_pointer->game_state = g_pointer->OVER;
                            }
                        }
                    }
                    if (p_pointer->Last_Player_X + p_pointer->Player_Width >= Collision_X && p_pointer->Last_Player_X + p_pointer->Player_Width <= Collision_X + blockSize) {
                        if (p_pointer->Last_Player_Y + p_pointer->Player_Height <= Collision_Y + (blockSize - 5) && p_pointer->Last_Player_Y + p_pointer->Player_Height >= Collision_Y) {
                            if (distance <= 160) {
                                g_pointer->game_state = g_pointer->OVER;
                            }
                        }
                    }
                    if (p_pointer->Last_Player_X < 0) {
                        g_pointer->game_state = g_pointer->OVER;
                    }
                    if (p_pointer->Last_Player_X+p_pointer->Player_Width> width) {
                        g_pointer->game_state = g_pointer->OVER;
                    }
                }
                if (map[index] == 'g') {
                    Collision_X = Block_X;
                    if (p_pointer->Last_Player_X > Block_X) {
                        g_pointer->game_state = g_pointer->CLEAR;
                    }
                }
            }
        }
    }
    void MAP::MAP_Free() {
        free(map);
    }
}