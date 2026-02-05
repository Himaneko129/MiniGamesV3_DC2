#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME05.h"
#include"GAME_STRUCT.h"
#include"Player.h"
#include"MAP.h"
#include"STAGE2_MAP.h"
#include"TITLE.h"
#include"SELECT.h"
#include"STAGE3_MAP.h"
/*
namespace GAME05{
	struct PLAYER
	...

	新しくファイルを作る場合はこのように.
*/
namespace GAME05
{

	int GAME::create()
	{
		player = new PLAYER;
		map = new MAP;
		map2 = new MAP2;
		title = new TITLE;
		game_struct = new GAME_STRUCT;
		select = new SELECT;
		map3 = new MAP3;
		int player_load_Image = loadImage("..\\MAIN\\assets\\game05\\player11.png");
		int title_load_Image = loadImage("..\\MAIN\\assets\\game05\\block_graw.png");
		int stage_load_Image = loadImage("..\\MAIN\\assets\\game05\\block_graw.png");
		int stage2_load_Image = loadImage("..\\MAIN\\assets\\game05\\block_graw.png");
		int stage3_load_Image = loadImage("..\\MAIN\\assets\\game05\\block_graw.png");
		int stage_goal_Image = loadImage("..\\MAIN\\assets\\game05\\goal.png");
		int stage2_goal_Image = loadImage("..\\MAIN\\assets\\game05\\goal.png");
		int stage3_goal_Image = loadImage("..\\MAIN\\assets\\game05\\goal.png");
		int stage1_sound = loadSound("..\\main\\assets\\game05\\Artcore_first_5.wav");
		int stage2_sound = loadSound("..\\main\\assets\\game05\\hardcore_1.wav");
		int stage3_sound = loadSound("..\\main\\assets\\game05\\[drum'n'bass]_first_mecafuture.wav");
		player->setImage(player_load_Image);
		title->setImage(title_load_Image);
		map->setImage(stage_load_Image, stage_goal_Image);
		map2->setImage(stage2_load_Image, stage2_goal_Image);
		map3->setImage(stage3_load_Image, stage3_goal_Image);
		map->setMusic(stage1_sound);
		map2->setMusic(stage2_sound);
		map3->setMusic(stage3_sound);

		player->Player_INIT();
		title->for_TITLE_LOAD();
		title->FILE_OPEN_etc_MEMORY_ALLOCATION(&fp);
		title->for_TITLE_INIT();
		map->for_MAP_LOAD();
		map->FILE_OPEN_etc_MEMORY_ALLOCATION(&fp);
		map->for_MAP_INIT();
		map2->for_MAP2_LOAD();
		map2->MAP2FILE_OPEN_etc_MEMORY_ALLOCATION(&fp);
		map2->for_MAP2_INIT();
		map3->for_MAP3_LOAD();
		map3->MAP3FILE_OPEN_etc_MEMORY_ALLOCATION(&fp);
		map3->for_MAP3_INIT();
		select->INIT_for_SELECT();
		return 0;
	}

