#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME11.h"
#include<time.h>

#include "GAME_GRAPHIC.h"
#include "PLAYER_and_NPC.h"
#include "GAME_SCENE.h"
namespace GAME11
{
	int GAME::create()
	{
		game_scene = new GAME_SCENE;
		player = new PLAYER;
		map = new MAP;
		for (int i = 0; i < 50; i++) {
			enemy[i] = new ENEMY;
		}
		select = new SELECT;
		boss = new BOSS;
		return 0;
	}

	void GAME::destroy()
	{
		delete game_scene;
		delete player;
		delete map;
		for (int i = 0; i < 50; i++) {
			delete enemy[i];
		}
		delete select;
		delete boss;
	}

	void GAME::proc()
	{
		if (game_scene->game_state == game_scene->INIT) {
			srand((unsigned int)time(0));
			player->Player_INIT();
			player->player_status->STATUS_INIT();
			player->attack->ATTACK_INIT();
			for (int i = 0; i < 32; i++) {
				player->bullet[i]->BULLET_INIT(player);
			}
			for (int i = 0; i < 50; i++) {
				enemy[i]->ENEMY_INIT(enemy[i]);
			}
			boss->BOSS_INIT(boss);
			game_scene->game_state = game_scene->TITLE;
		}
		if (game_scene->game_state == game_scene->TITLE) {
			clear(0);
			//BOTTOM, TOP, BCENTER, MBCENTER
			fill(255);
			textSize(200);
			textMode(TOP);
			text("BRINGITON", (Yoko / 2) - 425, 100);
			textSize(100);
			text("Press_SPACE : START_GAME", (Yoko / 2) - 600, 800);
			text("Press_O : OPTION", (Yoko / 2) - 400, 900);
			//textMode(TOP);
			textSize(50);
			fill(255, 255, 0);
			//text("GAME05", 0, 100);
			fill(255);
			text("ENTERキーでメニューに戻る", 0, 1080);
			if (isTrigger(KEY_ENTER)) {
				main()->backToMenu();
			}
			if (isTrigger(KEY_SPACE)) {
				game_scene->game_state = game_scene->SELECT;
			}
			if (isTrigger(KEY_O)) {
				game_scene->game_state = game_scene->OPTION;
			}
		}
		if (game_scene->game_state == game_scene->OPTION) {
			clear(0);
			textSize(100);
			//textMode(TOP);
			text("OPTION", 0, 0);
			text("E : EXIT", 0, Tate - 100);
			if (isTrigger(KEY_E)) {
				game_scene->game_state = game_scene->TITLE;
			}
			//textMode(TOP);
		}
		if (game_scene->game_state == game_scene->SELECT) {
			clear(0);
			textMode(TOP);
			//セレクトキャラクター.
			select->SELECT_SELECT_CHARA();
			if (isTrigger(MOUSE_LBUTTON)) {
				select->GET_SELECT_NUM(select->SELECT_SELECT_CHARA());
			}
			select->SELECT_WEAPON(select->OUT_SELECT_NUM());
			//textSize(500);
			//text(select->SELECT_SELECT_CHARA(), Yoko / 2, 500);
			select->SELECT_DRAW(select->SELECT_SELECT_CHARA());
			if (select->Go_to_PLAY() == true) {
				if (select->OUT_SELECT_NUM() == 1) {
					player->attack->Flag_INIT();
					player->attack->Melee_Flag = true;
				}
				else if (select->OUT_SELECT_NUM() == 2) {
					player->attack->Flag_INIT();
					player->attack->Mouse_Flag = true;
				}
				else if (select->OUT_SELECT_NUM() == 3) {
					player->attack->Flag_INIT();
					player->attack->Range_Flag = true;
				}
				else if (select->OUT_SELECT_NUM() == 4) {
					player->attack->Flag_INIT();
					player->attack->Long_Range_Flag = true;
				}
				else if (select->OUT_SELECT_NUM() == 5) {
					player->attack->Flag_INIT();
					player->attack->Laser_Flag = true;
				}
				else if (select->OUT_SELECT_NUM() == 6) {
					player->attack->Flag_INIT();
					player->attack->Bounce_Flag = true;
				}
				else if (select->OUT_SELECT_NUM() == 7) {
					player->attack->Flag_INIT();
					player->attack->Boom_Flag = true;
					player->attack->Boom_Center_INIT();
				}
				else if (select->OUT_SELECT_NUM() == 8) {
					player->attack->Flag_INIT();
					player->attack->Random_Flag = true;
				}
				else if (select->OUT_SELECT_NUM() == 9) {
					player->attack->Flag_INIT();
					player->attack->Orbit_Flag = true;
					//int num = 2;
					for (int i = 0; i < player->ORBIT_NUM_return(); i++) {
						/*
						float start_angle = (360.0f / 12) * i;
						player->bullet[i]->ORBIT_START(i, 90, 2.0f);
						player->bullet[i]->Angle = start_angle;
						*/
						player->bullet[i]->ORBIT_START(i, player->ORBIT_NUM_return(), 100.0f, 0.0005f); // 半径100で回転
					}
				}
				else if (select->OUT_SELECT_NUM() == 10) {
					player->attack->Flag_INIT();
					player->attack->MINE_Flag = true;
				}
				else if (select->OUT_SELECT_NUM() == 11) {
					player->attack->Flag_INIT();
				}
				else if (select->OUT_SELECT_NUM() == 12) {
					player->attack->Flag_INIT();
				}
				else if (select->OUT_SELECT_NUM() == 13) {
					player->attack->Flag_INIT();
				}
				else if (select->OUT_SELECT_NUM() == 14) {
					player->attack->Flag_INIT();
				}
				else if (select->OUT_SELECT_NUM() == 15) {
					player->attack->Flag_INIT();
				}
				else if (select->OUT_SELECT_NUM() == 16) {
					player->attack->Flag_INIT();

				}
				game_scene->game_state = game_scene->PLAY;
				boss->BOSS_Spawn_Flag = true;
				player->Player_INIT();
				for (int i = 0; i < 50; i++) {
					enemy[i]->ENEMY_RESPORN(enemy[i]);
				}
			}
		}
		if (game_scene->game_state == game_scene->PLAY) {
			clear(0);
			player->Player_Angle_Change();
			player->Player_MOVE();
			if (player->attack->Long_Range_Flag == true) {
				if (isTrigger(MOUSE_LBUTTON)) {
					player->BULLET_To_Mouse();
				}
			}
			if (player->attack->Laser_Flag == true) {
				if (isTrigger(MOUSE_RBUTTON)) {
					player->LASER_To_Mouse();
				}
			}
			if (player->attack->Bounce_Flag == true) {
				if (isTrigger(KEY_Q)) {
					player->BULLET_To_Mouse();
				}
			}
			if (player->attack->Random_Flag == true) {
				if (isTrigger(KEY_E)) {
					player->BULLET_To_Mouse();
				}
			}
			if (player->attack->MINE_Flag == true) {
				//for (int i = 0; i < 10; i++) {
				if (isTrigger(KEY_C)) {
					player->bullet[0]->MINE_USE(player->bullet);
				}
				//}
			}
			map->MOVE_CAMERA(player);
			//map->DRAW_BUG();
			for (int i = 0; i < 50; i++) {
				enemy[i]->Despone(enemy[i], false);
				enemy[i]->Spawn_Enemy(enemy[i]);
				enemy[i]->Go_Player(enemy[i]);
				/*
				if (player_status->Exp_System(enemy[i]) == true) {
					//attack->LEVEL_UP();
				}
				*/
			}
			boss->Spawn_BOSS(boss);
			boss->Go_Player_BOSS(boss);
			for (int i = 0; i < 50; i++) {
				if (player->attack->Melee_Flag == true) {
					player->attack->Melee_Attack(enemy[i]);
				}
				if (player->attack->Range_Flag == true) {
					player->attack->Range_Attack(enemy[i]);
				}
				if (player->attack->Mouse_Flag == true) {
					player->attack->Mouse_Attack(enemy[i]);
				}
			}
			if (player->attack->Boom_Flag == true) {
				player->attack->Boom_Attack(enemy);
			}
			if (boss->BOSS_Spawn_Flag == false) {
				if (player->attack->Melee_Flag == true) {
					player->attack->Melee_Attack_BOSS(boss);
				}
				if (player->attack->Range_Flag == true) {
					player->attack->Range_Attack_BOSS(boss);
				}
				if (player->attack->Mouse_Flag == true) {
					player->attack->Mouse_Attack_BOSS(boss);
				}
				if (player->attack->Boom_Flag == true) {
					player->attack->Boom_Attack_BOSS(boss);
				}
				//player->attack->Boom_HP_Flag_False();
			}
			//player->attack->Boom_HP_Flag_False();

			if (player->attack->Long_Range_Flag == true) {
				for (int i = 0; i < 32; i++) {
					for (int j = 0; j < 50; j++) {
						player->bullet[i]->BULLET_MOVE_and_DRAW(enemy[j]);
					}
					if (boss->BOSS_Spawn_Flag == false) {
						player->bullet[i]->BULLET_MOVE_and_DRAW_for_BOSS(boss);
					}
				}
			}
			if (player->attack->Laser_Flag == true) {
				for (int i = 0; i < 25; i++) {
					for (int j = 0; j < 50; j++) {
						player->bullet[0]->LASER_MOVE_and_DRAW(enemy[j]);
					}
					if (boss->BOSS_Spawn_Flag == false) {
						player->bullet[0]->LASER_MOVE_and_DRAW_for_BOSS(boss);
					}
				}
			}
			if (player->attack->Bounce_Flag == true) {
				for (int i = 0; i < 32; i++) {
					for (int j = 0; j < 50; j++) {
						player->BOUNCE_To_ENEMY(enemy[j]);
						player->bullet[i]->BOUNCE_MOVE_and_DRAW(enemy[j]);
					}
					if (boss->BOSS_Spawn_Flag == false) {
						player->bullet[i]->BOUNCE_MOVE_and_DRAW_for_BOSS(boss);
					}
				}
			}
			if (player->attack->Random_Flag == true) {
				for (int i = 0; i < 15; i++) {
					player->RANDOM_To_Random();
					for (int j = 0; j < 50; j++) {
						player->bullet[i]->RANDOM_MOVE_and_DRAW(enemy[j]);
					}
					if (boss->BOSS_Spawn_Flag == false) {
						player->bullet[i]->RANDOM_MOVE_and_DRAW_for_BOSS(boss);
					}
				}
			}
			if (player->attack->Orbit_Flag == true) {//............Orbit.
				for (int i = 0; i < player->ORBIT_NUM_return(); i++) {
					for (int j = 0; j < 50; j++) {
						player->bullet[i]->ORBIT_MOVE_and_DRAW(enemy[j]);
					}
					if (boss->BOSS_Spawn_Flag == false) {
						player->bullet[i]->ORBIT_MOVE_and_DRAW_for_BOSS(boss);
					}
				}
			}
			if (player->attack->MINE_Flag == true) {
				for (int i = 0; i < 10; i++) {
					//player->bullet[i]->MINE_INIT();
					player->bullet[i]->MINE_MOVE();
					for (int j = 0; j < 50; j++) {
						if (player->bullet[i]->MINE_JUDGE_and_DRAW(enemy[j])) {
							player->bullet[i]->MINE_damege(enemy);
						}
					}
					if (boss->BOSS_Spawn_Flag == false) {
						if (player->bullet[i]->MINE_JUDGE_and_DRAW_for_BOSS(boss)) {
							player->bullet[i]->MINE_damege_for_BOSS(boss);
						}
					}
				}
			}
			player->Player_DRAW();
			player->player_status->DRAW_EXP();
			for (int i = 0; i < 50; i++) {
				enemy[i]->DRAW_ENEMY(enemy[i]);
				enemy[i]->DRAW_ENEMY_HP(enemy[i]);
				player->PLAYER_DAMAGE_and_DRAW(enemy[i]);
			}
			boss->DRAW_BOSS(boss);
			player->PLAYER_DAMAGE_and_DRAW_for_BOSS(boss);
			if (boss->BOSS_Spawn_Flag == false) {
				if (player->player_status->Exp_System_for_BOSS(boss) == true) {
					boss->BOSS_LEVELUP(boss);
				}
			}
			for (int i = 0; i < 50; i++) {
				if (player->player_status->Exp_System(enemy[i])) {
					enemy[i]->ENEMY_LEVELUP(enemy[i]);
				}
			} 
			/*
			if (player->player_status->Exp_System(enemy[i]) == true) {
				player->player_status->Set_LEVELUP_Flag(true);
				//player->player_status->LEVELUP_Flag();
			}
			*/
			if (player->player_status->LEVELUP_Flag() == true) {
				player->LEVEL_UP();
			}

			if (player->player_status->LEVELUP_Flag() == true) {
				player->LEVEL_UP_STATUS();
				player->player_status->Set_LEVELUP_Flag(false);
				//player->player_status->LEVELUP_Finish();
			}
			/*
			for (int i = 0; i < 50; i++) {
				if (boss->BOSS_Spawn_Flag == false) {
					if (player->player_status->Exp_System_for_BOSS(boss)) {
						boss->BOSS_LEVELUP(boss);
						for (int j = 0; j < 50; j++) {
							enemy[j]->ENEMY_LEVELUP(enemy[j]);
						}
					}
				}

				// 通常敵の経験値処理
				if (player->player_status->Exp_System(enemy[i])) {
					player->player_status->Set_LEVELUP_Flag(true);
				}
			}

			// レベルアップが起きた場合のみ処理
			if (player->player_status->LEVELUP_Flag()) {
				player->LEVEL_UP();
				player->player_status->Set_LEVELUP_Flag(false);
			}
			*/


			player->player_status->DRAW_EXP();
			player->DEBUG_TEXT();
			if (map->DRAW_TEXT() == 1) {
				game_scene->game_state = game_scene->INIT;
				for (int i = 0; i < 50; i++) {
					enemy[i]->Despone(enemy[i], true);
					enemy[i]->Spawn_Enemy(enemy[i]);
				}
			}
			else if (map->DRAW_TEXT() == 2) {
				game_scene->game_state = game_scene->OPTION;
			}
			fill(255);
			//text("ENTERキーでメニューに戻る", 0, 1080);
			if (isTrigger(KEY_ENTER)) {
				main()->backToMenu();
			}
			if (player->JUDGE_GAME_OVER()) {
				game_scene->game_state = game_scene->GAMEOVER;
			}
		}
		if (game_scene->game_state == game_scene->GAMEOVER) {
			clear(0);
			if (isTrigger(KEY_ENTER)) {
				main()->backToMenu();
			}
			map->MOVE_CAMERA(player);
			for (int i = 0; i < 50; i++) {
				enemy[i]->DRAW_ENEMY(enemy[i]);
				enemy[i]->DRAW_ENEMY_HP(enemy[i]);
			}
			fill(0);
			textSize(100);
			text("GAME_OVER!", 200, 200);
			text("_RESTART_", 200, 350);
			text("Press_SPACE", 200, 500);
			if (isTrigger(KEY_SPACE)) {
				game_scene->game_state = game_scene->SELECT;
			}
		}
	}
}
//ボスを倒したら敵強くなる.
