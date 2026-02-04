#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME01.h"
#include "kanji.h"
#include"windows.h"
#include<cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
namespace GAME01 {
	int GAME01::KANJI::cont = 0;
	int GAME01::KANJI::correctStreak = 0;
	int GAME01::KANJI::Qpoint = 0;
	int GAME01::KANJI::Apoint = 0;
	void KANJI::game() {
		clear(0, 0, 64);
		textSize(75);
		fill(255, 0, 0);
		text("漢字問題モード＞＞＞＞＞＞", 20, 100);
		textSize(55);
		fill(255, 255, 255);
		text("準備が出来たらスタート！※「」内のキーを入力すると確定。", 20, 200);
		text("", 20, 280);
		text("[←]キーでメニューに戻る", 90, 1000);
		fill(100, 120, 105);
		rect(110, 400, 470, 200);
		textSize(45);
		fill(0, 0, 0);
		text("ＳＴＡＲＴ「→」", 150, 530);
		if (KANJI::cont == 1) {
			textSize(50);
			fill(255);
			text("漢字:コンテニュー", 1220, 1080);
		}
		fill(255, 255, 255);
		text("＜＜＜統計＞＞＞", 820, 300);
		char buf[128];
		sprintf_s(buf, "回答数:%d", Qpoint);
		textSize(50);
		text(buf, 820, 380);
		sprintf_s(buf, "正解数:%d", Apoint);
		text(buf, 820, 430);
		sprintf_s(buf, "正解率: %.2f%%", accuracyRate);
		text(buf, 820, 480);
		textSize(30);
		text("※　　注意　　※", 820, 630);
		text("〇キーボード入力中に「半角／全角(漢字)」キーを押さないでください。", 820, 680);
	}
	void KANJI::Kanser1() {
		if (!Kanser1Generated && kanjiCount >= 0) {
			currentKanji = random(0, kanjiCount - 1);
			Kanser1Generated = true;
		}
		fill(0, 0, 0);
		clear(255, 255, 255);
		textSize(60);
		text("上の漢字の読み方を答えてください。SPACEで確定。", 20, 700);
		text("※下線部のついてる漢字は下線部の部分のみ答えて下さい", 20, 770);
		textSize(55);
		fill(116, 27, 124);
		text("【　[←]キーでメニューに戻る", 90, 1000);
		text("[↓]キーで1文字削除　】", 1000, 1000);
		fill(255, 255, 0);
		if (kanjiCount > 0) {
			image(kanji[currentKanji].img, 120, 100);
	    }
		fill(255, 255, 0);
	}