	void GAME::destroy()
	{
		title->TITLE_Free();
		map->MAP_Free();
		map2->MAP2_Free();
		map3->MAP3_Free();
		delete player;
		delete map;
		delete map2;
		delete title;
		delete game_struct;
		delete select;
		delete map3;
	}
	void GAME::proc()
	{
		if (game_struct->game_state == game_struct->MAEGAKI) {
			fill(255);
			textSize(50);
			text("GAME TITLE : SO5:20Z", 700, 100);
			text("楽曲の音量が大きいです！",200,200);
			text("十分に音量を下げてからプレイすることを推奨します。", 200, 300);
			text("移動方法", 200, 500);
			text("Q&U : →↑", 200, 600);
			text("W&I :→", 200, 700);
			text("E&O : →↓", 200, 800);
			text("A&J :↑", 800, 600);
			text("S&K :←", 800, 700);
			text("D&L : ↓", 800, 800);
			text("Press F", 1000, 1000);
			text("→ TITLE", 1000, 1050);
			if (isTrigger(KEY_F)) {
				game_struct->game_state = game_struct->TITLE;
			}
			text("ENTERキーでメニューに戻る", 0, 1080);
			if (isTrigger(KEY_ENTER)) {
				main()->backToMenu();
			}
		}
		if (game_struct->game_state == game_struct->TITLE) {
			clear();
			title->WORLD_SCROLL();
			title->MAP_DRAW();
			title->TITLE_text();
			if (isTrigger(KEY_SPACE)) {
				game_struct->game_state = game_struct->SELECT;
				player->Player_position_reset();
			}
			text("ENTERキーでメニューに戻る", 0, 1080);
			if (isTrigger(KEY_ENTER)) {
				main()->backToMenu();
			}
		}
		if (game_struct->game_state == game_struct->SELECT) {
			player->Player_SELECT_MOVE();
			select->MOVE_AREA(player);
			clear();
			select->DRAW_for_SELECT(player);
			select->select_text();
			player->Player_DRAW();
			game_struct->Music_Change();
			if (game_struct->music_onoff == 1) {
				select->DRAW_MIC();
			}
			if (isTrigger(KEY_F)) {
				game_struct->game_state = game_struct->PLAY;
				player->Player_position_reset();
			}
			text("ENTERキーでメニューに戻る", 0, 1080);
			if (isTrigger(KEY_ENTER)) {
				main()->backToMenu();
			}
		}
		if (game_struct->game_state == game_struct->PLAY) {
			if (select->STAGE_SELECT() == 1) {
				if (game_struct->play_start == 0) {
					clear();
					map->MAP_DRAW();
					player->Player_DRAW();
					fill(255);
					textSize(100);
					text("Game Start", 0, 850);
					text("Press W", 0, 950);
					if (isTrigger(KEY_W)) {
						game_struct->play_start = 1;
						if (game_struct->music_onoff == 0) {
							map->playMusic();
						}
					}
				}
				if (game_struct->play_start == 1) {
					map->WORLD_SCROLL();
					player->Player_MOVE(1);
					map->PLAYER_MAP_COLLISION(player, game_struct);
					clear();
					map->MAP_DRAW();
					player->Player_DRAW();
				}
				fill(255);
				textSize(50);
				text("ENTERキーでメニューに戻る", 0, 1080);
				textSize(100);
				if (isTrigger(KEY_ENTER)) {
					main()->backToMenu();
				}
			}
			else if (select->STAGE_SELECT() == 2) {
				if (game_struct->play_start == 0) {
					clear();
					map2->MAP2_DRAW();
					player->Player_DRAW();
					fill(255);
					textSize(100);
					text("Game Start", 0, 850);
					text("Press W", 0, 950);
					if (isTrigger(KEY_W)) {
						game_struct->play_start = 1;
						if (game_struct->music_onoff == 0) {
							map2->playMusic();
						}
					}
				}
				if (game_struct->play_start == 1) {
					map2->MAP2WORLD_SCROLL();
					player->Player_MOVE(2);
					player->Player_MOVE(2);
					map2->PLAYER_MAP2_COLLISION(player, game_struct);
					clear();
					map2->MAP2_DRAW();
					player->Player_DRAW();
				}
				fill(255);
				textSize(50);
				text("ENTERキーでメニューに戻る", 0, 1080);
				textSize(100);
				if (isTrigger(KEY_ENTER)) {
					main()->backToMenu();
				}
			}
			else if (select->STAGE_SELECT() == 3) {
				if (game_struct->play_start == 0) {
					clear();
					map3->MAP3_DRAW();
					player->Player_DRAW();
					fill(255);
					textSize(100);
					text("Game Start", 0, 850);
					text("Press W", 0, 950);
					if (isTrigger(KEY_W)) {
						game_struct->play_start = 1;
						if (game_struct->music_onoff == 0) {
							map3->playMusic();
						}
					}
				}
				if (game_struct->play_start == 1) {
					map3->MAP3WORLD_SCROLL();
					player->Player_MOVE(3);
					player->Player_MOVE(3);
					map3->PLAYER_MAP3_COLLISION(player, game_struct);
					clear();
					map3->MAP3_DRAW();
					player->Player_DRAW();
				}
				fill(255);
				textSize(50);
				text("ENTERキーでメニューに戻る", 0, 1080);
				textSize(100);
				if (isTrigger(KEY_ENTER)) {
					main()->backToMenu();
				}
			}
			else {
				game_struct->game_state = game_struct->SELECT;
			}
		}
		if (game_struct->game_state == game_struct->OVER) {
			map->stopMusic();
			map2->stopMusic();
			map3->stopMusic();
			if (select->STAGE_SELECT() == 1) {
				clear();
				map->MAP_DRAW();
				fill(255);
				text("Game Over", 0, 700);
				text("Press SPACE", 0, 800);
				text("RE:Start", 0, 900);
				text("Press F", width/2, 800);
				text("SELECT", width / 2, 900);
				if (isTrigger(KEY_SPACE)) {
					game_struct->game_state = game_struct->PLAY;
					game_struct->play_start = 0;
					map->RESTART_MAP();
					player->Player_position_reset();
				}
				if (isTrigger(KEY_F)) {
					game_struct->game_state = game_struct->SELECT;
					game_struct->play_start = 0;
					map->RESTART_MAP();
					player->Player_position_reset();
				}
			}
			else if (select->STAGE_SELECT() == 2) {
				clear();
				map2->MAP2_DRAW();
				fill(255);
				text("Game Over", 0, 700);
				text("Press SPACE", 0, 800);
				text("RE:Start", 0, 900);
				text("Press F", width / 2, 800);
				text("SELECT", width / 2, 900);
				if (isTrigger(KEY_SPACE)) {
					game_struct->game_state = game_struct->PLAY;
					game_struct->play_start = 0;
					map2->RESTART_MAP2();
					player->Player_position_reset();
				}
				if (isTrigger(KEY_F)) {
					game_struct->game_state = game_struct->SELECT;
					game_struct->play_start = 0;
					map2->RESTART_MAP2();
					player->Player_position_reset(); 
				}
			}
			else if (select->STAGE_SELECT() == 3) {
				clear();
				map3->MAP3_DRAW();
				fill(255);
				text("Game Over", 0, 700);
				text("Press SPACE", 0, 800);
				text("RE:Start", 0, 900);
				text("Press F", width / 2, 800);
				text("SELECT", width / 2, 900);
				if (isTrigger(KEY_SPACE)) {
					game_struct->game_state = game_struct->PLAY;
					game_struct->play_start = 0;
					map3->RESTART_MAP3();
					player->Player_position_reset();
				}
				if (isTrigger(KEY_F)) {
					game_struct->game_state = game_struct->SELECT;
					game_struct->play_start = 0;
					map3->RESTART_MAP3();
					player->Player_position_reset();
				}
			}
		}
		if (game_struct->game_state == game_struct->CLEAR) {
			map->stopMusic();
			map2->stopMusic();
			if (select->STAGE_SELECT() == 1) {
				clear();
				map->MAP_DRAW();
				fill(255);
				text("YOU SUCCESS!", 0, 700);
				text("Press SPACE", 0, 800);
				if (isTrigger(KEY_SPACE)) {
					game_struct->game_state = game_struct->SELECT;
					game_struct->play_start = 0;
					map->RESTART_MAP();
					player->Player_position_reset();
				}
			}
			else if (select->STAGE_SELECT() == 2) {
				clear();
				map2->MAP2_DRAW();
				fill(255);
				text("YOU SUCCESS!", 0, 700);
				text("Press SPACE", 0, 800);
				if (isTrigger(KEY_SPACE)) {
					game_struct->game_state = game_struct->SELECT;
					game_struct->play_start = 0;
					map2->RESTART_MAP2();
					player->Player_position_reset();
				}
			}
			else if (select->STAGE_SELECT() == 3) {
				clear();
				map3->MAP3_DRAW();
				fill(255);
				text("YOU SUCCESS!", 0, 700);
				text("Press SPACE", 0, 800);
				if (isTrigger(KEY_SPACE)) {
					game_struct->game_state = game_struct->SELECT;
					game_struct->play_start = 0;
					map3->RESTART_MAP3();
					player->Player_position_reset();
				}
			}
		}
	}
}

