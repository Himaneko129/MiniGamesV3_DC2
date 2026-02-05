#include "../../libOne/inc/libOne.h"
#include "GAME11.h"
#include"TITLE_SELECT.h"
namespace GAME11 {
	int SELECT::SELECT_SELECT_CHARA() {
		if (100 < mouseX && mouseX < 250) {
			if (100 < mouseY && mouseY < 250) {
				return 1;
			}
			else if (250 < mouseY && mouseY < 400) {
				return 2;
			}
			else if (400 < mouseY && mouseY < 550) {
				return 3;
			}
			else if (550 < mouseY && mouseY < 700) {
				return 4;
			}
			else {
				return 0;
			}
		}
		else if (250 < mouseX && mouseX < 400) {
			if (100 < mouseY && mouseY < 250) {
				return 5;
			}
			else if (250 < mouseY && mouseY < 400) {
				return 6;
			}
			else if (400 < mouseY && mouseY < 550) {
				return 7;
			}
			else if (550 < mouseY && mouseY < 700) {
				return 8;
			}
			else {
				return 0;
			}
		}
		else if (400 < mouseX && mouseX < 550) {
			if (100 < mouseY && mouseY < 250) {
				return 9;
			}
			else if (250 < mouseY && mouseY < 400) {
				return 10;
			}
			else if (400 < mouseY && mouseY < 550) {
				return 11;
			}
			else if (550 < mouseY && mouseY < 700) {
				return 12;
			}
			else {
				return 0;
			}
		}
		else if (550 < mouseX && mouseX < 700) {
			if (100 < mouseY && mouseY < 250) {
				return 13;
			}
			else if (250 < mouseY && mouseY < 400) {
				return 14;
			}
			else if (400 < mouseY && mouseY < 550) {
				return 15;
			}
			else if (550 < mouseY && mouseY < 700) {
				return 16;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	void SELECT::SELECT_DRAW(int num) {
		fill(128);
		rect(100, 100, 150, 150);
		rect(100, 250, 150, 150);
		rect(100, 400, 150, 150);
		rect(100, 550, 150, 150);
		rect(250, 100, 150, 150);
		rect(250, 250, 150, 150);
		rect(250, 400, 150, 150);
		rect(250, 550, 150, 150);
		rect(400, 100, 150, 150);
		rect(400, 250, 150, 150);
		rect(400, 400, 150, 150);
		rect(400, 550, 150, 150);
		rect(550, 100, 150, 150);
		rect(550, 250, 150, 150);
		rect(550, 400, 150, 150);
		rect(550, 550, 150, 150);
		if (num == 1) {
			fill(255, 255, 0);
			rect(100, 100, 150, 150);
		}
		else if (num == 2) {
			fill(255, 255, 0);
			rect(100, 250, 150, 150);
		}
		else if (num == 3) {
			fill(255, 255, 0);
			rect(100, 400, 150, 150);
		}
		else if (num == 4) {
			fill(255, 255, 0);
			rect(100, 550, 150, 150);
		}

		else if (num == 5) {
			fill(255, 255, 0);
			rect(250, 100, 150, 150);
		}
		else if (num == 6) {
			fill(255, 255, 0);
			rect(250, 250, 150, 150);
		}
		else if (num == 7) {
			fill(255, 255, 0);
			rect(250, 400, 150, 150);
		}
		else if (num == 8) {
			fill(255, 255, 0);
			rect(250, 550, 150, 150);
		}
		else if (num == 9) {
			fill(255, 255, 0);
			rect(400, 100, 150, 150);
		}
		else if (num == 10) {
			fill(255, 255, 0);
			rect(400, 250, 150, 150);
		}
		else if (num == 11) {
			fill(255, 255, 0);
			rect(400, 400, 150, 150);
		}
		else if (num == 12) {
			fill(255, 255, 0);
			rect(400, 550, 150, 150);
		}
		else if (num == 13) {
			fill(255, 255, 0);
			rect(550, 100, 150, 150);
		}
		else if (num == 14) {
			fill(255, 255, 0);
			rect(550, 250, 150, 150);
		}
		else if (num == 15) {
			fill(255, 255, 0);
			rect(550, 400, 150, 150);
		}
		else if (num == 16) {
			fill(255, 255, 0);
			rect(550, 550, 150, 150);
		}

	}
	int SELECT::SELECT_CHARA() {
		if (100 < mouseX && mouseX < 250) {
			if (100 < mouseY && mouseY < 250) {
				select_return = 1;
				return 1;
			}
			else if (250 < mouseY && mouseY < 400) {
				select_return = 2;
				return 2;
			}
			else if (400 < mouseY && mouseY < 550) {
				select_return = 3;
				return 3;
			}
			else if (550 < mouseY && mouseY < 700) {
				select_return = 4;
				return 4;
			}
			else {
				return 0;
			}
		}
		else if (250 < mouseX && mouseX < 400) {
			if (100 < mouseY && mouseY < 250) {
				select_return = 5;
				return 5;
			}
			else if (250 < mouseY && mouseY < 400) {
				select_return = 6;
				return 6;
			}
			else if (400 < mouseY && mouseY < 550) {
				select_return = 7;
				return 7;
			}
			else if (550 < mouseY && mouseY < 700) {
				select_return = 8;
				return 8;
			}
			else {
				return 0;
			}
		}
		else if (400 < mouseX && mouseX < 550) {
			if (100 < mouseY && mouseY < 250) {
				select_return = 9;
				return 9;
			}
			else if (250 < mouseY && mouseY < 400) {
				select_return = 10;
				return 10;
			}
			else if (400 < mouseY && mouseY < 550) {
				select_return = 11;
				return 11;
			}
			else if (550 < mouseY && mouseY < 700) {
				select_return = 12;
				return 12;
			}
			else {
				return 0;
			}
		}
		else if (550 < mouseX && mouseX < 700) {
			if (100 < mouseY && mouseY < 250) {
				select_return = 13;
				return 13;
			}
			else if (250 < mouseY && mouseY < 400) {
				select_return = 14;
				return 14;
			}
			else if (400 < mouseY && mouseY < 550) {
				select_return = 15;
				return 15;
			}
			else if (550 < mouseY && mouseY < 700) {
				select_return = 16;
				return 16;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	bool SELECT::Go_to_PLAY() {
		textSize(100);
		fill(255);
		rect(Yoko - 250, Tate - 175, 300, 150);
		fill(255, 255, 0);
		rect(Yoko - 225, Tate - 150, 200, 100);
		fill(0);
		text("PLAY", Yoko - 225, Tate - 150);
		if (isTrigger(MOUSE_LBUTTON)) {
			if ((Yoko - 250 < mouseX && mouseX < Yoko) && (Tate-175 < mouseY && mouseY < Tate)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			false;
		}
	}
	void SELECT::HOW_TO_PLAY() {
		if (mouseY > Tate - 100 && mouseX < 850) {
			if (isTrigger(MOUSE_LBUTTON)) {
				if (how_to_flag) {
					how_to_flag = false;
				}
				else {
					how_to_flag = true;
				}
			}
		}
	}
	void SELECT::SELECT_WEAPON(int num) {
		textSize(100);
		fill(255);
		HOW_TO_PLAY();
		text("HOW_TO_PLAY:CLICK", 0, Tate - 100);
		if (how_to_flag) {
			textSize(50);
			text("Startを押した瞬間", Yoko / 2, (Tate / 2) - 500);
			text("PLAY画面へ移動します", Yoko / 2, (Tate / 2) - 450);
			text("周りに敵がスポーンするので", Yoko / 2, (Tate / 2) - 300);
			text("それらを倒して経験値を獲得し、", Yoko / 2, (Tate / 2) - 250);
			text("レベルを上げて", Yoko / 2, (Tate / 2) - 200);
			text("より長く生き残ってください", Yoko / 2, (Tate / 2) - 150);
			text("定期的に他の個体よりも", Yoko / 2, (Tate / 2));
			text("体が大きいボス個体がスポーンします", Yoko / 2, (Tate / 2)+50);
			text("倒すと他の個体よりも多く", Yoko / 2, (Tate / 2) + 100);
			text("経験値を落としますが", Yoko / 2, (Tate / 2) + 150);
			text("その分体力が多いです", Yoko / 2, (Tate / 2) + 200);
			return;
		}
		if (num == 1) {
			text("No.1", Yoko / 2, (Tate / 2) - 200);
			text("NAME:MELEE", Yoko / 2, (Tate / 2)-100);
			text("Method:SPACE", Yoko / 2, (Tate / 2));
			text("MIN:1...MAX:4", Yoko / 2, (Tate / 2) + 100);
			text("Attack:5", Yoko / 2, (Tate / 2) + 200);
			text("Range:1", Yoko / 2, (Tate / 2) + 300);
			text("Easy to use:5", Yoko / 2, (Tate / 2) + 400);	//penetrating
		}
		else if (num == 2) {
			text("No.2", Yoko / 2, (Tate / 2) - 200);
			text("NAME:MOUSE", Yoko / 2, (Tate / 2)-100);
			text("Method:WASD", Yoko / 2, (Tate / 2));
			text("MIN:1...MAX:4", Yoko / 2, (Tate / 2) + 100);
			text("Attack:2", Yoko / 2, (Tate / 2) + 200);
			text("Range:5", Yoko / 2, (Tate / 2) + 300);
			text("Easy to use:1", Yoko / 2, (Tate / 2) + 400);
		}
		else if (num == 3) {
			text("No.3", Yoko / 2, (Tate / 2) - 200);
			text("NAME:RANGE", Yoko / 2, (Tate / 2)-100);
			text("Method:Shift", Yoko / 2, (Tate / 2));
			text("MIN:1...MAX:4", Yoko / 2, (Tate / 2) + 100);
			text("Attack:5", Yoko / 2, (Tate / 2) + 200);
			text("Range:2", Yoko / 2, (Tate / 2) + 300);
			text("Easy to use3:", Yoko / 2, (Tate / 2) + 400);
		}
		else if (num == 4) {
			text("No.4", Yoko / 2, (Tate / 2) - 200);
			text("NAME:GUN", Yoko / 2, (Tate / 2)-100);
			text("Method:MouseL", Yoko / 2, (Tate / 2));
			text("MIN:1...MAX:4", Yoko / 2, (Tate / 2) + 100);
			text("Attack:4", Yoko / 2, (Tate / 2) + 200);
			text("Range:5", Yoko / 2, (Tate / 2) + 300);
			text("Easy to use:5", Yoko / 2, (Tate / 2) + 400);
		}
		else if (num == 5) {
			text("No.5", Yoko / 2, (Tate / 2) - 200);
			text("NAME:LASER", Yoko / 2, (Tate / 2)-100);
			text("Method:MouseR", Yoko / 2, (Tate / 2));
			text("MIN:1...MAX:4", Yoko / 2, (Tate / 2) + 100);
			text("Attack:5", Yoko / 2, (Tate / 2) + 200);
			text("Range:5", Yoko / 2, (Tate / 2) + 300);
			text("Easy to use:5", Yoko / 2, (Tate / 2) + 400);
		}
		else if (num == 6) {
			text("No.6", Yoko / 2, (Tate / 2) - 200);
			text("NAME:BOUNCE", Yoko / 2, (Tate / 2)-100);
			text("Method:Q", Yoko / 2, (Tate / 2));
			text("MIN:1...MAX:4", Yoko / 2, (Tate / 2) + 100);
			text("Attack:4", Yoko / 2, (Tate / 2) + 200);
			text("Range:5", Yoko / 2, (Tate / 2) + 300);
			text("Easy to use:4", Yoko / 2, (Tate / 2) + 400);
		}
		else if (num == 7) {
			text("No.7", Yoko / 2, (Tate / 2) - 200);
			text("NAME:BOOM", Yoko / 2, (Tate / 2)-100);
			text("Method:Mouse", Yoko / 2, (Tate / 2));
			text("MIN:1...MAX:5", Yoko / 2, (Tate / 2) + 100);
			text("Attack:2", Yoko / 2, (Tate / 2) + 200);
			text("Range:4", Yoko / 2, (Tate / 2) + 300);
			text("Easy to use:2", Yoko / 2, (Tate / 2) + 400);
		}
		else if (num == 8) {
			text("No.8", Yoko / 2, (Tate / 2) - 200);
			text("NAME:RANDOM", Yoko / 2, (Tate / 2)-100);
			text("Method:E", Yoko / 2, (Tate / 2));
			text("MIN:1...MAX:5", Yoko / 2, (Tate / 2) + 100);
			text("Attack:3", Yoko / 2, (Tate / 2) + 200);
			text("Range:5", Yoko / 2, (Tate / 2) + 300);
			text("Easy to use:?", Yoko / 2, (Tate / 2) + 400);
		}
		else if (num == 9) {
			text("No.9", Yoko / 2, (Tate / 2) - 200);
			text("NAME:ORBIT", Yoko / 2, (Tate / 2)-100);
			text("Method:None", Yoko / 2, (Tate / 2));
			text("MIN:1...MAX:5", Yoko / 2, (Tate / 2) + 100);
			text("Attack:2", Yoko / 2, (Tate / 2) + 200);
			text("Range:2", Yoko / 2, (Tate / 2) + 300);
			text("Easy to use:2", Yoko / 2, (Tate / 2) + 400);
		}
		else if (num == 10) {
			text("No.10", Yoko / 2, (Tate / 2) - 200);
			text("NAME:MINE", Yoko / 2, (Tate / 2)-100);
			text("Method:C", Yoko / 2, (Tate / 2));
			text("MIN:1...MAX:5", Yoko / 2, (Tate / 2) + 100);
			text("Attack:5", Yoko / 2, (Tate / 2) + 200);
			text("Range:1", Yoko / 2, (Tate / 2) + 300);
			text("Easy to use:1", Yoko / 2, (Tate / 2) + 400);
		}
		else {
			text("左から武器種を", Yoko / 2, Tate / 2);
			text("選んでクリック！", Yoko / 2, Tate / 2 + 100);
		}
	}
	void SELECT::GET_SELECT_NUM(int num) {
		if (!(num == 0)) {
			select_return = num;
		}
	}
	int SELECT::OUT_SELECT_NUM() {
		return select_return;
	}
}