	bool KANJI::romajiToKana(const char* src, char* dst) {

		struct RK { const char* r; const char* k; };
		static const RK table[] = {
			// ===== 拗音（清音）=====
			{"kya","きゃ"},{"kyu","きゅ"},{"kyo","きょ"},
			{"sya","しゃ"},{"syu","しゅ"},{"syo","しょ"},
			{"sha","しゃ"},{"shu","しゅ"},{"sho","しょ"},
			{"tya","ちゃ"},{"tyu","ちゅ"},{"tyo","ちょ"},
			{"cha","ちゃ"},{"chu","ちゅ"},{"cho","ちょ"},
			{"nya","にゃ"},{"nyu","にゅ"},{"nyo","にょ"},
			{"hya","ひゃ"},{"hyu","ひゅ"},{"hyo","ひょ"},
			{"mya","みゃ"},{"myu","みゅ"},{"myo","みょ"},
			{"rya","りゃ"},{"ryu","りゅ"},{"ryo","りょ"},

			// ===== 拗音（濁音・半濁音）=====
			{"gya","ぎゃ"},{"gyu","ぎゅ"},{"gyo","ぎょ"},
			{"zya","じゃ"},{"zyu","じゅ"},{"zyo","じょ"},
			{"ja","じゃ"},{"ju","じゅ"},{"jo","じょ"},
			{"bya","びゃ"},{"byu","びゅ"},{"byo","びょ"},
			{"pya","ぴゃ"},{"pyu","ぴゅ"},{"pyo","ぴょ"},

			// ===== 清音 =====
			{"a","あ"},{"i","い"},{"u","う"},{"e","え"},{"o","お"},
			{"ka","か"},{"ki","き"},{"ku","く"},{"ke","け"},{"ko","こ"},
			{"sa","さ"},{"si","し"},{"su","す"},{"se","せ"},{"so","そ"},
			{"ta","た"},{"ti","ち"},{"tu","つ"},{"te","て"},{"to","と"},
			{"na","な"},{"ni","に"},{"nu","ぬ"},{"ne","ね"},{"no","の"},
			{"ha","は"},{"hi","ひ"},{"hu","ふ"},{"fu","ふ"},{"he","へ"},{"ho","ほ"},
			{"ma","ま"},{"mi","み"},{"mu","む"},{"me","め"},{"mo","も"},
			{"ya","や"},{"yu","ゆ"},{"yo","よ"},
			{"ra","ら"},{"ri","り"},{"ru","る"},{"re","れ"},{"ro","ろ"},
			{"wa","わ"},{"wo","を"},

			// ===== 濁音 =====
			{"ga","が"},{"gi","ぎ"},{"gu","ぐ"},{"ge","げ"},{"go","ご"},
			{"za","ざ"},{"zi","じ"},{"zu","ず"},{"ze","ぜ"},{"zo","ぞ"},
			{"da","だ"},{"di","ぢ"},{"du","づ"},{"de","で"},{"do","ど"},
			{"ba","ば"},{"bi","び"},{"bu","ぶ"},{"be","べ"},{"bo","ぼ"},

			// ===== 半濁音 =====
			{"pa","ぱ"},{"pi","ぴ"},{"pu","ぷ"},{"pe","ぺ"},{"po","ぽ"},

			// ===== 特殊ローマ字 =====
			{"shi","し"},{"chi","ち"},{"tsu","つ"},
			{"ji","じ"},

			// ===== 促音（小さい っ）=====
			{"xtu","っ"},{"xtsu","っ"},
			{"ltu","っ"}, { "ltsu","っ" },
			
			// ===== 小文字 =====
			{"xa","ぁ"}, {"xi","ぃ"}, {"xu","ぅ"}, {"xe","ぇ"}, {"xo","ぉ"},
			{"xya","ゃ"}, {"xyu","ゅ"}, {"xyo","ょ"},
			{"lya","ゃ"}, {"lyu","ゅ"}, {"lyo","ょ"},

			// ===== ん =====
			{"nn","ん"},

			// ===== その他 =====
			{"kka","っか"},
		};

	for (auto& e : table) {
		if (strcmp(src, e.r) == 0) {
			strcpy_s(dst, 8, e.k);
			return true;
		}
	}
	return false;
}

	void KANJI::updateDisplay() {
		strcpy_s(displayStr, fixedKana);
		strcat_s(displayStr, pendingRoma);
	}

