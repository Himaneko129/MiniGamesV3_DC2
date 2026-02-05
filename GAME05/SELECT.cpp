#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME05.h"
#include"SELECT.h"
namespace GAME05 {
	void SELECT::INIT_for_SELECT() {
		SELECT_BLOCK_HEIGHT = height / 2;
		SELECT_BLOCK_WIDTH = width / 2;
		STAGE1_positionX = 0;
		STAGE1_positionY = 0;
		STAGE2_positionX = width/2;
		STAGE2_positionY = 0;
		STAGE3_positionX = 0;
		STAGE3_positionY = height/2;
		STAGE4_positionX = width/2;
		STAGE4_positionY = height/2;
		mic_Image = loadImage("..\\MAIN\\assets\\game05\\mic_mute.png");
	}
	void SELECT::DRAW_for_SELECT(class PLAYER* p_pointer) {
		if (p_pointer->Player_X+p_pointer->Player_Width/2 > width / 2) {
			if (p_pointer->Player_Y + p_pointer->Player_Height/2 > height / 2) {
				fill(200);
				rect(STAGE4_positionX, STAGE4_positionY, SELECT_BLOCK_WIDTH , SELECT_BLOCK_HEIGHT);
				fill(0);
				rect(STAGE3_positionX, STAGE3_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				rect(STAGE2_positionX, STAGE2_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				rect(STAGE1_positionX, STAGE1_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				STAGE4_select = 1;
				STAGE3_select = 0;
				STAGE2_select = 0;
				STAGE1_select = 0;
			}
			//else if (Last_Player_Y < height / 2) {
			else{
				fill(200);
				rect(STAGE2_positionX, STAGE2_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				fill(0);
				rect(STAGE4_positionX, STAGE4_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				rect(STAGE3_positionX, STAGE3_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				rect(STAGE1_positionX, STAGE1_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				STAGE2_select = 1;
				STAGE4_select = 0;
				STAGE3_select = 0;
				STAGE1_select = 0;
			}
		}
		//else if (p_pointer->Last_Player_X < width / 2) {
		else{
			if (p_pointer->Player_Y + p_pointer->Player_Height/2 > height / 2) {
				fill(200);
				rect(STAGE3_positionX, STAGE3_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				fill(0);
				rect(STAGE4_positionX, STAGE4_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				rect(STAGE2_positionX, STAGE2_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				rect(STAGE1_positionX, STAGE1_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				STAGE3_select = 1;
				STAGE4_select = 0;
				STAGE2_select = 0;
				STAGE1_select = 0;
			}
			//else if (Last_Player_Y < height / 2) {
			else{
				fill(200);
				rect(STAGE1_positionX, STAGE1_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				fill(0);
				rect(STAGE2_positionX, STAGE2_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				rect(STAGE3_positionX, STAGE3_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				rect(STAGE4_positionX, STAGE4_positionY, SELECT_BLOCK_WIDTH, SELECT_BLOCK_HEIGHT);
				STAGE1_select = 1;
				STAGE2_select = 0;
				STAGE3_select = 0;
				STAGE4_select = 0;
			}
		}
	}
	void SELECT::DRAW_MIC() {
		image(mic_Image,width-100 ,height-150 );
	}
	void SELECT::MOVE_AREA(class PLAYER* p_pointer) {
		if (p_pointer->Player_X<0 || p_pointer->Player_X+p_pointer->Player_Width>width) {
			p_pointer->Player_X = p_pointer->Last_Player_X;
		}
		if (p_pointer->Player_Y<0 || p_pointer->Player_Y+p_pointer->Player_Height>height) {
			p_pointer->Player_Y = p_pointer->Last_Player_Y;
		}
	}
	void SELECT::select_text() {
		textSize(50);
		text("[Artcore][House]", 25, height / 4+100);
		text("[Hardcore][Gabba][Jersey club]", (width / 2) + 50, height / 4+100);
		text("[Drum'n'bass][CROSSBREED]", 50, height - (height / 4)+100);
		textSize(100);
		text("STAGE1", 50, height / 4);
		text("STAGE3", (width / 2) + 50, height / 4);
		text("STAGE2", 50, height - (height / 4));
		text("STAGE4", (width / 2) + 50, height - (height / 4));
		//text("COMING SOON...", 50, height - (height / 4)+100);
		text("COMING SOON...", (width / 2) + 50, height - (height / 4) + 100);
		textSize(50);
		fill(128);
		text("'F' : SELECT_GAME", 750, height / 2+25);
		text("'M':Mute", width - 200, height - 200);
	}
	int SELECT::STAGE_SELECT() {
		if (STAGE1_select == 1) {
			return 1;
		}
		else if (STAGE2_select == 1) {
			return 2;
		}
		else if (STAGE3_select == 1) {
			return 3;
		}
		else if (STAGE4_select == 1) {
			return 4;
		}
		else {

		}
	}
}