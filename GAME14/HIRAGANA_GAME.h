#pragma once
#include "GAME14.h"
namespace GAME14 {
	class HIRAGANA {
		int WIDTH = 0;
		int HEIGHT = 0;
		float Position_X = 0;
		float Position_Y = 0;
		float Position_X_2 = 0;
		float Position_Y_2 = 0;
		int stage_Progress = 0;
		int text_Potition_X = 0;
		int text_Potition_Y = 0;
		int text_Size = 0;
		bool Goto_Select_Stage = false;
		bool Start_Stage = false;
		bool correct_Answer = false;
		bool HINT_Flag = false;
		int Image[17] = {};
		int How_To_Image = 0;
	public:
		void IMAGE_SET_INIT();
		void TITLE_INIT();
		int TITLE_DRAW();
		bool MOUSE_JUDGE(int WIDTH,int HEIGHT, float Position_X, float Position_Y);
		void STAGE1_DRAW();
		void STAGE1_INPUT(const char* str);
		void STAGE1_HINT();
		void STAGE2_DRAW();
		void STAGE2_INPUT(const char* str);
		void STAGE2_HINT();
		void STAGE3_DRAW();
		void STAGE3_INPUT(const char* str);
		void STAGE3_HINT();
		void STAGE4_DRAW();
		void STAGE4_INPUT(const char* str);
		void STAGE4_HINT();
		void STAGE5_DRAW();
		void STAGE5_INPUT(const char* str);
		//void STAGE5_HINT();
		void START_STAGE(int num,int mouseX,int mouseY);
		bool How_To_Play();
		bool GOTO_SELECT_STAGE();
		bool SENT_START_STAGE_FLAG();
		void FLAG_INIT();
		void Correct_answer();
		void Image_How_To_Play();
	};
}