	void KANJI::loadKanjiImages() {
		if (kanjiCount > 0) return;

		kanji[0] = { loadImage("..\\MAIN\\assets\\game01\\kanji1.png"), "じごく" };
		kanji[1] = { loadImage("..\\MAIN\\assets\\game01\\kanji2.png"), "えこひいき" };
		kanji[2] = { loadImage("..\\MAIN\\assets\\game01\\kanji3.png"), "しんれい" };
		kanji[3] = { loadImage("..\\MAIN\\assets\\game01\\kanji4.png"), "いせき" };
		kanji[4] = { loadImage("..\\MAIN\\assets\\game01\\kanji5.png"), "つきぎめ" };
		kanji[5] = { loadImage("..\\MAIN\\assets\\game01\\kanji6.png"), "どうとく" };
		kanji[6] = { loadImage("..\\MAIN\\assets\\game01\\kanji7.png"), "うんぱん" };
		kanji[7] = { loadImage("..\\MAIN\\assets\\game01\\kanji8.png"), "はぐく" };
		kanji[8] = { loadImage("..\\MAIN\\assets\\game01\\kanji9.png"), "にゅうがくしき" };
		kanji[9] = { loadImage("..\\MAIN\\assets\\game01\\kanji10.png"), "へんこう" };
		kanji[10] = { loadImage("..\\MAIN\\assets\\game01\\kanji11.png"), "ふへんてき" };
		kanji[11] = { loadImage("..\\MAIN\\assets\\game01\\kanji12.png"), "さば" };
		kanji[12] = { loadImage("..\\MAIN\\assets\\game01\\kanji13.png"), "ようにん" };
		kanji[13] = { loadImage("..\\MAIN\\assets\\game01\\kanji14.png"), "ふっかつ" };
		kanji[14] = { loadImage("..\\MAIN\\assets\\game01\\kanji15.png"), "とそう" };
		kanji[15] = { loadImage("..\\MAIN\\assets\\game01\\kanji16.png"), "ひしがた" };
		kanji[16] = { loadImage("..\\MAIN\\assets\\game01\\kanji17.png"), "さおとめ" };
		kanji[17] = { loadImage("..\\MAIN\\assets\\game01\\kanji18.png"), "かたず" };
		kanji[18] = { loadImage("..\\MAIN\\assets\\game01\\kanji19.png"), "ちょうしゅう" };
		kanji[19] = { loadImage("..\\MAIN\\assets\\game01\\kanji20.png"), "いぞん" };
		kanji[20] = { loadImage("..\\MAIN\\assets\\game01\\kanji21.png"), "ひょうへん" };
		kanji[21] = { loadImage("..\\MAIN\\assets\\game01\\kanji22.png"), "うるお" };
		kanji[22] = { loadImage("..\\MAIN\\assets\\game01\\kanji23.png"), "ひれつ" };
		kanji[23] = { loadImage("..\\MAIN\\assets\\game01\\kanji24.png"), "あいしゅう" };
		kanji[24] = { loadImage("..\\MAIN\\assets\\game01\\kanji25.png"), "おうか" };
		kanji[25] = { loadImage("..\\MAIN\\assets\\game01\\kanji26.png"), "こせきとうほん" };
		kanji[26] = { loadImage("..\\MAIN\\assets\\game01\\kanji27.png"), "かわせ" };
		kanji[27] = { loadImage("..\\MAIN\\assets\\game01\\kanji28.png"), "とそう" };
		kanji[28] = { loadImage("..\\MAIN\\assets\\game01\\kanji29.png"), "きょうじ" };
		kanji[29] = { loadImage("..\\MAIN\\assets\\game01\\kanji30.png"), "しょくざい" };
		kanji[30] = { loadImage("..\\MAIN\\assets\\game01\\kanji31.png"), "うんちく" };
		kanji[31] = { loadImage("..\\MAIN\\assets\\game01\\kanji32.png"), "ひまわり" };
		kanji[32] = { loadImage("..\\MAIN\\assets\\game01\\kanji33.png"), "かじ" };
		kanji[33] = { loadImage("..\\MAIN\\assets\\game01\\kanji34.png"), "ぶさた" };
		kanji[34] = { loadImage("..\\MAIN\\assets\\game01\\kanji35.png"), "あいづち" };
		kanji[35] = { loadImage("..\\MAIN\\assets\\game01\\kanji36.png"), "いかん" };
		kanji[36] = { loadImage("..\\MAIN\\assets\\game01\\kanji37.png"), "ひやく" };
		kanji[37] = { loadImage("..\\MAIN\\assets\\game01\\kanji38.png"), "はんざつ" };
		kanji[38] = { loadImage("..\\MAIN\\assets\\game01\\kanji39.png"), "こんざつ" };
		kanji[39] = { loadImage("..\\MAIN\\assets\\game01\\kanji40.png"), "ようや" };
		kanji[40] = { loadImage("..\\MAIN\\assets\\game01\\kanji41.png"), "いあつてき" };
		kanji[41] = { loadImage("..\\MAIN\\assets\\game01\\kanji42.png"), "こんりゅう" };
		kanji[42] = { loadImage("..\\MAIN\\assets\\game01\\kanji43.png"), "ようし" };
		kanji[43] = { loadImage("..\\MAIN\\assets\\game01\\kanji44.png"), "じゅんたく" };
		kanji[44] = { loadImage("..\\MAIN\\assets\\game01\\kanji45.png"), "じゅんかつゆ" };
		kanji[45] = { loadImage("..\\MAIN\\assets\\game01\\kanji46.png"), "たまねぎ" };
		kanji[46] = { loadImage("..\\MAIN\\assets\\game01\\kanji47.png"), "とうがらし" };
		kanji[47] = { loadImage("..\\MAIN\\assets\\game01\\kanji48.png"), "くじゅう" };
		kanji[48] = { loadImage("..\\MAIN\\assets\\game01\\kanji49.png"), "ねんしょう" };
		kanji[49] = { loadImage("..\\MAIN\\assets\\game01\\kanji50.png"), "ふほう" };
		kanji[50] = { loadImage("..\\MAIN\\assets\\game01\\kanji51.png"), "せいきょ" };
		kanji[51] = { loadImage("..\\MAIN\\assets\\game01\\kanji52.png"), "かいぎてき" };
		kanji[52] = { loadImage("..\\MAIN\\assets\\game01\\kanji53.png"), "たんのう" };
		kanji[53] = { loadImage("..\\MAIN\\assets\\game01\\kanji54.png"), "めまい" };
		kanji[54] = { loadImage("..\\MAIN\\assets\\game01\\kanji55.png"), "いわゆる" };
		kanji[55] = { loadImage("..\\MAIN\\assets\\game01\\kanji56.png"), "あなが" };
		kanji[56] = { loadImage("..\\MAIN\\assets\\game01\\kanji57.png"), "けんじょうご" };
		kanji[57] = { loadImage("..\\MAIN\\assets\\game01\\kanji58.png"), "しんこう" };

		kanjiCount = 58;
	}

