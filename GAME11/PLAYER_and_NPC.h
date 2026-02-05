#pragma once
#include "GAME11.h"
#include<chrono>
namespace GAME11 {
	class ENEMY; // 前方宣言
	class PLAYER;
	class BOSS;

	class CHARACTER {
	public:
		float X = 0, Y = 0, Angle = 0;
		int Width = 0, Height = 0;
		float HP = 0, MAX_HP = 0, ATK = 0;
		float SPEED = 0;
	public:
		//virtual ~CHARACTER() {}
	};

	class PLAYER_STATUS {
	public:
		bool Draw_Level_Up = false;
		int Drawtime = 0;
		bool LevelUp_Flag = false;
	protected:
		int LEVEL = 0;
		double EXP = 0;
		double NextExp = 0;
		float Bar_Width = 0;
	public:
		void STATUS_INIT();
		void DRAW_EXP();
		bool Exp_System(ENEMY* enemy);
		bool Exp_System_for_BOSS(BOSS* boss);
		int PLAYER_LEVEL_RETURN();
		bool LEVELUP_Flag();
		void LEVELUP_Finish();
		void Set_LEVELUP_Flag(bool flag);
	};

	class ATTACK {
	public:
		int Attack_Power = 0;
		int FireRate = 0;   // 連射間隔 
		float Center_X = 0;
		float Center_Y = 0;
		float Center_2_X = 0;
		float Center_2_Y = 0;
		float Center_3_X = 0;
		float Center_3_Y = 0;
		float range = 0;    // 攻撃範囲
		//int duration = 0;   // 残りフレーム数
		bool Melee_Flag = false;
		bool Mouse_Flag = false;
		bool Range_Flag = false;
		bool Long_Range_Flag = false;
		bool Laser_Flag = false;
		bool Bounce_Flag = false;
		bool Boom_Flag = false;
		bool Boom_HP = false;
		bool Boom_HP_for_BOSS = false;
		bool Random_Flag = false;
		bool Orbit_Flag = false;
		bool MINE_Flag = false;
	public:
		void ATTACK_INIT();
		void Flag_INIT();
		void Melee_Attack(ENEMY* enemy);
		void Range_Attack(ENEMY* enemy);
		void Mouse_Attack(ENEMY* enemy);
		void Mouse_damege(ENEMY enemy[]);
		void Boom_Attack(ENEMY** enemy);
		void Boom_Center_INIT();
		void Melee_Attack_BOSS(BOSS* boss);
		void Range_Attack_BOSS(BOSS* boss);
		void Mouse_Attack_BOSS(BOSS* boss);
		void Boom_Attack_BOSS(BOSS* boss);
		void Boom_HP_Flag_False();
	};
	class BULLET {
	public:
		bool HP = 0;
		int Bullet_Power = 0;
		int BulletSpeed = 0;
		float Bullet_X = 0;
		float Bullet_Y = 0;
		float Bullet_Vector_X = 0;
		float Bullet_Vector_Y = 0;
		float Angle = 0;
		bool bounce_F = 0;
		const int Orbit_MAX = 12;
		float radius = 0;
		float angle_increment = 0;
		bool Bullet_Hit_Flag = false;
		const float PI = 3.14159265358979323846f;
		bool MINE_damege_Flag = false;
	public:
		void BULLET_INIT(PLAYER* player);
		void BULLET_MOVE_and_DRAW(ENEMY* enemy);
		void LASER_MOVE_and_DRAW(ENEMY* enemy);
		void BOUNCE_MOVE_and_DRAW(ENEMY* enemy);
		void RANDOM_MOVE_and_DRAW(ENEMY* enemy);
		void ORBIT_START(int index, int total_bullets, float radius_argument, float angle_increment);
		void ORBIT_MOVE_and_DRAW(ENEMY* enemy);
		void MINE_USE(BULLET* bullet[]);
		void MINE_MOVE();
		bool MINE_JUDGE_and_DRAW(ENEMY* enemy);
		void MINE_damege(ENEMY* enemy[]);
		void BULLET_MOVE_and_DRAW_for_BOSS(BOSS* boss);
		void LASER_MOVE_and_DRAW_for_BOSS(BOSS* boss);
		void BOUNCE_MOVE_and_DRAW_for_BOSS(BOSS* boss);
		void RANDOM_MOVE_and_DRAW_for_BOSS(BOSS* boss);
		void ORBIT_MOVE_and_DRAW_for_BOSS(BOSS* boss);
		//void MINE_DRAW_for_BOSS(BOSS* boss);
		bool MINE_JUDGE_and_DRAW_for_BOSS(BOSS* boss);
		void MINE_damege_for_BOSS(BOSS* boss);
	};

