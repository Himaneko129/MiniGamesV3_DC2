#include "../../libOne/inc/libOne.h"
#include "GAME11.h"
#include"PLAYER_and_NPC.h"
#include<time.h>
#include<chrono>
namespace GAME11 {
	void BOSS::BOSS_INIT(BOSS* boss) {
		/*
		boss->SPEED = 1;
		boss->Width = 300;
		boss->HP = 20;
		save_HP = boss->HP;
		save_SPEED=boss->SPEED;
		*/
		SPEED = 1;
		Width = 300;
		HP = 20;
		save_HP = HP;
		save_SPEED = SPEED;
		boss_Level = 0;
		Spawn_time = 0;
		Spawn_Count = 0;
	}
	void BOSS::Spawn_BOSS(BOSS* boss) {
		if (boss->BOSS_Spawn_Flag == true) {
			boss->Spawn_time++;
			if (boss->Spawn_time > 10) {
				boss->Spawn_Count++;
				boss->Spawn_time = 0;
				if (boss->Spawn_Count > 60) {
					boss->Spawn_Count = 0;
					boss->BOSS_Spawn_Flag = false;
					boss->HP = save_HP;
					boss->MAX_HP = boss->HP;
					switch (rand() % 4) {
					case 0:
						boss->X = (float)(Yoko);
						boss->Y = (float)(Tate / 2);
						break;
					case 1:
						boss->X = (float)(Yoko / 2);
						boss->Y = (float)(Tate);
						break;
					case 2:
						boss->X = 0.0f;
						boss->Y = (float)(Tate / 2);
						break;
					case 3:
						boss->X = (float)(Yoko / 2);
						boss->Y = 0.0f;
						break;
					default:
						break;
					}
				}
			}
		}
		else {
			if (HP <= 0) {
				boss->BOSS_Spawn_Flag = true;
			}
		}
	}
	void BOSS::Go_Player_BOSS(BOSS* boss) {
		if (boss->BOSS_Spawn_Flag == false) {
			float dX = (Yoko / 2) - boss->X;
			float dy = (Tate / 2) - boss->Y;
			float dist = (float)sqrt(dX * dX + dy * dy);
			if (dist > 0) {
				/*
				enemy->boss->X += (((dboss->X / dist) * SPEED) / 2)+Player_boss->X;
				enemy->Y += (((dy / dist) * SPEED) / 2)+Player_Y;
				*/
				fill(0);
				//text((((dX / dist) * boss->SPEED) / 0.5f), 300, 800);
				boss->X += (((dX / dist) * boss->SPEED) / 0.5f);
				boss->Y += (((dy / dist) * boss->SPEED) / 0.5f);
				if (isPress(KEY_W)) { boss->Y -= -3; }
				if (isPress(KEY_A)) { boss->X -= -3; }
				if (isPress(KEY_S)) { boss->Y -= 3; }
				if (isPress(KEY_D)) { boss->X -= 3; }
			}
		}
	}
	void PLAYER::PLAYER_DAMAGE_and_DRAW_for_BOSS(BOSS* boss) {
		if (boss->HP < 0)return;

	    float distX = (Yoko/2) - boss->X;
		float distY = (Tate/2) - boss->Y;
		float distance = sqrt(distX * distX + distY * distY);
		if (distance < 140) {
			HP -= 20;
		}
		/*
		if (((HP / MAX_HP) * 100) <= 25) {
			fill(255, 0, 0);
		}
		else if (((HP / MAX_HP) * 100) <= 50) {
			fill(255, 255, 0);
		}
		else {
			fill(0, 255, 0);
		}
		if (!(HP < 0)) {
			rect(Yoko / 2, (Tate / 2) - 20, (HP / MAX_HP) * 50, 10);
		}
		*/

	}
	void BOSS::DRAW_BOSS(BOSS* boss) {
		DRAW_BOSS_HP(boss);
		fill(0, 255, 0);
		//text(boss->BOSS_Spawn_Flag, 300, 500);
		//text(boss->Spawn_time, 300, 600);
		//text(boss->Spawn_Count, 300, 700);
		if (boss->BOSS_Spawn_Flag == false) {
			if (rand() % 30 == 0) {
				if (rand() % (30 / 2) == 0) {
					fill(0, 255, 0);
				}
				else if (rand() % (30 / 2) == 1) {
					fill(0, 0, 255);
				}
				else { fill(255, 0, 0); }
			}
			else {
				fill(255, 0, 0);
			}
			circle(boss->X, boss->Y, (float)Width);
		}
	}
	void BOSS::DRAW_BOSS_HP(BOSS* boss) {
		fill(255);
		rect((Yoko / 2) - 300, Tate - 30, boss->MAX_HP, 20);
		if (((boss->HP / boss->MAX_HP) * 100) <= 25) {
			fill(255, 0, 0);
		}
		else if (((boss->HP / boss->MAX_HP) * 100) <= 50) {
			fill(255, 255, 0);
		}
		else {
			fill(0, 255, 0);
		}
		if (!(boss->HP < 0)) {
			rect((Yoko / 2) - 150, Tate - 30, (boss->HP / boss->MAX_HP) * 300, 20);
		}
		fill(0);
		//text((HP / MAX_HP) * 100, 300, 400);
	}
	void BOSS::BOSS_LEVELUP(BOSS* boss) {
		boss->boss_Level++;
		save_HP = (float)((boss->HP) + (boss->boss_Level * 4));
	}
	void ATTACK::Melee_Attack_BOSS(BOSS* boss) {
		if (Melee_Flag == true) {
			if (isTrigger(KEY_SPACE)) {
				Center_X = Yoko / 2; Center_Y = Tate / 2;
				//duration = 10; //
				float dx = Center_X - boss->X;
				float dy = Center_Y - boss->Y;
				float dist = (float)sqrt(dx * dx + dy * dy);
				if (dist < range * 3) {
					boss->HP -= Attack_Power;
				}
				fill(255, 0, 0);
				circle(Center_X, Center_Y, range * 2);
			}
		}
	}
	void ATTACK::Range_Attack_BOSS(BOSS* boss) {
		fill(255, 0, 0);
		rectMode(CENTER);
		angleMode(DEGREES);
		if (Range_Flag == true) {
			if (isTrigger(KEY_SHIFT)) {
				if (isPress(KEY_W)) {
					if (isPress(KEY_D)) {
						Center_X = (Yoko / 2) + 25;
						Center_Y = (Tate / 2) - 25;
						Center_2_X = (Yoko / 2) + 50;
						Center_2_Y = (Tate / 2) - 50;
						Center_3_X = (Yoko / 2) + 75;
						Center_3_Y = (Tate / 2) - 75;
						rect(Yoko / 2 + 50, Tate / 2 - 50, range / 2, (range / 2) * 3, 45);
					}
					else if (isPress(KEY_A)) {
						Center_X = (Yoko / 2) - 25;
						Center_Y = (Tate / 2) - 25;
						Center_2_X = (Yoko / 2) - 50;
						Center_2_Y = (Tate / 2) - 50;
						Center_3_X = (Yoko / 2) - 75;
						Center_3_Y = (Tate / 2) - 75;
						rect(Yoko / 2 - 50, Tate / 2 - 50, range / 2, (range / 2) * 3, 315);
					}
					else {
						Center_X = Yoko / 2;
						Center_Y = (Tate / 2) - 25;
						Center_2_X = Yoko / 2;
						Center_2_Y = (Tate / 2) - 50;
						Center_3_X = Yoko / 2;
						Center_3_Y = (Tate / 2) - 75;
						rect(Yoko / 2, Tate / 2 - 50, range / 2, (range / 2) * 3, 0);
					}
				}
				else if (isPress(KEY_A)) {
					if (isPress(KEY_W)) {
						Center_X = (Yoko / 2) - 25;
						Center_Y = (Tate / 2) - 25;
						Center_2_X = (Yoko / 2) - 50;
						Center_2_Y = (Tate / 2) - 50;
						Center_3_X = (Yoko / 2) - 75;
						Center_3_Y = (Tate / 2) - 75;
						rect(Yoko / 2 - 50, Tate / 2 - 50, range / 2, (range / 2) * 3, 315);
					}
					else if (isPress(KEY_S)) {
						Center_X = (Yoko / 2) - 25;
						Center_Y = (Tate / 2) + 25;
						Center_2_X = (Yoko / 2) - 50;
						Center_2_Y = (Tate / 2) + 50;
						Center_3_X = (Yoko / 2) - 75;
						Center_3_Y = (Tate / 2) + 75;
						rect(Yoko / 2 - 50, Tate / 2 + 50, range / 2, (range / 2) * 3, 225);
					}
					else {
						Center_X = (Yoko / 2) - 25;
						Center_Y = (Tate / 2);
						Center_2_X = (Yoko / 2) - 50;
						Center_2_Y = (Tate / 2);
						Center_3_X = (Yoko / 2) - 75;
						Center_3_Y = (Tate / 2);
						rect(Yoko / 2 - 50, Tate / 2, range / 2, (range / 2) * 3, 270);
					}
				}
				else if (isPress(KEY_S)) {
					if (isPress(KEY_D)) {
						Center_X = (Yoko / 2) + 25;
						Center_Y = (Tate / 2) + 25;
						Center_2_X = (Yoko / 2) + 50;
						Center_2_Y = (Tate / 2) + 50;
						Center_3_X = (Yoko / 2) + 75;
						Center_3_Y = (Tate / 2) + 75;
						rect(Yoko / 2 + 50, Tate / 2 + 50, range / 2, (range / 2) * 3, 135);
					}
					else if (isPress(KEY_A)) {
						Center_X = (Yoko / 2) - 25;
						Center_Y = (Tate / 2) + 25;
						Center_2_X = (Yoko / 2) - 50;
						Center_2_Y = (Tate / 2) + 50;
						Center_3_X = (Yoko / 2) - 75;
						Center_3_Y = (Tate / 2) + 75;
						rect(Yoko / 2 - 50, Tate / 2 + 50, range / 2, (range / 2) * 3, 225);
					}
					else {
						Center_X = Yoko / 2;
						Center_Y = (Tate / 2) + 25;
						Center_2_X = Yoko / 2;
						Center_2_Y = (Tate / 2) + 50;
						Center_3_X = Yoko / 2;
						Center_3_Y = (Tate / 2) + 75;
						rect(Yoko / 2, Tate / 2 + 50, range / 2, (range / 2) * 3, 180);
					}

				}
				else if (isPress(KEY_D)) {
					if (isPress(KEY_W)) {
						Center_X = (Yoko / 2) + 25;
						Center_Y = (Tate / 2) - 25;
						Center_2_X = (Yoko / 2) + 50;
						Center_2_Y = (Tate / 2) - 50;
						Center_3_X = (Yoko / 2) + 75;
						Center_3_Y = (Tate / 2) - 75;
						rect(Yoko / 2 + 50, Tate / 2 - 50, range / 2, (range / 2) * 3, 45);
					}
					else if (isPress(KEY_S)) {
						Center_X = (Yoko / 2) + 25;
						Center_Y = (Tate / 2) + 25;
						Center_2_X = (Yoko / 2) + 50;
						Center_2_Y = (Tate / 2) + 50;
						Center_3_X = (Yoko / 2) + 75;
						Center_3_Y = (Tate / 2) + 75;
						rect(Yoko / 2 + 50, Tate / 2 + 50, range / 2, (range / 2) * 3, 135);
					}
					else {
						Center_X = (Yoko / 2) + 25;
						Center_Y = (Tate / 2);
						Center_2_X = (Yoko / 2) + 50;
						Center_2_Y = (Tate / 2);
						Center_3_X = (Yoko / 2) + 75;
						Center_3_Y = (Tate / 2);
						rect(Yoko / 2 + 50, Tate / 2, range / 2, (range / 2) * 3, 90);
					}

				}
				float dx_1 = Center_X - boss->X;
				float dy_1 = Center_Y - boss->Y;
				float dist_1 = (float)sqrt(dx_1 * dx_1 + dy_1 * dy_1);
				float dx_2 = Center_2_X - boss->X;
				float dy_2 = Center_2_Y - boss->Y;
				float dist_2 = (float)sqrt(dx_2 * dx_2 + dy_2 * dy_2);
				float dx_3 = Center_3_X - boss->X;
				float dy_3 = Center_3_Y - boss->Y;
				float dist_3 = (float)sqrt(dx_3 * dx_3 + dy_3 * dy_3);
				if (dist_1 < (range * 3) || dist_2 < (range * 3) || dist_3 < (range * 3)) {
					boss->HP -= Attack_Power;
				}
			}
		}
		rectMode(CORNER);
	}
	//敵が死ににくい瞬間あり.
	void ATTACK::Boom_Attack_BOSS(BOSS* boss) {
		//fill(255);
		//circle(Center_X, Center_Y, 50);
	//	if (Boom_HP == true) {
		float dx = mouseX - Center_X;
		float dy = mouseY - Center_Y;

		// ベクトル正規化
		float length = (float)sqrt(dx * dx + dy * dy);
		float Vector_X = dx / length;
		float Vector_Y = dy / length;

		//	Center_X += Vector_X *= 0.1f;
			//Center_Y += Vector_Y *= 0.1f;
			//enemy_distance and mouse_distance.
		float dist_x = Center_X - mouseX;
		float dist_y = Center_Y - mouseY;
		float dist = (float)sqrt(dist_x * dist_x + dist_y * dist_y);
		if (Boom_HP_for_BOSS == true) {
		//	if (dist < 15) {
				float distance_x = Center_X - boss->X;
				float distance_y = Center_Y - boss->Y;
				float distance = (float)sqrt(distance_x * distance_x + distance_y * distance_y);
				Boom_HP_for_BOSS = false;
				if (distance < (range * 2) * 2) {
					fill(255, 0, 0);
					circle(Center_X, Center_Y, 200 * 2);
					boss->HP -= Attack_Power;
				//	boss->HP = 0;
				}
			//}
		}
		//}
	}