	void KANJI::savePoint() {
		std::ofstream ofs("..\\MAIN\\assets\\game01\\kanji_point.txt");
		ofs << totalPoint;
	}

	void KANJI::loadPoint() {
		std::ifstream ifs("..\\MAIN\\assets\\game01\\kanji_point.txt");
		if (ifs) {
			ifs >> totalPoint;
		}
		else {
			totalPoint = 0;
		}
	}

	void GAME01::KANJI::saveQA() {
		{
			std::ofstream ofs("..\\MAIN\\assets\\game01\\Qpoint.txt");
			ofs << Qpoint;
		}
		{
			std::ofstream ofs("..\\MAIN\\assets\\game01\\Apoint.txt");
			ofs << Apoint;
		}
	}

	void GAME01::KANJI::loadQA() {
		{
			std::ifstream ifs("..\\MAIN\\assets\\game01\\Qpoint.txt");
			if (ifs) ifs >> Qpoint;
			else Qpoint = 0;
		}
		{
			std::ifstream ifs("..\\MAIN\\assets\\game01\\Apoint.txt");
			if (ifs) ifs >> Apoint;
			else Apoint = 0;
		}
	}

	void KANJI::drawMeter(float x, float y) {
		float maxWidth = 300;
		float height = 25;

		// 枠
		fill(255, 253, 85);
		rect(x, y, maxWidth, height);

		// 中身
		fill(0, 200, 100);
		float w = (correctStreak * maxWidth) / 10;
		rect(x, y, w, height);

		// テキスト
		char buf[64];
		sprintf_s(buf, "%d / 10", correctStreak);
		fill(0, 0, 0);
		textSize(20);
		text(buf, x + 110, y + 18);
	}

	KANJI* KANJI::kanji1() {
		static KANJI kanjiinstance1;
		kanjiinstance1.loadKanjiImages();
		return &kanjiinstance1;
	}
	void KANJI::initialize() {

		memset(fixedKana, 0, sizeof(fixedKana));
		memset(pendingRoma, 0, sizeof(pendingRoma));

		// 入力状態
		memset(displayStr, 0, sizeof(displayStr));
		memset(inputStrB, 0, sizeof(inputStrB));
		inputLenB = 0;

		// 判定状態
		KanswerChecked = false;
		KanswerCorrect = false;

		rewardGiven = false;

		kanjiCount = 0;
	}

	void KANJI::Leftinitialize() {

		memset(fixedKana, 0, sizeof(fixedKana));
		memset(pendingRoma, 0, sizeof(pendingRoma));

		// 入力状態
		memset(displayStr, 0, sizeof(displayStr));
		memset(inputStrB, 0, sizeof(inputStrB));
		inputLenB = 0;

		// 判定状態
		KanswerChecked = false;
		KanswerCorrect = false;

		rewardGiven = false;

		kanjiCount = 0;
	}

	void KANJI::updateStatistics() {
		if (Qpoint > 0) {
			accuracyRate = (float)Apoint * 100.0f / (float)Qpoint;
		}
		else {
			accuracyRate = 0.0f;
		}
	}

