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
	/*int GAME01::KANJI::correctStreak = 0;
	int GAME01::KANJI::totalPoint = 0;*/
	void KANJI::game() {
		clear(0, 0, 64);
		textSize(55);
		fill(255, 255, 255);
		text("難易度を選んでください。※「」内のキーを入力すると確定。", 20, 200);
		text("", 20, 280);
		text("[←]キーでメニューに戻る", 90, 1000);
		fill(100, 120, 105);
		rect(110, 400, 470, 200);
		textSize(45);
		fill(0, 0, 0);
		text("★☆☆☆☆「→」", 120, 530);
	}
	void KANJI::Kanser1() {
		if (!Kanser1Generated && kanjiCount >= 0) {
			currentKanji = random(0, kanjiCount - 1);
			Kanser1Generated = true;
		}
		fill(255, 255, 255);
		clear(0, 0, 64);
		textSize(80);
		text("上の漢字の読み方を答えてください。SPACEで確定。", 20, 700);
		textSize(55);
		text("[←]キーでメニューに戻る", 90, 1000);
		text("[↓]キーで1文字削除", 800, 1000);
		fill(255, 255, 0);
		if (kanjiCount > 0) {
			image(kanji[currentKanji].img, 120, 100);
	    }
		fill(255, 255, 0);
	}

    bool KANJI::romajiToKana(const char* src, char* dst) {

	struct RK { const char* r; const char* k; };
	static const RK table[] = {
		{"kya","きゃ"},{"kyu","きゅ"},{"kyo","きょ"},
		{"sha","しゃ"},{"shu","しゅ"},{"sho","しょ"},
		{"cha","ちゃ"},{"chu","ちゅ"},{"cho","ちょ"},
		{"nya","にゃ"},{"nyu","にゅ"},{"nyo","にょ"},
		{"hya","ひゃ"},{"hyu","ひゅ"},{"hyo","ひょ"},
		{"mya","みゃ"},{"myu","みゅ"},{"myo","みょ"},
		{"rya","りゃ"},{"ryu","りゅ"},{"ryo","りょ"},

		{"shi","し"},{"chi","ち"},{"tsu","つ"},

		{"ka","か"},{"ki","き"},{"ku","く"},{"ke","け"},{"ko","こ"},
		{"sa","さ"},{"si","し"},{"su","す"},{"se","せ"},{"so","そ"},
		{"ta","た"},{"ti","ち"},{"tu","つ"},{"te","て"},{"to","と"},
		{"na","な"},{"ni","に"},{"nu","ぬ"},{"ne","ね"},{"no","の"},
		{"ha","は"},{"hi","ひ"},{"fu","ふ"},{"he","へ"},{"ho","ほ"},
		{"ma","ま"},{"mi","み"},{"mu","む"},{"me","め"},{"mo","も"},
		{"ya","や"},{"yu","ゆ"},{"yo","よ"},
		{"ra","ら"},{"ri","り"},{"ru","る"},{"re","れ"},{"ro","ろ"},
		{"wa","わ"},{"wo","を"},{"nn","ん"},
		{"ga","が"},{"gi","ぎ"},{"gu","ぐ"},{"ge","げ"},{"go","ご"},
		{"za","ざ"},{"zi","じ"},{"zu","ず"},{"ze","ぜ"},{"zo","ぞ"},
		{"da","だ"},{"de","で"},{"do","ど"},
		{"ba","ば"},{"bi","び"},{"bu","ぶ"},{"be","べ"},{"bo","ぼ"},
		{"pa","ぱ"},{"pi","ぴ"},{"pu","ぷ"},{"pe","ぺ"},{"po","ぽ"},

		{"a","あ"},{"i","い"},{"u","う"},{"e","え"},{"o","お"},
		{"ji","じ"}
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

		kanjiCount = 8;
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

	void KANJI::drawMeter(float x, float y) {
		float maxWidth = 300;
		float height = 25;

		// 枠
		fill(255, 255, 255);
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
			fill(255, 255, 0);
			text(displayStr, 200, 300);
			drawMeter(1400, 80);
			char pbuf[32];
			fill(255, 255, 0);
			sprintf_s(pbuf, "PT:  %d", totalPoint);
			textSize(30);
			text(pbuf, 1280, 110);
			if (isTrigger(KEY_LEFT)) {
				Leftinitialize();
				cont = 1;
			}
			if (!KanswerChecked) {
				// まだ判定していない
				if (isTrigger(KEY_SPACE)) {
					if (displayStr[0] != '\0') {
						textSize(30);
						fill(0, 255, 0);
						KanswerCorrect = strcmp(displayStr, kanji[currentKanji].yomi) == 0;
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
					fill(255, 255, 0);
					text("不正解！", 700, 400);
					text("Enterで次の問題へ", 700, 500);
					text("Shiftでメニューに戻る", 700, 600);
				}

				if (KanswerCorrect) {
					fill(255, 255, 0);
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

					// 未確定ローマ字に追加
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

	//メモ
	//漢字追加・メニュー画面の制限時間表記削除or制限時間機能追加
	//初期化　メニュー→漢字→前の情報を残すか消すか(数値)「shiftは数値残る、Enterは消える」