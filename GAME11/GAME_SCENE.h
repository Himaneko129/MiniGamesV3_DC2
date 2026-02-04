#pragma once
#include "GAME11.h"
namespace GAME11 {
	class GAME_SCENE {
	public:
		const enum scene {
			INIT, TITLE, OPTION, SELECT, PLAY,GAMEOVER
		};
		int game_state = 0;
	};
}