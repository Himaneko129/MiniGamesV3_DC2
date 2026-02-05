#include "../../libOne/inc/libOne.h"
#include "GAME11.h"
#include"PLAYER_and_NPC.h"
#include<time.h>
#include<chrono>
namespace GAME11 {
	void PLAYER::Player_INIT() {
		X = Yoko / 2;
		Y = Tate / 2;
		Player_Width = 30;
		Player_Height = 45;
		orbit_num = 2;
		lastBulletBonusLevel = 0;
		MAX_HP = 500;
		HP = MAX_HP;
	}
	void PLAYER::RANDOM_SET() {
		srand((unsigned int)time(0));
	}
	void PLAYER::Like_a_BUG(int percent, int color, int pattern) {
		int BUG_Flag = 0;
		BUG_X = 0; BUG_Y = 0;
		if (rand() % percent == 0) {
			if (rand() % (percent / 2) == 0) {
				fill(255, 0, 0); BUG_Flag = 1;
			}
			else if (rand() % (percent / 2) == 1) {
				fill(0, 255, 0); BUG_Flag = 1;
			}
			else if (rand() % (percent / 2) == 2) {
				fill(0, 0, 255); BUG_Flag = 1;
			}
			else { fill((float)color); }
		}
		else {
			fill((float)color);
		} if (pattern == 1 && BUG_Flag == 1) {
			if (rand() % 3 == 0) {
				BUG_X += 5;
			} if (rand() % 3 == 1) {
				BUG_X -= 5;
			} if (rand() % 3 == 2) {
				BUG_Y += 5;
			} if (rand() % 3 == 3) {
				BUG_Y -= 5;
			}
		}
	}
	void PLAYER::Player_MOVE() {
		Vector_X_Flag = 0; Vector_Y_Flag = 0;
		if (isPress(KEY_W)) {
			Y += -3;
			//Vector_Y_Flag = -1;
		}
		if (isPress(KEY_A)) {
			X += -3;
			//Vector_X_Flag = -1;
		}
		if (isPress(KEY_S)) {
			Y += 3;
			//Vector_Y_Flag = 1;
		}
		if (isPress(KEY_D)) {
			X += 3;
			//Vector_X_Flag = 1;
		}
	}
	void PLAYER::Player_Angle_Change() {
		if (isPress(KEY_W)) {
			if (isPress(KEY_D)) {
				Angle = 45;
			}
			else if (isPress(KEY_A)) {
				Angle = 315;
			}
			else {
				Angle = 0;
			}
		}
		if (isPress(KEY_A)) {
			if (isPress(KEY_W)) {
				Angle = 315;
			}
			else if (isPress(KEY_S)) {
				Angle = 225;
			}
			else {
				Angle = 270;;
			}

		}
		if (isPress(KEY_S)) {
			if (isPress(KEY_D)) {
				Angle = 135;
			}
			else if (isPress(KEY_A)) {
				Angle = 225;
			}
			else {
				Angle = 180;
			}

		}
		if (isPress(KEY_D)) {
			if (isPress(KEY_W)) {
				Angle = 45;
			}
			else if (isPress(KEY_S)) {
				Angle = 135;
			}
			else {
				Angle = 90;
			}

		}
	}
	void PLAYER::Player_DRAW() {
		rectMode(CENTER);
		fill(1);//arc.arrow,shape 
		Like_a_BUG(16, 0, 1);

		rect(((Yoko / 2) + BUG_X) + 10, ((Tate / 2) + BUG_Y) + 10, (float)Player_Width, (float)Player_Height, Angle);
		// //fill(255,0,0); strokeWeight(10); //剣の攻撃判定. //arc(mouseX,mouseY, a, b, c); // 銃の攻撃判定. //arrow((Yoko / 2) - (Player_Yoko / 2), (Tate / 2) - (Player_Tate / 2), mouseX, mouseY, 30);
		noStroke();
		rectMode(CORNER);
	}
	/*
void Player::Attack() {
switch (attackType) {
case SINGLE_SHOT:
bullets.push_back(Bullet(x, y, 0, -bulletSpeed));
break;
case DOUBLE_SHOT:
bullets.push_back(Bullet(x - 5, y, 0, -bulletSpeed));
bullets.push_back(Bullet(x + 5, y, 0, -bulletSpeed));
break; case SPREAD_SHOT:
bullets.push_back(Bullet(x, y, -2, -bulletSpeed));
bullets.push_back(Bullet(x, y, 0, -bulletSpeed));
bullets.push_back(Bullet(x, y, 2, -bulletSpeed));
break;
case AUTO_ORBIT: // プレイヤーの周りに角度をずらして弾を配置
for (int i = 0; i < 4; i++)
float angle = (frameCount / 10.0f) + i * M_PI / 2;
bullets.push_back(Bullet(x + cos(angle) * 40, y + sin(angle) * 40, 0, 0, true));
} break;
}
}
*/
	void PLAYER::PLAYER_DAMAGE_and_DRAW(ENEMY* enemy) {
		if (enemy->HP < 0)return;
		float distX = (Yoko/2) - enemy->X;
		float distY = (Tate/2) - enemy->Y;
		float distance = sqrt(distX * distX + distY * distY);
		if (distance < 40) {
			HP-=5;
		}
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
			rect(Yoko/2, (Tate/2) - 20, (HP / MAX_HP) * 50, 10);
		}
	}
	bool PLAYER::JUDGE_GAME_OVER() {
		if (HP < 0) {
			return true;
		}
		return false;
	}
	void ENEMY::ENEMY_INIT(ENEMY* enemy) {
		enemy->HP = 10;
		enemy->SPEED = 1;
		save_HP = enemy->HP;
		save_SPEED = enemy->SPEED;
		enemy->MAX_HP = enemy->HP;
	}
	void ENEMY::ENEMY_RESPORN(ENEMY* enemy) {
		enemy->HP = 0;
	}
	void ENEMY::Spawn_Enemy(ENEMY* enemy) {
		if (enemy->HP <= 0) {
			enemy->HP = save_HP;
			enemy->save_SPEED = save_SPEED;
			enemy->MAX_HP = enemy->HP;
			int yoko = Yoko;
			int tate = Tate;
			switch (rand() % 4) {
			case 0:
				enemy->X = (float)(rand() % yoko);
				enemy->Y = (float)(rand() % tate / 2);
				break;
			case 1:
				enemy->X = (float)(rand() % yoko / 2);
				enemy->Y = (float)(rand() % tate);
				break;
			case 2:
				enemy->X = (float)(rand() % yoko);
				enemy->Y = (float)((rand() % tate / 2) + (tate / 2));
				break;
			case 3:
				enemy->X = (float)((rand() % yoko / 2) + (yoko / 2));
				enemy->Y = (float)(rand() % tate);
				break;
			default:
				break;
			}
		}
	}
	void ENEMY::Go_Player(ENEMY* enemy) {
		float dx = (Yoko / 2) - enemy->X;
		float dy = (Tate / 2) - enemy->Y;
		float dist = (float)sqrt(dx * dx + dy * dy);
		if (dist > 0) {
			/*
			enemy->X += (((dx / dist) * SPEED) / 2)+Player_X;
			enemy->Y += (((dy / dist) * SPEED) / 2)+Player_Y;
			*/
			enemy->X += (((dx / dist) * SPEED) / 2);
			enemy->Y += (((dy / dist) * SPEED) / 2);
			if (isPress(KEY_W)) { enemy->Y -= -3; }
			if (isPress(KEY_A)) { enemy->X -= -3; }
			if (isPress(KEY_S)) { enemy->Y -= 3; }
			if (isPress(KEY_D)) { enemy->X -= 3; }
		}
	}
	void ENEMY::DRAW_ENEMY_HP(ENEMY* enemy) {
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
		rect(enemy->X, enemy->Y - 20, (HP / MAX_HP) * 50, 10);
		}
	}
	void ENEMY::DRAW_ENEMY(ENEMY* enemy) {
		if (enemy->HP > 0) {
			fill(255, 0, 0);
			rect(enemy->X, enemy->Y, 20, 20);
			//DRAW_ENEMY_HP(enemy);
		}
	}
	float Distance(float x1, float y1, float x2, float y2) {
		//float dist = ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1), 0.5);
		return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	}
	void ENEMY::Despone(ENEMY* enemy, bool flag) {
		if (flag == false) {
			if (Distance(enemy->X, enemy->Y, Yoko / 2, Tate / 2) >= Yoko / 2) {
				enemy->HP = 0;
			}
		}
		else if (flag == true) {
			enemy->HP = 0;
		}
	}
	void ENEMY::ENEMY_LEVELUP(ENEMY* enemy) {
		enemy_Level++;
		save_HP = (enemy->HP)+enemy->enemy_Level * 3;
		save_SPEED = enemy->SPEED + (enemy->enemy_Level * 0.1);
	}
	void ATTACK::ATTACK_INIT() {
		//HP = 0; SPEED = 0;
		Attack_Power = 5;
		FireRate = 0;
		// 連射間隔
		range = 100;
		//LEVEL = 0;
	   // EXP = 0;
		//NextExp = 0;
	}
	void ATTACK::Flag_INIT() {
		Melee_Flag = false;
		Mouse_Flag = false;
		Range_Flag = false;
		Long_Range_Flag = false;
		Laser_Flag = false;
		Bounce_Flag = false;
		Boom_Flag = false;
		Boom_HP = false;
		Random_Flag = false;
		Orbit_Flag = false;
		MINE_Flag = false;
	}
	void PLAYER_STATUS::STATUS_INIT() {
		//HP = 0; SPEED = 0;
		Bar_Width = 600;
		LEVEL = 0;
		EXP = 0;
		NextExp = Bar_Width;
		Drawtime = 0;
	}
	void BULLET::BULLET_INIT(PLAYER* player) {
		HP = 0;
		BulletSpeed = 1;
		Bullet_X = 0.0f;
		Bullet_Y = 0.0f;
		Bullet_Vector_X = 0.0f;
		Bullet_Vector_Y = 0.0f;
		Angle = 0.0f;
		Bullet_Power = player->attack->Attack_Power;
		radius = 0;
		angle_increment = 0;
		Bullet_Hit_Flag = false;
	}
	void PLAYER:: ORBIT_BULLET_PLUS(int num) {
		if (orbit_num <= 32) {
			orbit_num = orbit_num + num;
		}
		else {
			orbit_num = 32;
		}
	}

	/*
void PLAYER_STATUS::LevelUp() {
if (EXP >= NextExp) {
LEVEL++; EXP -= NextExp;
NextExp = LEVEL * 20;
// 必要経験値を増やす // レベルアップ時の演出や強化選択をここで呼ぶ }
} */
	bool PLAYER_STATUS::Exp_System(ENEMY* enemy) {
		if (enemy->HP <= 0) {
			EXP += (10+(LEVEL*2));
		} //}
		if (EXP >= NextExp) {
			LEVEL++;
			EXP -= NextExp;
			NextExp = (int)(NextExp * 1.05);
			Draw_Level_Up = true;
			return true;
		}
		else {
			return false;
		}
	}
	bool PLAYER_STATUS::Exp_System_for_BOSS(BOSS* boss) {
		if (boss->HP <= 0) {
			EXP += (100+(LEVEL * 3));
			return true;
		} //}
		else return false;
	}
	void PLAYER::LEVEL_UP() {
		if (player_status->Draw_Level_Up) {
			player_status->Drawtime++;
			textSize(32);
			text("Level UP!", Yoko / 2, Tate / 2);
			if (player_status->Drawtime >= 100) {
				player_status->Draw_Level_Up = false;
				player_status->Drawtime = 0;
			}
		}
	}
	/*
	void PLAYER::LEVEL_UP_STATUS() {
		HP += 10;
		attack->Attack_Power += 5;
		attack->range += 0.2;
		if ((player_status->PLAYER_LEVEL_RETURN() % 5) == 0) {
		textSize(132);
		text("iq3utrvb24t3b!", Yoko / 2, Tate / 2);
			ORBIT_BULLET_PLUS(1);
			int total = ORBIT_NUM_return();
			for (int i = 0; i < total; i++) {
				bullet[i]->ORBIT_START(i, total, 100.0f, 0.0005f);
			}
			//player_status->Set_LEVELUP_Flag(false);
		}
		for (int i = 0; i < 32; i++) {
			bullet[i]->Bullet_Power += 1;
		}
	}
	*/
	void PLAYER::LEVEL_UP_STATUS() {
		HP += 10;
		attack->Attack_Power += 5;
		attack->range += 0.2;

		// これまでに弾を増やした回数を static で保持
		//static int lastBulletBonusLevel = 0;

		int currentLevel = player_status->PLAYER_LEVEL_RETURN();

		// 5レベル上がるたびに1発追加（5,10,15,...で複数レベル上がっても対応）
		int bonusCount = (currentLevel / 5) - (lastBulletBonusLevel / 5);
		if (bonusCount > 0) {
			for (int j = 0; j < bonusCount; j++) {
				ORBIT_BULLET_PLUS(1);
			}
			int total = ORBIT_NUM_return();
			for (int i = 0; i < total; i++) {
				bullet[i]->ORBIT_START(i, total, 100.0f, 0.0005f);
			}
			lastBulletBonusLevel = currentLevel; // 記録更新
		}

		// 攻撃力アップ
		for (int i = 0; i < 32; i++) {
			bullet[i]->Bullet_Power += 1;
		}
	}
	/*
	void PLAYER::LEVEL_UP() {
		HP += 10;
		attack->Attack_Power += 5;
		for (int i = 0; i < 32; i++) {
			bullet[i]->Bullet_Power += 1;
		}
		attack->range += 0.2;

		// ★ レベルが5の倍数ごとにオービット弾を追加
		if ((player_status->PLAYER_LEVEL_RETURN() % 5) == 0) {
			ORBIT_BULLET_PLUS(1);
			for (int i = 0; i < ORBIT_NUM_return(); i++) {
				bullet[i]->ORBIT_START(i, ORBIT_NUM_return(), 100.0f, 0.0005f);
			}
		}

		// ★ ここからは演出部分
		player_status->Draw_Level_Up = true;
		player_status->Drawtime = 0;
	}
	*/
	bool PLAYER_STATUS::LEVELUP_Flag() {
		return LevelUp_Flag;
	}
	void PLAYER_STATUS::Set_LEVELUP_Flag(bool flag) {
		LevelUp_Flag = flag;
	}
	void PLAYER_STATUS::LEVELUP_Finish() {
		if (Draw_Level_Up == false) {
			LevelUp_Flag = false;
		}
	}
	void PLAYER_STATUS::DRAW_EXP() {
		fill(255);
		rect((Yoko / 2) - 300, 30, Bar_Width, 20);//外枠. 
		fill(0, 255, 0);
		rect((Yoko / 2) - 300, 30, (float)((EXP / NextExp) * 100) * 6, 20);//中身. 
		//text(((EXP / NextExp) * 100) * 6, 300, 300);
		textSize(30);
		text("Lv.", (Yoko / 2) - 410, 50);
		text(LEVEL, (Yoko / 2) - 370, 50);
		if (Draw_Level_Up) {
			Drawtime++;
			textSize(32);
			text("Level UP!", Yoko / 2, Tate / 2);
			if (Drawtime >= 100) {
				Draw_Level_Up = false;
				Drawtime = 0;
			}
		}
		//text(EXP, 20, 20);
	}
	int PLAYER_STATUS::PLAYER_LEVEL_RETURN() {
		return LEVEL;
	}
	void ATTACK::Melee_Attack(ENEMY* enemy) {
		if (Melee_Flag == true) {
			if (isTrigger(KEY_SPACE)) {
				Center_X = Yoko / 2; Center_Y = Tate / 2;
				//duration = 10; //
				float dx = Center_X - enemy->X;
				float dy = Center_Y - enemy->Y;
				float dist =(float) sqrt(dx * dx + dy * dy);
				if (dist < range) {
					enemy->HP -= Attack_Power;
				}
				fill(255, 0, 0);
				circle(Center_X, Center_Y, range * 2);
			}
		}
	}
	void ATTACK::Range_Attack(ENEMY* enemy) {
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
				float dx_1 = Center_X - enemy->X;
				float dy_1 = Center_Y - enemy->Y;
				float dist_1 = (float)sqrt(dx_1 * dx_1 + dy_1 * dy_1);
				float dx_2 = Center_2_X - enemy->X;
				float dy_2 = Center_2_Y - enemy->Y;
				float dist_2 = (float)sqrt(dx_2 * dx_2 + dy_2 * dy_2);
				float dx_3 = Center_3_X - enemy->X;
				float dy_3 = Center_3_Y - enemy->Y;
				float dist_3 = (float)sqrt(dx_3 * dx_3 + dy_3 * dy_3);
				if (dist_1 < (range/2) || dist_2 < (range/2) || dist_3 < (range/2)) {
					enemy->HP -= Attack_Power*2;
				}
			}
		}
		rectMode(CORNER);
	}
	void ATTACK::Boom_Center_INIT(){
		Center_X = Yoko / 2;
		Center_Y = Tate / 2;
	}
	//敵が死ににくい瞬間あり.
	void ATTACK::Boom_Attack(ENEMY** enemy) {
		fill(255);
		circle(Center_X, Center_Y, 50);
		//if (Boom_HP == true) {
		float dx = mouseX - Center_X;
		float dy = mouseY - Center_Y;

		// ベクトル正規化
		float length = (float)sqrt(dx * dx + dy * dy);
		float Vector_X = dx / length;
		float Vector_Y = dy / length;

		Center_X += Vector_X *= 3.0f;
		Center_Y += Vector_Y *= 3.0f;
		//enemy_distance and mouse_distance.
		float dist_x = Center_X - mouseX;
		float dist_y = Center_Y - mouseY;
		float dist = (float)sqrt(dist_x * dist_x + dist_y * dist_y);
		if (Boom_HP == true) {
			if (dist < 15) {
				for (int i = 0; i < 50; i++) {
					float distance_x = Center_X - enemy[i]->X;
					float distance_y = Center_Y - enemy[i]->Y;
					float distance = (float)sqrt(distance_x * distance_x + distance_y * distance_y);
					Boom_HP = false;
					if (distance < range * 2) {
						Boom_HP_for_BOSS = true;
						fill(255, 0, 0);
						circle(Center_X, Center_Y, 200 * 2);
						enemy[i]->HP -= Attack_Power;
						//enemy->HP = 0;
					}
				}
			}
		}
		if (15 < dist) {
			Boom_HP = true;
		}
	}
	void ATTACK::Boom_HP_Flag_False() {
				Boom_HP = false;
	}
	void ATTACK::Mouse_Attack(ENEMY* enemy) {
		if (isTrigger(KEY_W) || isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {
			//duration = 10; //
			float dx = mouseX - enemy->X;
			float dy = mouseY - enemy->Y;
			float dist = (float)sqrt(dx * dx + dy * dy);
			if (dist < (range / 1.5)) {
				enemy->HP -= Attack_Power;
			}
			fill(255, 0, 0);
			circle(mouseX, mouseY, (range / 1.5f) * 2);
		}
	}



	//跳弾-敵から敵へ、ランダムに飛び回るやつ、全方位に飛ばすやつ、サークル.
	//,マウスの場所まで行って着いたら爆発.



	void PLAYER::BULLET_To_Mouse() {
		for (int i = 0; i < num; i++) {
			if (bullet[i]->HP == false) {  // 死んでる弾を再利用
				bullet[i]->HP = true;  // 生きてる状態にする
				bullet[i]->bounce_F = true;
				bullet[i]->Bullet_X = Yoko / 2;
				bullet[i]->Bullet_Y = Tate / 2;

				// マウス座標を取得
				float dx = mouseX - Yoko / 2;
				float dy = mouseY - Tate / 2;

				// ベクトル正規化
				float length = (float)sqrt(dx * dx + dy * dy);
				bullet[i]->Bullet_Vector_X = dx / length;
				bullet[i]->Bullet_Vector_Y = dy / length;

				break; // 1発だけ発射
			}
		}
	}
	void PLAYER::BOUNCE_To_ENEMY(ENEMY* enemy) {
		for (int i = 0; i < num; i++) {
			if (!(bullet[i]->HP == false)) {  // 死んでる弾を再利用
				bullet[i]->HP = true;
				bullet[i]->bounce_F = true;
				// 生きてる状態にする
				//bullet[i]->Bullet_X = Yoko / 2;
				//bullet[i]->Bullet_Y = Tate / 2;

				// マウス座標を取得
				float distance_x = bullet[i]->Bullet_X - enemy->X;
				float distance_y = bullet[i]->Bullet_Y - enemy->Y;
				float dist = (float)sqrt(distance_x * distance_x + distance_y * distance_y);
				if (dist < 20 && bullet[i]->bounce_F == true) {
					//float dx = bullet[i]->Bullet_X - enemy->X;
					//float dy = bullet[i]->Bullet_Y - enemy->Y;
					// ベクトル正規化
					float length = (float)sqrt(distance_x * distance_x + distance_y * distance_y);
					bullet[i]->Bullet_Vector_X = distance_x / length;
					bullet[i]->Bullet_Vector_Y = distance_y / length;
					bullet[i]->bounce_F = false;
				}

				break; // 1発だけ発射
			}
			else { bullet[i]->bounce_F = false; }
		}
	}
	void BULLET::BOUNCE_MOVE_and_DRAW(ENEMY* enemy) {
		//for (int i = 0; i < 32; i++) {
		if (HP == true) {
			Bullet_X += Bullet_Vector_X * (BulletSpeed / 1.5f);
			Bullet_Y += Bullet_Vector_Y * (BulletSpeed / 1.5f);

			float dx = Bullet_X - enemy->X;
			float dy = Bullet_Y - enemy->Y;
			float dist = (float)sqrt(dx * dx + dy * dy);
			if (dist < 25) {
				enemy->HP -= Bullet_Power;
				bounce_F = true;
			}
			else {
				bounce_F = false;
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

	void BULLET::BULLET_MOVE_and_DRAW(ENEMY* enemy) {
		//for (int i = 0; i < 32; i++) {
		if (HP == true) {
			Bullet_X += Bullet_Vector_X * BulletSpeed;
			Bullet_Y += Bullet_Vector_Y * BulletSpeed;

			float dx = Bullet_X - enemy->X;
			float dy = Bullet_Y - enemy->Y;
			float dist = (float)sqrt(dx * dx + dy * dy);
			if (dist < 25) {
				enemy->HP -= Bullet_Power;
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
	void PLAYER::LASER_To_Mouse() {
		if (bullet[0]->HP == false) {  // 死んでる弾を再利用
			bullet[0]->HP = true;  // 生きてる状態にする
			bullet[0]->Bullet_X = Yoko / 2;
			bullet[0]->Bullet_Y = Tate / 2;

			// マウス座標を取得
			float dx = mouseX - Yoko / 2;
			float dy = mouseY - Tate / 2;

			// ベクトル正規化
			float length = (float)sqrt(dx * dx + dy * dy);
			bullet[0]->Bullet_Vector_X = dx / length;
			bullet[0]->Bullet_Vector_Y = dy / length;

			//break; // 1発だけ発射
		}

	}
	void BULLET::LASER_MOVE_and_DRAW(ENEMY* enemy) {
		//for (int i = 0; i < 32; i++) {
		if (HP == true) {
			Bullet_X += Bullet_Vector_X * BulletSpeed;
			Bullet_Y += Bullet_Vector_Y * BulletSpeed;

			float dx = Bullet_X - enemy->X;
			float dy = Bullet_Y - enemy->Y;
			float dist = (float)sqrt(dx * dx + dy * dy);
			if (dist < 25) {
				enemy->HP -= Bullet_Power;
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
	/*
	void PLAYER:: RANDOM_To_Mouse() {
		for (int i = 0; i < num; i++) {
			if (bullet[i]->HP == false) {  // 死んでる弾を再利用
				bullet[i]->HP = true;  // 生きてる状態にする
				bullet[i]->bounce_F = true;
				bullet[i]->Bullet_X = Yoko / 2;
				bullet[i]->Bullet_Y = Tate / 2;

				// マウス座標を取得
				float dx = mouseX - Yoko / 2;
				float dy = mouseY - Tate / 2;

				// ベクトル正規化
				float length = sqrt(dx * dx + dy * dy);
				bullet[i]->Bullet_Vector_X = dx / length;
				bullet[i]->Bullet_Vector_Y = dy / length;

				break; // 1発だけ発射
			}
		}
	}
	*/
	void PLAYER::RANDOM_To_Random() {
		for (int i = 0; i < num; i++) {
			if (!(bullet[i]->HP == false)) {  // 死んでる弾を再利用
				//bullet[i]->HP = true;  // 生きてる状態にする
				//bullet[i]->Bullet_X = Yoko / 2;
				//bullet[i]->Bullet_Y = Tate / 2;
				if (rand() % 120 == 0) {
					// マウス座標を取得
					float dx = bullet[i]->Bullet_X - (rand() % Yoko);
					float dy = bullet[i]->Bullet_Y - (rand() % Tate);
					// ベクトル正規化
					float length = (float)sqrt(dx * dx + dy * dy);
					bullet[i]->Bullet_Vector_X = dx / length;
					bullet[i]->Bullet_Vector_Y = dy / length;

					break; // 1発だけ発射
				}
			}
		}
	}
	void BULLET::RANDOM_MOVE_and_DRAW(ENEMY* enemy) {
		//for (int i = 0; i < 32; i++) {
		if (HP == true) {
			Bullet_X += Bullet_Vector_X * (BulletSpeed * 0.1f);
			Bullet_Y += Bullet_Vector_Y * (BulletSpeed * 0.1f);

			float dx = Bullet_X - enemy->X;
			float dy = Bullet_Y - enemy->Y;
			float dist = (float)sqrt(dx * dx + dy * dy);
			if (dist < 30) {
				enemy->HP -= Bullet_Power;
				//HP = 0;
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
	void BULLET::ORBIT_START(int index, int total_bullets,  float radius_argument, float angle_increment_argument) {
		HP = true;
		this->radius = radius_argument;
		this->angle_increment = angle_increment_argument;

		// 均等な初期角度（indexごとにずらす）
		this->Angle = (2 * PI / total_bullets) * index;

		this->Bullet_Hit_Flag = false;
	}
	void BULLET::ORBIT_MOVE_and_DRAW(ENEMY* enemy) {
		if (!HP) return;

		// 中心をプレイヤーの座標に設定
		float centerX = Yoko/2.0f;
		float centerY = Tate/2.0f;

		// 回転更新
		Angle += angle_increment;
		if (Angle > 2 * PI) Angle -= 2 * PI;

		// 座標更新
		Bullet_X = centerX + (float)cos(Angle) * radius;
		Bullet_Y = centerY + (float)sin(Angle) * radius;

		// 当たり判定（オプション）
		if (enemy != nullptr) {
			float dx = enemy->X - (Bullet_X + 10);
			float dy = enemy->Y - (Bullet_Y + 10);
			float dist = (float)sqrt(dx * dx + dy * dy);
			if (dist < 15) {
				enemy->HP -= Bullet_Power;
			}
		}

		// 描画
		fill(0, 0, 255);
		circle(Bullet_X+25, Bullet_Y+25, 6);

		//if (Angle > 360.0f) Angle -= 360.0f;
	}
	int PLAYER::ORBIT_NUM_return() {
		return orbit_num;
	}
	void BULLET::MINE_USE(BULLET* bullet[]) {
		for (int i = 0; i < 10; i++) {
			if (bullet[i]->HP == false) {  // 死んでる弾を再利用
				bullet[i]->HP = true;  // 生きてる状態にする 
				bullet[i]->Bullet_X = Yoko / 2;
				bullet[i]->Bullet_Y = Tate / 2;
				break;
			}
		}
		//break; // 1発だけ
	}
	void BULLET::MINE_MOVE() {
		if (HP == true) {
			if (isPress(KEY_W)) { Bullet_Y -= -3; }
			if (isPress(KEY_A)) { Bullet_X -= -3; }
			if (isPress(KEY_S)) { Bullet_Y -= 3; }
			if (isPress(KEY_D)) { Bullet_X -= 3; }
			// 画面外に出たら消す
			if (Bullet_X < -1000 || Bullet_X > 2900 || Bullet_Y < -1000 || Bullet_Y > 2100) {
				HP = 0;
			}
		}
	}
	bool BULLET::MINE_JUDGE_and_DRAW(ENEMY* enemy) {
		if (HP == true) {
			float dist_x = Bullet_X - enemy->X;
			float dist_y = Bullet_Y - enemy->Y;
			float dist = (float)sqrt(dist_x * dist_x + dist_y * dist_y);
			fill(0, 0, 255);
			circle(Bullet_X, Bullet_Y, 30 * 2);
			if (dist < 30 && HP == true) {
				MINE_damege_Flag = true;
				return true;
			}
				return false;
		}
	}
	void BULLET::MINE_damege(ENEMY* enemy[]) {
		for (int i = 0; i < 50; i++) {
			if (!(enemy[i]->HP <= 0)) {
				float distance_x = Bullet_X - enemy[i]->X;
				float distance_y = Bullet_Y - enemy[i]->Y;
				float distance = (float)sqrt(distance_x * distance_x + distance_y * distance_y);
				if (distance < 300) {
					fill(255, 0, 0);
					circle(Bullet_X, Bullet_Y, 350 * 2);
					enemy[i]->HP -= Bullet_Power;
					//enemy[i].HP = 0;
						HP = false;
				}
			}
		}
		MINE_damege_Flag = false;
	}
	void PLAYER::DEBUG_TEXT() {
		//text(orbit_num, 500, 100);
	}
}