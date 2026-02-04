#pragma once
namespace GAME05 {
	class PLAYER {
	public:
		float Player_X = 0;
		float Player_Y = 0;
		float Last_Player_X = 0;
		float Last_Player_Y = 0;
		int Player_Width = 0;
		float Player_Height = 0;
		float Vector_X = 0;
		float Vector_Y = 0;
		int Player_Image = 0;
	public:
		void setImage(int Img);
		void Player_INIT();
		void Player_MOVE(int num);
		void Player_DRAW();
		void Player_SELECT_MOVE();
		void Player_position_reset();
	};
}