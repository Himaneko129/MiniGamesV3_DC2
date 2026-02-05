#pragma once
#include"GAME01.h"
#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include <cstdlib>
#include<cstring>
namespace GAME01 {
	struct KanjiData {
		int img;                // 画像ID
		const char* yomi;       // 正解の読み
	};
	class KANJI {
	private:
		int select2 = 0;
		static const int KANJI_MAX = 58;
		KanjiData kanji[KANJI_MAX];
		int kanjiCount = 0;
		int currentKanji = 0;
		char inputStrB[32] = "";    // 入力文字
		char displayStr[64] = "";
		int inputLenB = 0;
		void loadKanjiImages();
		bool romajiToKana(const char* src, char* dst);
		bool KanswerChecked = false;
		bool KanswerCorrect = false;
		bool Meter = false;
		int correctCount = 0;   // 今回の10問用カウンタ (0?10)
		char fixedKana[128];     // 確定したひらがな
		int point = 0;          // 累計ポイント（保存される
		char pendingRoma[8];     // 未確定ローマ字（最大3で足りる）
		char inputRoma[128];     // ローマ字全文（判定用）
		bool rewardGiven;
		static int Qpoint;   // 問題回答数
		static int Apoint;   // 正解数
		static void saveQA();
		static void loadQA();
		float accuracyRate = 0.0f;   // 正解率（%）
	public:
		static int cont;
		bool Kanser1Generated = false;
		void game();
		void Kanser1();
		void updateDisplay();
		void key();
		void proc();
		void initialize();
		void Leftinitialize();
		void savePoint();
		void loadPoint();
		void drawMeter(float x,float y);
		void updateStatistics();
		static KANJI* kanji1();
		int kanjiImg;   // 　　　漢字画像ID
		static int correctStreak;   // 現在の正解数（0～10）
		int totalPoint;     // 所持ポイント
		int Kans = 0;
	};
}