	void ATTACK::Mouse_Attack_BOSS(BOSS* boss) {
		if (isTrigger(KEY_W) || isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {
			//duration = 10; //
			float dx = mouseX - boss->X;
			float dy = mouseY - boss->Y;
			float dist = (float)sqrt(dx * dx + dy * dy);
			if (dist < ((range * 3) / 1.5)) {
				boss->HP -= Attack_Power;
			}
			fill(255, 0, 0);
			circle(mouseX, mouseY, (range / 1.5f) * 2);
		}
	}
	void BULLET::BOUNCE_MOVE_and_DRAW_for_BOSS(BOSS* boss) {
		//for (int i = 0; i < 32; i++) {
		if (HP == true) {
			Bullet_X += Bullet_Vector_X * (BulletSpeed / 1.5f);
			Bullet_Y += Bullet_Vector_Y * (BulletSpeed / 1.5f);

			float dx = Bullet_X - boss->X;
			float dy = Bullet_Y - boss->Y;
			float dist = (float)sqrt(dx * dx + dy * dy);
			if (dist < 175) {
				boss->HP -= Bullet_Power;
				bounce_F = true;
				HP = 0;
			}
			// 画面外に出たら消す
			if (Bullet_X < -100 || Bullet_X > 2000 || Bullet_Y < -100 || Bullet_Y > 1200) {
				HP = 0;
				bounce_F = false;
			}

			fill(0, 0, 255); // 黄色い弾
			rect(Bullet_X, Bullet_Y, 15, 15);

		}
		//	}
	}

	void BULLET::BULLET_MOVE_and_DRAW_for_BOSS(BOSS* boss) {
		//for (int i = 0; i < 32; i++) {
		if (HP == true) {
			Bullet_X += Bullet_Vector_X * BulletSpeed;
			Bullet_Y += Bullet_Vector_Y * BulletSpeed;

			float dx = Bullet_X - boss->X;
			float dy = Bullet_Y - boss->Y;
			float dist = (float)sqrt(dx * dx + dy * dy);
			if (dist < 175) {
				boss->HP -= Bullet_Power;
				HP = 0;
			}
			// 画面外に出たら消す
			if (Bullet_X < -100 || Bullet_X > 2000 || Bullet_Y < -100 || Bullet_Y > 1200) {
				HP = 0;
			}

			fill(0, 0, 255); // 黄色い弾
			rect(Bullet_X, Bullet_Y, 10, 10);

		}
		//	}
	}
	void BULLET::LASER_MOVE_and_DRAW_for_BOSS(BOSS* boss) {
		//for (int i = 0; i < 32; i++) {
		if (HP == true) {
			Bullet_X += Bullet_Vector_X * BulletSpeed;
			Bullet_Y += Bullet_Vector_Y * BulletSpeed;

			float dx = Bullet_X - boss->X;
			float dy = Bullet_Y - boss->Y;
			float dist = (float)sqrt(dx * dx + dy * dy);
			if (dist < 175) {
				boss->HP -= Bullet_Power;
				HP = 0;
			}
			// 画面外に出たら消す
			if (Bullet_X < -100 || Bullet_X > 2000 || Bullet_Y < -100 || Bullet_Y > 1200) {
				HP = 0;
			}

			fill(0, 0, 255); // 黄色い弾
			rect(Bullet_X, Bullet_Y, 10, 10);
		}
		//}
	}
	void BULLET::RANDOM_MOVE_and_DRAW_for_BOSS(BOSS* boss) {
		//for (int i = 0; i < 32; i++) {
		if (HP == true) {
			Bullet_X += Bullet_Vector_X * (BulletSpeed * 0.1f);
			Bullet_Y += Bullet_Vector_Y * (BulletSpeed * 0.1f);

			float dx = Bullet_X - boss->X;
			float dy = Bullet_Y - boss->Y;
			float dist = (float)sqrt(dx * dx + dy * dy);
			if (dist < 180) {
				boss->HP -= Bullet_Power;
				HP = 0;
			}
			// 画面外に出たら消す
			if (Bullet_X < -100 || Bullet_X > 2000 || Bullet_Y < -100 || Bullet_Y > 1200) {
				HP = 0;
			}

			fill(0, 0, 255); // 黄色い弾
			rect(Bullet_X, Bullet_Y, 30, 30);

		}
		//	}
	}
	void BULLET::ORBIT_MOVE_and_DRAW_for_BOSS(BOSS* boss) {
		if (!HP) return;

		// 中心をプレイヤーの座標に設定
		float centerX = Yoko / 2.0f;
		float centerY = Tate / 2.0f;

		// 回転更新
		Angle += angle_increment;
		if (Angle > 2 * PI) Angle -= 2 * PI;

		// 座標更新
		Bullet_X = centerX + (float)cos(Angle) * radius;
		Bullet_Y = centerY + (float)sin(Angle) * radius;

		// 当たり判定（オプション）
		if (boss != nullptr) {
			float dx = boss->X - (Bullet_X + 25);
			float dy = boss->Y - (Bullet_Y + 25);
			float dist = (float)sqrt(dx * dx + dy * dy);
			if (dist < 165) {
				boss->HP -= Bullet_Power;
			}
		}

		// 描画
		fill(0, 0, 255);
		circle(Bullet_X + 25, Bullet_Y + 25, 6);

		//if (Angle > 360.0f) Angle -= 360.0f;
	}
	/*
	void BULLET::MINE_DRAW_for_BOSS(BOSS*boss) {
		if (HP == false) {  // 死んでる弾を再利用
			HP = true;  // 生きてる状態にする
			//enemy_distance and mouse_distance.
			float dist_x = Bullet_X - Yoko / 2;
			float dist_y = Bullet_Y - Tate / 2;
			float dist = (float)sqrt(dist_x * dist_x + dist_y * dist_y);
			if (dist < 15 && HP == true) {
				float distance_x = Bullet_X - boss->X;
				float distance_y = Bullet_Y - boss->Y;
				float distance = (float)sqrt(distance_x * distance_x + distance_y * distance_y);
				if (distance < 250*3) {
					fill(255, 0, 0);
					circle(Bullet_X, Bullet_Y, 250 * 2);
					boss->HP -= Bullet_Power;
					boss->HP = 0;
				}
			}
		}
		//break; // 1発だけ
	}
	*/
	bool BULLET::MINE_JUDGE_and_DRAW_for_BOSS(BOSS* boss) {
		if (HP == true) {
			float dist_x = Bullet_X - boss->X;
			float dist_y = Bullet_Y - boss->Y;
			float dist = (float)sqrt(dist_x * dist_x + dist_y * dist_y);
			fill(0, 0, 255);
			circle(Bullet_X, Bullet_Y, 30 * 2);
			if (dist < 150 && HP == true) {
				MINE_damege_Flag = true;
				return true;
			}
			else {
				return false;
			}
		}
	}
	void BULLET::MINE_damege_for_BOSS(BOSS* boss) {
		float distance_x = Bullet_X - boss->X;
		float distance_y = Bullet_Y - boss->Y;
		float distance = (float)sqrt(distance_x * distance_x + distance_y * distance_y);
		if (distance < 250) {
			fill(255, 0, 0);
			circle(Bullet_X, Bullet_Y, 300 * 2);
			boss->HP -= Bullet_Power;
			boss->HP = 0;
			HP = false;

		}
		MINE_damege_Flag = false;
	}
}