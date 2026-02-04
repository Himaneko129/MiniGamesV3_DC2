#pragma once
#include "GAME11.h"
namespace GAME11 {
	class TITLE {

	};
	class SELECT {
		int select_return = 0;
		bool how_to_flag = 0;
	public:
		void SELECT_DRAW(int num);
		int SELECT_CHARA();
		void SELECT_WEAPON(int num);
		int SELECT_SELECT_CHARA();
		void GET_SELECT_NUM(int num);
		int OUT_SELECT_NUM();
		bool Go_to_PLAY();
		void HOW_TO_PLAY();
	};
}