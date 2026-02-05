#include"HIRAGANA_GAME.h"
namespace GAME14 {
	void HIRAGANA::IMAGE_SET_INIT() {
		//Image[0][1] = loadImage("..\\MAIN\\assets\\game14\\Commander.png");
		Image[0]= loadImage("..\\MAIN\\assets\\game14\\hiragana\\yazirusi.png");
		Image[1] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\blue.png");
		Image[2] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\ie.png");
		Image[3] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\ai.png");
		Image[4] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\iai.png");
		Image[5] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\ou.png");
		Image[6] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\iu.png");
		Image[7] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\iei.png");
		Image[8] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\nisi.png");
		Image[9] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\koma.png");
		Image[10] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\hati.png");
		Image[11] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\nasi.png");
		Image[12] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\yakann.png");
		Image[13] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\moyasi.png");
		Image[14] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\kiiro.png");
		Image[15] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\suika.png");
		Image[16] = loadImage("..\\MAIN\\assets\\game14\\hiragana\\sikaku.png");
		How_To_Image= loadImage("..\\MAIN\\assets\\game14\\hiragana\\how_to_play_.png");
	}
	void HIRAGANA::TITLE_INIT() {
		WIDTH = 750;
		HEIGHT = 200;
		Position_X = (Yoko / 2) - 425;
		Position_Y = Tate / 2;
		Position_X_2 = (Yoko / 2) - 425;
		Position_Y_2 = (Tate / 2) + 200;
		stage_Progress = 1;
		text_Potition_X = 650;
		text_Potition_Y = 200;
		text_Size = 200;
	}
	bool HIRAGANA::MOUSE_JUDGE(int WIDTH, int HEIGHT, float Pos_X, float Pos_Y) {
		if (Pos_X - 50 < mouseX && mouseX < Pos_X + (WIDTH - 50) && Pos_Y < mouseY && mouseY < Pos_Y + HEIGHT) {
			return true;
		}
		else {
			return false;
		}
	}
	int HIRAGANA::TITLE_DRAW() {
		rectMode(CORNER);
		if (MOUSE_JUDGE(WIDTH, HEIGHT, Position_X - 50, Position_Y - (HEIGHT - 25)) == true) {
			fill(255, 255, 50);
		}
		else {
			fill(255);
		}
		rect(Position_X - 50, Position_Y - (HEIGHT - 50), WIDTH, HEIGHT);
		if (MOUSE_JUDGE(WIDTH, HEIGHT, Position_X_2 - 50, Position_Y_2 - (HEIGHT - 25)) == true) {
			fill(255, 255, 50);
		}
		else {
			fill(255);
		}
		rect(Position_X_2 - 50, Position_Y_2 - (HEIGHT - 25), WIDTH, HEIGHT);
		textSize(150);
		fill(0);
		text("Ç–ÇÁÇ™Ç»éZ", (Yoko / 2) - 375, 300);
		text("ÇÕÇ∂ÇﬂÇÈ", Position_X, Position_Y);
		text("Ç‡Ç«ÇÈ", Position_X_2, Position_Y_2);
		if (isTrigger(MOUSE_LBUTTON)) {
			if (MOUSE_JUDGE(WIDTH, HEIGHT, Position_X, Position_Y - HEIGHT) == true) {
				return 2;
			}
			else if (MOUSE_JUDGE(WIDTH, HEIGHT, Position_X_2, Position_Y_2 - HEIGHT) == true) {
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	void HIRAGANA::STAGE1_DRAW() {
		fill(255);
		textSize(text_Size);
		Goto_Select_Stage = false;
		Correct_answer();
		if (!correct_Answer) {
			if (stage_Progress == 1) {
				text("Ç†+Ç¢=?", text_Potition_X, text_Potition_Y);
				text("Ç¢+Ç¢=?", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 2) {
				text("Ç†+Ç®=?", text_Potition_X, text_Potition_Y);
				text("Ç¢+Ç§=?", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 3) {
				text("Ç¢+Ç®=?", text_Potition_X, text_Potition_Y);
				text("Ç†+Ç§=?", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 4) {
				text("Ç§+Ç§=?", text_Potition_X, text_Potition_Y);
				text("Ç§+Ç¶=?", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 5) {
				text("Ç¢+Ç®=?", text_Potition_X, text_Potition_Y);
				text("Ç¢+Ç¶=?", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç§+Ç¶=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
		}
		else {
			if (stage_Progress == 1) {
				text("Ç†+Ç¢=Ç§", text_Potition_X, text_Potition_Y);
				text("Ç¢+Ç¢=Ç¶", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 2) {
				text("Ç†+Ç®=Ç†", text_Potition_X, text_Potition_Y);
				text("Ç¢+Ç§=Ç®", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 3) {
				text("Ç¢+Ç®=Ç¢", text_Potition_X, text_Potition_Y);
				text("Ç†+Ç§=Ç¶", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 4) {
				text("Ç§+Ç§=Ç†", text_Potition_X, text_Potition_Y);
				text("Ç§+Ç¶=Ç¢", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 5) {
				text("Ç¢+Ç®=Ç¢", text_Potition_X, text_Potition_Y);
				text("Ç¢+Ç¶=Ç†", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç§+Ç¶=Ç¢", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
		}
	}
	void HIRAGANA::STAGE1_INPUT(const char* str) {
		if (stage_Progress == 1) {
			if (strcmp(str, "Ç§Ç¶") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 2) {
			if (strcmp(str, "Ç†Ç®") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 3) {
			if (strcmp(str, "Ç¢Ç¶") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 4) {
			if (strcmp(str, "Ç†Ç¢") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 5) {
			if (strcmp(str, "Ç¢Ç†Ç¢") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
	}
	void HIRAGANA::STAGE1_HINT() {
		textSize(100);
		fill(255);
		if (HINT_Flag) {
			fill(200);
			rect(0, Tate - 400, 256, 256);
			/*
			if (stage_Progress == 1) {
				image(Image[0], 0, Tate - 400);
			}
			else if (stage_Progress == 2) {
				image(Image[1], 0, Tate - 400);
			}
			else if (stage_Progress == 3) {
				image(Image[2], 0, Tate - 400);
			}
			else if (stage_Progress == 4) {
				image(Image[3], 0, Tate - 400);
			}
			else if (stage_Progress == 5) {
				image(Image[4], 0, Tate - 400);
			}
			*/
			image(Image[stage_Progress-1], 0, Tate - 400);
		}
		if (isTrigger(KEY_H)) {
			if (!HINT_Flag) {
				HINT_Flag = true;
			}
			else if (HINT_Flag) {
				HINT_Flag = false;
			}
		}
		else if ((mouseY > (Tate - 100) && mouseX <= 300)) {
			fill(255, 255, 0);
			if (isTrigger(MOUSE_LBUTTON)) {
				if (!HINT_Flag) {
					HINT_Flag = true;
				}
				else if (HINT_Flag) {
					HINT_Flag = false;
				}
			}
		}
		text("H:HINT", 0, Tate);
	}
	void HIRAGANA::STAGE2_DRAW() {
		fill(255);
		textSize(text_Size);
		Goto_Select_Stage = false;
		Correct_answer();
		if (!correct_Answer) {
			if (stage_Progress == 1) {
				text("Ç¢-Ç†=?", text_Potition_X, text_Potition_Y);
				text("Ç¶-Ç¢=?", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 2) {
				text("Ç§-Ç§=?", text_Potition_X, text_Potition_Y);
				text("Ç®-Ç¢=?", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 3) {
				text("Ç†-Ç¶=?", text_Potition_X, text_Potition_Y);
				text("Ç¢-Ç¶=?", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 4) {
				text("Ç®-Ç§=?", text_Potition_X, text_Potition_Y);
				text("Ç¢-Ç¢+Ç¶=?", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç†+Ç¶-Ç§=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 5) {
				text("Ç¶-Ç¶=?", text_Potition_X, text_Potition_Y);
				text("Ç¢+Ç®-Ç¢=?", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç¶-Ç†-Ç®=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
		}
		else {
			if (stage_Progress == 1) {
				text("Ç¢-Ç†=Ç†", text_Potition_X, text_Potition_Y);
				text("Ç¶-Ç¢=Ç¢", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 2) {
				text("Ç§-Ç§=Ç®", text_Potition_X, text_Potition_Y);
				text("Ç®-Ç¢=Ç§", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 3) {
				text("Ç†-Ç¶=Ç¢", text_Potition_X, text_Potition_Y);
				text("Ç¢-Ç¶=Ç§", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 4) {
				text("Ç®-Ç§=Ç¢", text_Potition_X, text_Potition_Y);
				text("Ç¢-Ç¢+Ç¶=Ç¶", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç†+Ç¶-Ç§=Ç¢", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 5) {
				text("Ç¶-Ç¶=Ç®", text_Potition_X, text_Potition_Y);
				text("Ç¢+Ç®-Ç¢=Ç®", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç¶-Ç†-Ç®=Ç§", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
		}
	}
	void HIRAGANA::STAGE2_INPUT(const char* str) {
		if (stage_Progress == 1) {
			if (strcmp(str, "Ç†Ç¢") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 2) {
			if (strcmp(str, "Ç®Ç§") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 3) {
			if (strcmp(str, "Ç¢Ç§") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 4) {
			if (strcmp(str, "Ç¢Ç¶Ç¢") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 5) {
			if (strcmp(str, "Ç®Ç®Ç§") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
	}
	void HIRAGANA::STAGE2_HINT() {
		textSize(100);
		fill(255);
		if (HINT_Flag) {
			fill(200);
			rect(0, Tate - 400, 256, 256);
			if (stage_Progress == 1) {
				image(Image[3], 0, Tate - 400);
			}
			else if (stage_Progress == 2) {
				image(Image[5], 0, Tate - 400);
			}
			else if (stage_Progress == 3) {
				image(Image[6], 0, Tate - 400);
			}
			else if (stage_Progress == 4) {
				image(Image[7], 0, Tate - 400);
			}
			else if (stage_Progress == 5) {
			//	image(Image[4], 0, Tate - 400);
			}
		}
		if (isTrigger(KEY_H)) {
			if (!HINT_Flag) {
				HINT_Flag = true;
			}
			else if (HINT_Flag) {
				HINT_Flag = false;
			}
		}
		else if ((mouseY > (Tate - 100) && mouseX <= 300)) {
			fill(255, 255, 0);
			if (isTrigger(MOUSE_LBUTTON)) {
				if (!HINT_Flag) {
					HINT_Flag = true;
				}
				else if (HINT_Flag) {
					HINT_Flag = false;
				}
			}
		}
		text("H:HINT", 0, Tate);
	}
	void HIRAGANA::STAGE3_DRAW() {
		fill(255);
		textSize(text_Size);
		Goto_Select_Stage = false;
		Correct_answer();
		if (!correct_Answer) {
			if (stage_Progress == 1) {
				text("Ç†+Ç»=?", text_Potition_X, text_Potition_Y);
				text("Ç©+Ç©=?", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 2) {
				text("Ç≠+Ç¢=?", text_Potition_X, text_Potition_Y);
				text("Ç +Ç∑=?", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 3) {
				text("Çµ+Çƒ=?", text_Potition_X, text_Potition_Y);
				text("Ç≠+Çπ=?", text_Potition_X, text_Potition_Y + text_Size);

			}
			else if (stage_Progress == 4) {
				text("Ç´+Çƒ=?", text_Potition_X, text_Potition_Y);
				text("Ç†+Ç≥=?", text_Potition_X, text_Potition_Y + text_Size);
			}
			else if (stage_Progress == 5) {
				text("Ç∑+Ç¬=?", text_Potition_X, text_Potition_Y);
				text("Ç≠+Ç∑=?", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç´+Çª=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
		}
		else {
			if (stage_Progress == 1) {
				text("Ç†+Ç»=Ç…", text_Potition_X, text_Potition_Y);
				text("Ç©+Ç©=Çµ", text_Potition_X, text_Potition_Y + text_Size);

			}
			else if (stage_Progress == 2) {
				text("Ç≠+Ç¢=Ç±", text_Potition_X, text_Potition_Y);
				text("Ç +Ç∑=Ç‹", text_Potition_X, text_Potition_Y + text_Size);

			}
			else if (stage_Progress == 3) {
				text("Çµ+Çƒ=ÇÕ", text_Potition_X, text_Potition_Y);
				text("Ç≠+Çπ=Çø", text_Potition_X, text_Potition_Y + text_Size);

			}
			else if (stage_Progress == 4) {
				text("Ç´+Çƒ=Ç»", text_Potition_X, text_Potition_Y);
				text("Ç†+Ç≥=Çµ", text_Potition_X, text_Potition_Y + text_Size);

			}
			else if (stage_Progress == 5) {
				text("Ç∑+Ç¬=ÇÕ", text_Potition_X, text_Potition_Y);
				text("Ç≠+Ç∑=ÇΩ", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç´+Çª=Çø", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
		}
	}
	void HIRAGANA::STAGE3_INPUT(const char* str) {
		if (stage_Progress == 1) {
			if (strcmp(str, "Ç…Çµ") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 2) {
			if (strcmp(str, "Ç±Ç‹") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 3) {
			if (strcmp(str, "ÇÕÇø") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 4) {
			if (strcmp(str, "Ç»Çµ") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 5) {
			if (strcmp(str, "ÇÕÇΩÇø") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
	}
	void HIRAGANA::STAGE3_HINT() {
		textSize(100);
		fill(255);
		if (HINT_Flag) {
			fill(200);
			rect(0, Tate - 400, 256, 256);
			if (stage_Progress == 1) {
				image(Image[8], 0, Tate - 400);
			}
			else if (stage_Progress == 2) {
				image(Image[9], 0, Tate - 400);
			}
			else if (stage_Progress == 3) {
				image(Image[10], 0, Tate - 400);
			}
			else if (stage_Progress == 4) {
				image(Image[11], 0, Tate - 400);
			}
			else if (stage_Progress == 5) {
				//image(Image[4], 0, Tate - 400);
			}
		}
		if (isTrigger(KEY_H)) {
			if (!HINT_Flag) {
				HINT_Flag = true;
			}
			else if (HINT_Flag) {
				HINT_Flag = false;
			}
		}
		else if ((mouseY > (Tate - 100) && mouseX <= 300)) {
			fill(255, 255, 0);
			if (isTrigger(MOUSE_LBUTTON)) {
				if (!HINT_Flag) {
					HINT_Flag = true;
				}
				else if (HINT_Flag) {
					HINT_Flag = false;
				}
			}
		}
		text("H:HINT", 0, Tate);
	}
	void HIRAGANA::STAGE4_DRAW() {
		fill(255);
		textSize(text_Size);
		Goto_Select_Stage = false;
		Correct_answer();
		if (!correct_Answer) {
			if (stage_Progress == 1) {
				text("ÇÎ+ÇÒ=?", text_Potition_X, text_Potition_Y);
				text("Ç”+Ç‰=?", text_Potition_X, text_Potition_Y + text_Size);
				text("ÇÌ+Ç±=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 2) {
				text("ÇÌ+ÇÍ=?", text_Potition_X, text_Potition_Y);
				text("Çµ+Ç÷=?", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç‰+Çﬂ=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 3) {
				text("Ç§-ÇÒ=?", text_Potition_X, text_Potition_Y);
				text("ÇÈ-ÇÁ=?", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç»-Ç‚=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 4) {
				text("ÇØ-ÇÒ=?", text_Potition_X, text_Potition_Y);
				text("Ç‰-Ç‚=?", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç¢-ÇÒ=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 5) {
				text("Ç”+ÇÍ=?", text_Potition_X, text_Potition_Y);
				text("ÇÎ+Ç»=?", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç‚+Ç–=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
		}
		else {
			if (stage_Progress == 1) {
				text("ÇÎ+ÇÒ=Ç‚", text_Potition_X, text_Potition_Y);
				text("Ç”+Ç‰=Ç©", text_Potition_X, text_Potition_Y + text_Size);
				text("ÇÌ+Ç±=ÇÒ", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 2) {
				text("ÇÌ+ÇÍ=Ç‡", text_Potition_X, text_Potition_Y);
				text("Çµ+Ç÷=Ç‚", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç‰+Çﬂ=Çµ", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 3) {
				text("Ç§-ÇÒ=Ç´", text_Potition_X, text_Potition_Y);
				text("ÇÈ-ÇÁ=Ç¢", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç»-Ç‚=ÇÎ", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 4) {
				text("ÇØ-ÇÒ=Ç∑", text_Potition_X, text_Potition_Y);
				text("Ç‰-Ç‚=Ç¢", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç¢-ÇÒ=Ç©", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 5) {
				text("Ç”+ÇÍ=Çµ", text_Potition_X, text_Potition_Y);
				text("ÇÎ+Ç»=Ç©", text_Potition_X, text_Potition_Y + text_Size);
				text("Ç‚+Ç–=Ç≠", text_Potition_X, text_Potition_Y + (text_Size * 2));
			}
		}
	}
	void HIRAGANA::STAGE4_INPUT(const char* str) {
		if (stage_Progress == 1) {
			if (strcmp(str, "Ç‚Ç©ÇÒ") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 2) {
			if (strcmp(str, "Ç‡Ç‚Çµ") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 3) {
			if (strcmp(str, "Ç´Ç¢ÇÎ") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 4) {
			if (strcmp(str, "Ç∑Ç¢Ç©") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 5) {
			if (strcmp(str, "ÇµÇ©Ç≠") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
	}
	void HIRAGANA::STAGE4_HINT() {
		textSize(100);
		fill(255);
		if (HINT_Flag) {
			fill(200);
			rect(0, Tate - 400, 256, 256);
			if (stage_Progress == 1) {
				image(Image[12], 0, Tate - 400);
			}
			else if (stage_Progress == 2) {
				image(Image[13], 0, Tate - 400);
			}
			else if (stage_Progress == 3) {
				image(Image[14], 0, Tate - 400);
			}
			else if (stage_Progress == 4) {
				image(Image[15], 0, Tate - 400);
			}
			else if (stage_Progress == 5) {
				image(Image[16], 0, Tate - 400);
			}
		}
		if (isTrigger(KEY_H)) {
			if (!HINT_Flag) {
				HINT_Flag = true;
			}
			else if (HINT_Flag) {
				HINT_Flag = false;
			}
		}
		else if ((mouseY > (Tate - 100) && mouseX <= 300)) {
			fill(255, 255, 0);
			if (isTrigger(MOUSE_LBUTTON)) {
				if (!HINT_Flag) {
					HINT_Flag = true;
				}
				else if (HINT_Flag) {
					HINT_Flag = false;
				}
			}
		}
		text("H:HINT", 0, Tate);
	}
	void HIRAGANA::STAGE5_DRAW() {
		fill(255);
		textSize(text_Size);
		Goto_Select_Stage = false;
		Correct_answer();
		if (!correct_Answer) {
			if (stage_Progress == 1) {
				text("Ç≥+ÇÕ+Ç†=?", text_Potition_X - 100, text_Potition_Y);
				text("ÇÌ+ÇÌ+Ç÷=?", text_Potition_X - 100, text_Potition_Y + text_Size);
				text("ÇÕ+ÇÕ+ÇÀ=?", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 2) {
				text("Ç›+Ç´+Ç÷=?", text_Potition_X - 100, text_Potition_Y);
				text("ÇÕ+Ç”+ÇÔ=?", text_Potition_X - 100, text_Potition_Y + text_Size);
				text("Ç»+Ç–+ÇÈ=?", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 3) {
				text("Ç‰-Ç†+Ç›=?", text_Potition_X - 100, text_Potition_Y);
				text("Ç-Ç≥+Çø=?", text_Potition_X - 100, text_Potition_Y + text_Size);
				text("Çµ-Çø+Ç=?", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 4) {
				text("Ç±-Ç≥+Ç‰=?", text_Potition_X - 100, text_Potition_Y);
				text("Ç–-Çﬂ+Ç∑=?", text_Potition_X - 100, text_Potition_Y + text_Size);
				text("Ç¬-Ç‚+Çƒ=?", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 5) {
				text("Çﬂ+ÇÃ+Ç∑=?", text_Potition_X - 100, text_Potition_Y);
				text("ÇΩ-Ç»+Ç≥=?", text_Potition_X - 100, text_Potition_Y + text_Size);
				text("ÇÓ+Ç´+Ç≠=?", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));
			}
		}
		else {
			if (stage_Progress == 1) {
				text("Ç≥+ÇÕ+Ç†=Ç‰", text_Potition_X - 100, text_Potition_Y);
				text("ÇÌ+ÇÌ+Ç÷=Ç©", text_Potition_X - 100, text_Potition_Y + text_Size);
				text("ÇÕ+ÇÕ+ÇÀ=ÇΩ", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 2) {
				text("Ç›+Ç´+Ç÷=Ç≠", text_Potition_X - 100, text_Potition_Y);
				text("ÇÕ+Ç”+ÇÔ=ÇÈ", text_Potition_X - 100, text_Potition_Y + text_Size);
				text("Ç»+Ç–+ÇÈ=Ç‹", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 3) {
				text("Ç‰-Ç†+Ç›=Çπ", text_Potition_X - 100, text_Potition_Y);
				text("Ç-Ç≥+Çø=ÇÒ", text_Potition_X - 100, text_Potition_Y + text_Size);
				text("Çµ-Çø+Ç=ÇÎ", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 4) {
				text("Ç±-Ç≥+Ç‰=Ç›", text_Potition_X - 100, text_Potition_Y);
				text("Ç–-Çﬂ+Ç∑=Ç©", text_Potition_X - 100, text_Potition_Y + text_Size);
				text("Ç¬-Ç‚+Çƒ=ÇÒ", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));
			}
			else if (stage_Progress == 5) {
				text("Çﬂ+ÇÃ+Ç∑=Ç´", text_Potition_X - 100, text_Potition_Y);
				text("ÇΩ-Ç»+Ç≥=Ç©", text_Potition_X - 100, text_Potition_Y + text_Size);
				text("ÇÓ+Ç´+Ç≠=Ç¢", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));
			}
		}
	}
	void HIRAGANA::STAGE5_INPUT(const char* str) {
		if (stage_Progress == 1) {
			if (strcmp(str, "Ç‰Ç©ÇΩ") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 2) {
			if (strcmp(str, "Ç≠ÇÈÇ‹") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 3) {
			if (strcmp(str, "ÇπÇÒÇÎ") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 4) {
			if (strcmp(str, "Ç›Ç©ÇÒ") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
		else if (stage_Progress == 5) {
			if (strcmp(str, "Ç´Ç©Ç¢") == 0) {
				correct_Answer = true; HINT_Flag = false;
			}
		}
	}
	void HIRAGANA::START_STAGE(int num, int mouseX, int mouseY) {
		fill(255);
		textSize(text_Size / 2);
		rectMode(CENTER);
		/*
		if (0 == num) {
			text("Ç†íiÇÃâ¡éZÇ…Ç¬Ç¢ÇƒçlÇ¶Ç‹Ç∑ÅB", 200, text_Potition_Y);
			if ((Yoko / 2) - 450 < mouseX && mouseX < (Yoko / 2) + 450 && 650 < mouseY && mouseY < 950) {
				fill(255, 255, 0);
				if (isTrigger(MOUSE_LBUTTON)) {
					Start_Stage = true;
				}
			}
			rect(Yoko / 2, 800, 900, 300);
			fill(0);
			text("ÇÕÇ∂ÇﬂÇÈ", Yoko/2-350, 650);
		}
		else if (1 == num) {
			text("Ç†íiÇÃå∏éZÇ…Ç¬Ç¢ÇƒçlÇ¶Ç‹Ç∑ÅB", 200, text_Potition_Y);
			if ((Yoko / 2) - 450 < mouseX && mouseX < (Yoko / 2) + 450 && 650 < mouseY && mouseY < 950) {
				fill(255, 255, 0);
				if (isTrigger(MOUSE_LBUTTON)) {
					Start_Stage = true;
				}
			}
			rect(Yoko / 2, 800, 900, 300);
			fill(0);
			text("ÇÕÇ∂ÇﬂÇÈ", Yoko/2-350 ,650);
		}
		else if (2 == num) {
			text("êÊíˆÇ‹Ç≈ÇÃÉãÅ[ÉãÇägí£ÇµÇ‹Ç∑ÅB", 200, text_Potition_Y);
			if ((Yoko / 2) - 450 < mouseX && mouseX < (Yoko / 2) + 450 && 650 < mouseY && mouseY < 950) {
				fill(255, 255, 0);
				if (isTrigger(MOUSE_LBUTTON)) {
					Start_Stage = true;
				}
			}
			rect(Yoko / 2, 800, 900, 300);
			fill(0);
			text("ÇÕÇ∂ÇﬂÇÈ", Yoko/2-350, 650);
		}
		else if (3 == num) {
			text("åJÇËè„Ç™ÇËÇÃÇ†ÇÈåvéZÇ…Ç¬Ç¢ÇƒçlÇ¶Ç‹Ç∑ÅB", 200, text_Potition_Y);
			if ((Yoko / 2) - 450 < mouseX && mouseX < (Yoko / 2) + 450 && 650 < mouseY && mouseY < 950) {
				fill(255, 255, 0);
				if (isTrigger(MOUSE_LBUTTON)) {
					Start_Stage = true;
				}
			}
			rect(Yoko / 2, 800, 900, 300);
			fill(0);
			text("ÇÕÇ∂ÇﬂÇÈ", Yoko/2-350, 650);
		}
		else if (4 == num) {
			text("ë∂ç›ÇµÇ»Ç¢ï∂éöÇ…Ç¬Ç¢ÇƒçlÇ¶Ç‹Ç∑ÅB", 200, text_Potition_Y);
			if ((Yoko / 2) - 450 < mouseX && mouseX < (Yoko / 2) + 450 && 650 < mouseY && mouseY < 950) {
				fill(255, 255, 0);
				if (isTrigger(MOUSE_LBUTTON)) {
					Start_Stage = true;
				}
			}
			rect(Yoko / 2, 800, 900, 300);
			fill(0);
			text("ÇÕÇ∂ÇﬂÇÈ", Yoko/2-350, 650);
		}
		*/
		if (0 == num) {
			text("1.ÉAçsÇÃë´ÇµéZ", 200, text_Potition_Y);
			text("ÉAçsìØémÇÃâ¡éZÇçlÇ¶Ç‹Ç∑ÅB", 200, text_Potition_Y + (text_Size / 2));
		}
		else if (1 == num) {
			text("2.ÉAçsÇÃà¯Ç´éZ", 200, text_Potition_Y);
			text("ÉAçsìØémÇÃå∏éZÇçlÇ¶Ç‹Ç∑ÅB", 200, text_Potition_Y + (text_Size / 2));
		}
		else if (2 == num) {
			text("3.ÉAÅ`ÉìçsÇÃåvéZ1", 200, text_Potition_Y);
			text("ÉAÅ`ÉìçsìØémÇÃâ¡éZÇçlÇ¶Ç‹Ç∑ÅB", 200, text_Potition_Y + (text_Size / 2));
			text("ÉAçsÇÃåvéZÇ‡ê¨ÇËóßÇ¬ÇÊÇ§Ç…", 200, text_Potition_Y + (text_Size + (text_Size / 2)));
			text("åvéZãKë•Çägí£ÇµÇ‹Ç∑ÅB", 200, text_Potition_Y + (text_Size * 2));
		}
		else if (3 == num) {
			text("4.ÉAÅ`ÉìçsÇÃåvéZ2", 200, text_Potition_Y);
			text("åJÇËè„Ç™ÇËÇÃÇ†ÇÈ", 200, text_Potition_Y + (text_Size / 2));
			text("â¡éZÇ∆å∏éZÇçlÇ¶Ç‹Ç∑ÅB", 200, text_Potition_Y + text_Size);
		}
		else if (4 == num) {
			text("5.ÉAÅ`ÉìçsÇÃåvéZ3", 200, text_Potition_Y);
			text("ë∂ç›ÇµÇ»Ç¢ï∂éöÇÃàµÇ¢ÇçlÇ¶Ç‹Ç∑ÅB", 200, text_Potition_Y + (text_Size / 2));
		}
		if ((Yoko / 2) - 450 < mouseX && mouseX < (Yoko / 2) + 450 && 650 < mouseY && mouseY < 950) {
			fill(255, 255, 0);
			if (isTrigger(MOUSE_LBUTTON)) {
				Start_Stage = true;
			}
		}
		rect(Yoko / 2, 800, 900, 300);
		fill(0);
		text("ÇÕÇ∂ÇﬂÇÈ", Yoko / 2 - 150, 850);

		//BOTTOM, TOP, BCENTER, MBCENTER.
		rectMode(CORNER);
	}
	bool HIRAGANA::SENT_START_STAGE_FLAG() {
		return Start_Stage;
	}
	void HIRAGANA::FLAG_INIT() {
		Goto_Select_Stage = false;
		Start_Stage = false;
		stage_Progress = 1;
		HINT_Flag = false;
	}
	bool HIRAGANA::GOTO_SELECT_STAGE(){
		return Goto_Select_Stage;
	}
	bool HIRAGANA::How_To_Play() {
		textSize(100);
		fill(250);
		if (mouseX < 450 && mouseY>(Tate-100)) {
			fill(255, 255, 0);
			if (isTrigger(MOUSE_LBUTTON)) {
				return true;
			}
		}
		text("AÅFóVÇ—ï˚", 0, Tate);
		return false;
	}
	void HIRAGANA::Image_How_To_Play() {
		image(How_To_Image, 0, 0);
	}
	void HIRAGANA::Correct_answer() {
		if (correct_Answer == true) {
			fill(255);
			rect(1500, 930, 500, 200);
			if (1500 < mouseX && 930 < mouseY) {
				fill(0, 255, 255);
				rect(1500, 930, 500, 200);
				if (isTrigger(MOUSE_LBUTTON)) {
					if (stage_Progress == 5) {
						stage_Progress = 1;
						Goto_Select_Stage = true;
						correct_Answer = false;
					}
					else {
						stage_Progress++;
						correct_Answer = false;
					}
				}
			}
			textSize(150);
			fill(0);
			text("ê≥â!", 1500, 930);
			text("éüÇ÷", 1500, 1080);
			fill(255, 0, 0);
			circle(Yoko / 2, Tate / 3, 700);
			fill(190);
			circle(Yoko / 2, Tate / 3, 600);
			fill(255);
		}
		fill(0);
		textSize(text_Size);
	}
}