	class PLAYER : public CHARACTER {
	protected:
		float BUG_X = 0;
		float BUG_Y = 0;
		int Player_Width = 0;
		int Player_Height = 0;
		signed char Vector_X_Flag = 0;
		signed char Vector_Y_Flag = 0;
		int Player_Image = 0;
		int lastBulletBonusLevel = 0;

	public:
		int orbit_num = 0;


		ATTACK* attack;

		PLAYER_STATUS* player_status;

		const int num = 32;
		BULLET* bullet[32];

		PLAYER() {
			player_status = new PLAYER_STATUS();
			attack = new ATTACK();
			for (int i = 0; i < 32; i++) {
				bullet[i] = new BULLET;
			}
		}
		~PLAYER() {
			delete player_status;
			delete attack;
			for (int i = 0; i < 32; i++) {
				delete bullet[i];
			}
		}
		//void setImage(int Img);
		void Player_INIT();
		void RANDOM_SET();
		void Like_a_BUG(int percent, int color, int pattern);
		void Player_MOVE();
		void Player_DRAW();
		void PLAYER_DAMAGE_and_DRAW(ENEMY* enemy);
		void PLAYER_DAMAGE_and_DRAW_for_BOSS(BOSS* boss);
		float Distance(float x1, float y1, float x2, float y2);
		void Player_Angle_Change();
		void LEVEL_UP();
		void LEVEL_UP_STATUS();
		void BULLET_To_Mouse();
		void LASER_To_Mouse();
		void BOUNCE_To_ENEMY(ENEMY* enemy);
		//void RANDOM_To_Mouse();
		void RANDOM_To_Random();
		void ORBIT_BULLET_PLUS(int num);
		int ORBIT_NUM_return();
		void DEBUG_TEXT();
		bool JUDGE_GAME_OVER();
	};

	class ENEMY : public CHARACTER {
	protected:
		int enemy_Level = 0;
		int Enemy_Image = 0;
		float save_HP = 0;
		float save_SPEED = 0;
		int Debug_Num = 0;

	public:
		void ENEMY_INIT(ENEMY* enemy);
		void DRAW_ENEMY_HP(ENEMY* enemy);
		void Spawn_Enemy(ENEMY* enemy);
		void Go_Player(ENEMY* enemy);
		void DRAW_ENEMY(ENEMY* enemy);
		void Despone(ENEMY* enemy, bool flag);
		void ENEMY_LEVELUP(ENEMY* enemy);
		void ENEMY_RESPORN(ENEMY* enemy);
	};
	class BOSS :public ENEMY {
	protected:
		int boss_Level = 0;
		int Spawn_time = 0;
		int Spawn_Count = 0;
	public:
		bool BOSS_Spawn_Flag = false;
		void BOSS_INIT(BOSS* boss);
		void Spawn_BOSS(BOSS* boss);
		void DRAW_BOSS_HP(BOSS* boss);
		void Go_Player_BOSS(BOSS* boss);
		void DRAW_BOSS(BOSS* boss);
		void BOSS_LEVELUP(BOSS* boss);
		//void DRAW_HP();
	};
}