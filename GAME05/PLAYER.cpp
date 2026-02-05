#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME05.h"
#include"PLAYER.h"
namespace GAME05 {

	void PLAYER::setImage(int Img) {
		Player_Image = Img;
	}
	void PLAYER::Player_INIT() {
		Player_X = 400;
		Player_Y = 500;
		Last_Player_X = Player_X;
		Last_Player_Y = Player_Y;
		Player_Width = 45;
		Player_Height = 50;;
		Vector_X = 2;
		Vector_Y = 2;

	}
	void PLAYER::Player_MOVE(int num) {
		Last_Player_X = Player_X;
		Last_Player_Y = Player_Y;
		if (isPress(KEY_Q)) {
			Player_X += 1;
			Player_Y -= 1;
		}
		if (isPress(KEY_W)) {
			//Last_Player_X = Player_X;
			Player_X += 3 ;
		}
		if (isPress(KEY_E)) {
			Player_X += 1;
			Player_Y += 1;
		}
		if (isPress(KEY_A)) {
			Player_Y -= 2;
		}
		if (isPress(KEY_S)) {
			Player_X -= 1;
		}
		if (isPress(KEY_D)) {
			Player_Y += 2;
		}
		//‰EŽè.
		if (isPress(KEY_U)) {
			Player_X += 1;
			Player_Y -= 1;
		}
		if (isPress(KEY_I)) {
			//Last_Player_X = Player_X;
			Player_X += 3;
		}
		if (isPress(KEY_O)) {
			Player_X += 1;
			Player_Y += 1;
		}
		if (isPress(KEY_J)) {
			Player_Y -= 2;
		}
		if (isPress(KEY_K)) {
			Player_X -= 1;
		}
		if (isPress(KEY_L)) {
			Player_Y += 2;
		}
		if (num == 1) {
		Player_X -= 4;
		}
		else if (num == 2) {
			Player_X -= 4;
		}
		else if (num == 3) {
			Player_X -= 3;

		}
	}
	void PLAYER::Player_SELECT_MOVE() {
		Last_Player_X = Player_X;
		Last_Player_Y = Player_Y;
		if (isPress(KEY_Q)) {
			Player_X += 3;
			Player_Y -= 3;
		}
		if (isPress(KEY_W)) {
			Player_X += 6;
		}
		if (isPress(KEY_E)) {
			Player_X += 3;
			Player_Y += 3;
		}
		if (isPress(KEY_A)) {
			Player_X -= 3;
			Player_Y -= 3;
		}
		if (isPress(KEY_S)) {
			Player_X -= 6;
		}
		if (isPress(KEY_D)) {
			Player_X -= 3;
			Player_Y += 3;
		}
		//‰EŽè.
		if (isPress(KEY_U)) {
			Player_X += 3;
			Player_Y -= 3;
		}
		if (isPress(KEY_I)) {
			Player_X += 6;
		}
		if (isPress(KEY_O)) {
			Player_X += 3;
			Player_Y += 3;
		}
		if (isPress(KEY_J)) {
			Player_X -= 3;
			Player_Y -= 3;
		}
		if (isPress(KEY_K)) {
			Player_X -= 6;
		}
		if (isPress(KEY_L)) {
			Player_X -= 3;
			Player_Y += 3;
		}

	}
	void PLAYER::Player_position_reset() {
		Player_X = 400;
		Player_Y = 500;
	}
	void PLAYER::Player_DRAW() {
		rectMode(CORNER);
		//rect(Player_X, Player_Y, Player_Width, Player_Height);
		image(Player_Image, Player_X-5, Player_Y-15);
	}
}