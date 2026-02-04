#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME14.h"
namespace GAME14
{
	int GAME::create()
	{
		game_scene = new GAME_SCENE;
		input = new INPUT;
		hiragana = new HIRAGANA;
		exploit = new EXPLOIT;
		exploit->SET_IMAGE();
		return 0;
	}

	void GAME::destroy()
	{
		delete input;
		delete game_scene;
		delete hiragana;
		delete exploit;
	}

	void GAME::proc()
	{
		clear(0);
		if (game_scene->now_game == game_scene->CHOOSE) {
			game_scene->GAME_SELECT();
			//clear(0, 0, 64);
			textSize(50);
			fill(255, 255, 0);
			text("GAME14", 0, 100);
			fill(255);
			text("ENTERキーでメニューに戻る", 0, 1080);
			if (isTrigger(MOUSE_LBUTTON) == 1 && game_scene->GAME_SELECT() == 1) {
				game_scene->now_game = game_scene->HIRAGANA;
				game_scene->game_state = game_scene->INIT;
			}
			if (isTrigger(MOUSE_LBUTTON) == 1 && game_scene->GAME_SELECT() == 2) {
				game_scene->now_game = game_scene->EXPLOIT;
				game_scene->game_state = game_scene->INIT;
			}
			if (isTrigger(KEY_ENTER)) {
				main()->backToMenu();
			}
		}
		else if (game_scene->now_game == game_scene->HIRAGANA) {
			clear(190);
			if (game_scene->game_state == game_scene->INIT) {
				input->INIT();
				hiragana->TITLE_INIT();
				hiragana->IMAGE_SET_INIT();
				game_scene->game_state = game_scene->TITLE;
			}
			else if (game_scene->game_state == game_scene->TITLE) {
				if (hiragana->TITLE_DRAW() == 2) {
					game_scene->game_state = game_scene->SELECT;
				}
				else if (hiragana->TITLE_DRAW() == 1) {
					game_scene->now_game = game_scene->CHOOSE;
					game_scene->game_state = game_scene->TITLE;
				}
			}
			else if (game_scene->game_state == game_scene->OPTION) {
				hiragana->Image_How_To_Play();
				textSize(100);
				fill(0);
				text("A：セレクト画面へ", 5, Tate+5);
				fill(255);
				if (isTrigger(KEY_A)) {
					game_scene->game_state = game_scene->SELECT;
				}
				if (mouseX < 850 && mouseY>(Tate - 100)) {
					fill(255, 255, 0);
					if (isTrigger(MOUSE_LBUTTON)) {
						game_scene->game_state = game_scene->SELECT;
					}
				}
				text("A：セレクト画面へ", 0, Tate);
			}
			/*
			else if (game_scene->game_state == game_scene->SELECT) {
				if (input->SELECT_MOUSE_INPUT(mouseX, mouseY)==0) {
					game_scene->now_stage = game_scene->stage1;
					game_scene->game_state = game_scene->PLAY;
				}
				else if (input->SELECT_MOUSE_INPUT(mouseX, mouseY) == 1) {
					game_scene->now_stage = game_scene->stage2;
					game_scene->game_state = game_scene->PLAY;
				}
				else if (input->SELECT_MOUSE_INPUT(mouseX, mouseY) == 2) {
					game_scene->now_stage = game_scene->stage3;
					game_scene->game_state = game_scene->PLAY;
				}
				else if (input->SELECT_MOUSE_INPUT(mouseX, mouseY) == 3) {
					game_scene->now_stage = game_scene->stage4;
					game_scene->game_state = game_scene->PLAY;
				}
				else if (input->SELECT_MOUSE_INPUT(mouseX, mouseY) == 4) {
					game_scene->now_stage = game_scene->stage5;
					game_scene->game_state = game_scene->PLAY;
				}
				input->DRAW_SELECT(mouseX, mouseY);
			}
			*/
			else if (game_scene->game_state == game_scene->SELECT) {
				//hiragana->How_To_Play();
				int result = input->SELECT_MOUSE_INPUT(mouseX, mouseY);  // ← ここで一度だけ呼ぶ！
				if (input->BACK_SCENE(mouseX, mouseY) == true) {
					game_scene->game_state = game_scene->TITLE;
				}
				if (result == 0) {
					game_scene->now_stage = game_scene->stage1;
					game_scene->game_state = game_scene->PLAY;
				}
				else if (result == 1) {
					game_scene->now_stage = game_scene->stage2;
					game_scene->game_state = game_scene->PLAY;
				}
				else if (result == 2) {
					game_scene->now_stage = game_scene->stage3;
					game_scene->game_state = game_scene->PLAY;
				}
				else if (result == 3) {
					game_scene->now_stage = game_scene->stage4;
					game_scene->game_state = game_scene->PLAY;
				}
				else if (result == 4) {
					game_scene->now_stage = game_scene->stage5;
					game_scene->game_state = game_scene->PLAY;
				}
				if (isTrigger(KEY_A)||hiragana->How_To_Play()) {
					game_scene->game_state = game_scene->OPTION;
				}
				input->DRAW_SELECT(mouseX, mouseY);
			}
			else if (game_scene->game_state == game_scene->PLAY) {
				if (game_scene->now_stage == game_scene->stage1) {
					if (hiragana->SENT_START_STAGE_FLAG() == false) {
						hiragana->START_STAGE(0, mouseX, mouseY);
						if (input->BACK_SCENE(mouseX, mouseY) == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
					}
					else if (hiragana->SENT_START_STAGE_FLAG() == true) {
						input->MOUSE_INPUT(mouseX, mouseY);
						input->KEYBOARD(mouseX, mouseY);
						input->SHOW_INPUT();
						hiragana->STAGE1_DRAW();
						hiragana->STAGE1_HINT();
						hiragana->STAGE1_INPUT(input->Sent_text());
						if (hiragana->GOTO_SELECT_STAGE() == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
						if (input->BACK_SCENE(mouseX, mouseY) == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
					}
				}
				else if (game_scene->now_stage == game_scene->stage2) {
					if (hiragana->SENT_START_STAGE_FLAG() == false) {
						hiragana->START_STAGE(1, mouseX, mouseY);
						if (input->BACK_SCENE(mouseX, mouseY) == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
					}
					else if (hiragana->SENT_START_STAGE_FLAG() == true) {
						input->MOUSE_INPUT(mouseX, mouseY);
						input->KEYBOARD(mouseX, mouseY);
						input->SHOW_INPUT();
						hiragana->STAGE2_DRAW();
						hiragana->STAGE2_HINT();
						hiragana->STAGE2_INPUT(input->Sent_text());
						if (hiragana->GOTO_SELECT_STAGE() == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
						if (input->BACK_SCENE(mouseX, mouseY) == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
					}
				}
				else if (game_scene->now_stage == game_scene->stage3) {
					if (hiragana->SENT_START_STAGE_FLAG() == false) {
						hiragana->START_STAGE(2, mouseX, mouseY);
						if (input->BACK_SCENE(mouseX, mouseY) == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
					}
					else if (hiragana->SENT_START_STAGE_FLAG() == true) {
						input->MOUSE_INPUT(mouseX, mouseY);
						input->KEYBOARD(mouseX, mouseY);
						input->SHOW_INPUT();
						hiragana->STAGE3_DRAW();
						hiragana->STAGE3_HINT();
						hiragana->STAGE3_INPUT(input->Sent_text());
						if (hiragana->GOTO_SELECT_STAGE() == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
						if (input->BACK_SCENE(mouseX, mouseY) == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
					}
				}
				else if (game_scene->now_stage == game_scene->stage4) {
					if (hiragana->SENT_START_STAGE_FLAG() == false) {
						hiragana->START_STAGE(3, mouseX, mouseY);
						if (input->BACK_SCENE(mouseX, mouseY) == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
					}
					else if (hiragana->SENT_START_STAGE_FLAG() == true) {
						input->MOUSE_INPUT(mouseX, mouseY);
						input->KEYBOARD(mouseX, mouseY);
						input->SHOW_INPUT();
						hiragana->STAGE4_DRAW();
						hiragana->STAGE4_HINT();
						hiragana->STAGE4_INPUT(input->Sent_text());
						if (hiragana->GOTO_SELECT_STAGE() == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
						if (input->BACK_SCENE(mouseX, mouseY) == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
					}
				}
				else if (game_scene->now_stage == game_scene->stage5) {
					if (hiragana->SENT_START_STAGE_FLAG() == false) {
						hiragana->START_STAGE(4, mouseX, mouseY);
						if (input->BACK_SCENE(mouseX, mouseY) == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
					}
					else if (hiragana->SENT_START_STAGE_FLAG() == true) {
						input->MOUSE_INPUT(mouseX, mouseY);
						input->KEYBOARD(mouseX, mouseY);
						input->SHOW_INPUT();
						hiragana->STAGE5_DRAW();
						hiragana->STAGE5_INPUT(input->Sent_text());
						if (hiragana->GOTO_SELECT_STAGE() == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
						if (input->BACK_SCENE(mouseX, mouseY) == true) {
							game_scene->game_state = game_scene->SELECT;
							hiragana->FLAG_INIT();
						}
					}
				}
			}
		}
		else if (game_scene->now_game == game_scene->EXPLOIT) {
			if (game_scene->game_state == game_scene->INIT) {
				exploit->INIT();
				exploit->PLAY_INIT();
				game_scene->game_state = game_scene->TITLE;
			}
			else if (game_scene->game_state == game_scene->TITLE) {
				if (exploit->TITLE_DRAW() == 2) {
					game_scene->game_state = game_scene->SELECT;
				}
				else if (exploit->TITLE_DRAW() == 1) {
					game_scene->now_game = game_scene->CHOOSE;
					game_scene->game_state = game_scene->TITLE;
				}
			}
			else if (game_scene->game_state == game_scene->OPTION) {

			}
			else if (game_scene->game_state == game_scene->SELECT) {
				textSize(200);
				fill(255, 0, 0);
				text("PLAY_START", 500, 300);
				text("Press_SPACE", 450, 500);
				if (isTrigger(KEY_SPACE)) {
					game_scene->game_state = game_scene->PLAY;
				}
			}
			else if (game_scene->game_state == game_scene->PLAY) {
				exploit->Setup_Cell_color();
				exploit->RULE_IMAGE();
				exploit->Draw_Board();
				exploit->DRAW_Game_Finish();
				//exploit->DEBUG_DRAW();
				if (exploit->CHANGE_Turn()) {
					if (isTrigger(MOUSE_LBUTTON)) {
						int r, c;
						if (exploit->Mouse_To_Cell(mouseX, mouseY, r, c)) {
							exploit->Click_Cell(r, c);
						}
					}
					else if (isTrigger(MOUSE_RBUTTON)) {
						exploit->Select_Cancel();
					}
					if (exploit->Sent_gameOver()) {
						if (isTrigger(KEY_SPACE)) {
							game_scene->game_state = game_scene->SELECT;
							exploit->INIT();
							exploit->PLAY_INIT();
						}
					}
				}
				if (exploit->Back_TITLE()) {
					game_scene->game_state = game_scene->INIT;
				}
			}

		}

	}
}