	void KANJI::proc() {
		static bool pointLoaded = false;
		if (!pointLoaded) {
			loadPoint();
			pointLoaded = true;
		}
		if (kanjiCount == 0) {
			loadKanjiImages();
		}
		if (select2 == 0) {
			KANJI::loadQA();
			updateStatistics();
			game();
			if (isTrigger(KEY_RIGHT)) {
				kanji1();
				select2 = 1;
			}
		}
		else if (select2 == 1) {
			kanji1();
			Kanser1();
			key();
			updateDisplay();
			textSize(80);
			//入力表示
			fill(55, 125, 34);
			text(displayStr, 200, 300);
			drawMeter(1400, 80);
			char pbuf[32];
			fill(0, 0, 0);
			sprintf_s(pbuf, "PT:  %d", totalPoint);
			textSize(30);
			text(pbuf, 1280, 110);
			if (isTrigger(KEY_LEFT)) {
				Leftinitialize();
				select2 = 0;
				cont = 1;
			}
			if (!KanswerChecked) {
				// まだ判定していない
				if (isTrigger(KEY_SPACE)) {
					if (displayStr[0] != '\0') {
						textSize(30);
						fill(0, 255, 0);
						Qpoint++;
						KanswerCorrect = strcmp(displayStr, kanji[currentKanji].yomi) == 0;
						if (KanswerCorrect) {
							Apoint++;  // ← 正解
						}
						saveQA();
						KanswerChecked = true;
					}
				}
			}
			else {
				// 判定済み → 結果表示
				textSize(50);

				if (KanswerCorrect && !rewardGiven) {
					correctStreak++;
					rewardGiven = true;

					if (correctStreak >= 10) {
						totalPoint++;
						correctStreak = 0;
						savePoint();
					}
					cont = 0;
				}
				else if (!KanswerCorrect)  {
					correctStreak = 0;
					fill(50, 130, 246);
					text("不正解！", 700, 400);
					text("Enterで次の問題へ", 700, 500);
					text("Shiftでメニューに戻る", 700, 600);
				}

				if (KanswerCorrect) {
					fill(235, 51, 36);
					text("正解！", 700, 400);
					text("Enterで次の問題へ", 700, 500);
					text("Shiftでメニューに戻る", 700, 600);
				}

				// 次の問題
				if (isTrigger(KEY_ENTER)) {
					kanji1();
					Kanser1Generated = false;
					initialize();
					memset(displayStr, 0, sizeof(displayStr));
					inputLenB = 0;
					KanswerChecked = false;
					KanswerCorrect = false;
				}

				if (isTrigger(KEY_SHIFT)) { //不正解
					initialize();
					select2 = 0;
					correctStreak = 0;
				}
			}
		}
			textSize(50);
			fill(255, 255, 255);
			fill(255, 255, 255);
		}

		void KANJI::key() {
			// 1文字削除
			if (isTrigger(KEY_DOWN)) {
				int len = strlen(pendingRoma);
				if (len > 0) {
					pendingRoma[len - 1] = '\0';
				}
				else {
					int klen = strlen(fixedKana);
					if (klen > 0) fixedKana[klen - 1] = '\0';
				}
				return;
			}

			if (inputLenB >= 120) return;

			const INPUT_CODE keys[26] = {
				KEY_A,KEY_B,KEY_C,KEY_D,KEY_E,KEY_F,
				KEY_G,KEY_H,KEY_I,KEY_J,KEY_K,KEY_L,
				KEY_M,KEY_N,KEY_O,KEY_P,KEY_Q,KEY_R,
				KEY_S,KEY_T,KEY_U,KEY_V,KEY_W,KEY_X,
				KEY_Y,KEY_Z
			};

			for (int i = 0; i < 26; i++) {
				if (isTrigger(keys[i])) {

					char c = 'a' + i;

					// 判定用ローマ字保存
					inputRoma[inputLenB++] = c;
					inputRoma[inputLenB] = '\0';

					// 未確定ローマ字追加
					int len = strlen(pendingRoma);
					pendingRoma[len] = c;
					pendingRoma[len + 1] = '\0';

					// 変換できたら確定
					char kana[8];
					if (romajiToKana(pendingRoma, kana)) {
						strcat_s(fixedKana, kana);
						pendingRoma[0] = '\0';
					}
					break;
				}
			}
		}
	}