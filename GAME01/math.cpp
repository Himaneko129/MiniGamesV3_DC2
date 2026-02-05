#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME01.h"
#include "math.h"
#include"windows.h"
#include"input2.h"
namespace GAME01 {
	int MATH::cont = 0;
	void MATH::game()    /*ランダム数読み込み→計算*/
	{
		clear(0, 0, 64);
		textSize(75);
		fill(0, 255, 0);
		text("計算問題モード＞＞＞＞＞＞", 20, 100);
		textSize(55);
		fill(255, 255, 255);
		text("モードを選んでください。※「」内のキーを入力すると進みます。",20, 200);
		text("[←]キーでメニューに戻る", 90, 1000);
		fill(0, 0, 255);
		rect(10, 400, 370, 200);
		fill(0, 255, 0);
		rect(510, 400, 370, 200);
		fill(255, 0, 0);
		rect(1010, 400, 370, 200);
		fill(125, 125, 125);
		rect(1510, 400, 370, 200);
		textSize(70);
		fill(0, 0, 0);
		text("足し算「P」", 20, 530);
		text("引き算「O」", 520, 530);
		text("掛け算「I」", 1020, 530);
		text("割り算「U」", 1520, 530);
		fill(150, 170, 120);
		rect(510, 670, 870, 200);
		textSize(40);
		fill(255, 255, 255);
		text("高難易度モード/「Y」足し算  「T」引き算", 510, 810);
	}
	void MATH::anser1() {
		/*四則演算[最大3桁+3桁](〇+〇)*/
		if (!anser1Generated) {
			Ma = 0, Mb = 0;
			Ma = random() % 101;
			Mb = random() % 101;
			Manser = Ma + Mb;
			anser1Generated = true;
		}
		fill(255, 255, 255);
		clear(0, 0, 64);
		textSize(80);
		text("答えを入力してください。SPACEで確定。", 20, 200);
		textSize(55);
		text("【　[←]キーで中断", 90, 1000);
		text("[↓]キーで1文字削除　】", 700, 1000);
		textSize(80);
		fill(255, 255, 0);
		text(Ma, 620, 100);
		text("+", 730, 100);
		text(Mb, 840, 100);
		text("=", 950, 100);
		text("？", 1060, 100);
	}
	void MATH::anser2() {
		/*四則演算[最大3桁-3桁](〇-〇)*/
		if (!anser2Generated) {
			Mc = random() % 101;
			Md = random() % 101;
			if (Mc > Md) {
				Manser2 = Mc - Md;
			}
			else if (Mc < Md) {
				Manser2 = Md - Mc;
			}
			anser2Generated = true;
		}
		clear(0, 0, 64);
		textSize(80);
		text("答えを入力してください。SPACEで確定。", 20, 200);
		textSize(55);
		text("【　[←]キーで中断", 90, 1000);
		text("[↓]キーで1文字削除　】", 700, 1000);
		textSize(80);
		if (Mc > Md) {
			fill(255, 255, 0);
			text(Mc, 620, 100);
			text("-", 730, 100);
			text(Md, 840, 100);
			text("=", 950, 100);
			text("？", 1060, 100);
		}
		else if (Mc < Md) {
			fill(255, 255, 0);
			text(Md, 620, 100);
			text("-", 730, 100);
			text(Mc, 840, 100);
			text("=", 950, 100);
			text("？", 1060, 100);
		}
	}
	void MATH::anser3() {
		/*四則演算[最大2桁×2桁](〇×〇)*/
		if (!anser3Generated) {
			Me = random() % 100;
			Mf = random() % 100;
			Manser3 = Me * Mf;
			anser3Generated = true;
		}
		clear(0, 0, 64);
		textSize(80);
		text("答えを入力してください。SPACEで確定。", 20, 200);
		textSize(55);
		text("【　[←]キーで中断", 90, 1000);
		text("[↓]キーで1文字削除　】", 700, 1000);
		textSize(80);
		fill(255, 255, 0);
		text(Me, 620, 100);
		text("×", 730, 100);
		text(Mf, 840, 100);
		text("=", 950, 100);
		text("？", 1060, 100);
	}
	void MATH::anser4() {
		/*四則演算[最大3桁÷2桁](〇÷〇)Mgが0になる対策　答えが0になりすぎないように*/
		if (!anser4Generated) {
			Mg = random() % 150 + 1;
			Mh = random() % 20 + 1;
			Manser4 = Mg / Mh;
			anser4Generated = true;
		}
		clear(0, 0, 64);
		textSize(60);
		text("答えを入力してください(商のみで可)。SPACEで確定。", 20, 200);
		textSize(55);
		text("【　[←]キーで中断", 90, 1000);
		text("[↓]キーで1文字削除　】", 700, 1000);
		textSize(80);
		fill(255, 255, 0);
		text(Mg, 620, 100);
		text("÷", 730, 100);
		text(Mh, 840, 100);
		text("=", 950, 100);
		text("？", 1060, 100);
	}
	void MATH::anser5() {
		/*四則演算[最大4桁+4桁](〇+〇)*/
		if (!anser5Generated) {
			Mi = random() % 1101;
			Mj = random() % 1101;
			Manser5 = Mi + Mj;
			anser5Generated = true;
		}
		clear(0, 0, 64);
		textSize(80);
		text("答えを入力してください。SPACEで確定。", 20, 200);
		textSize(55);
		text("【　[←]キーで中断", 90, 1000);
		text("[↓]キーで1文字削除　】", 700, 1000);
		textSize(60);
		fill(255, 255, 0);
		text(Mi, 620, 100);
		text("＋", 730, 100);
		text(Mj, 810, 100);
		text("=", 950, 100);
		text("？", 1060, 100);
	}
	void MATH::anser6() {
		/*四則演算[最大4桁-4桁](〇-〇)*/
		if (!anser6Generated) {
			Mk = random() % 2001;
			Ml = random() % 2001;
			if (Mk > Ml) {
				Manser6 = Mk - Ml;
			}
			else if (Mk < Ml) {
				Manser6 = Ml - Mk;
			}
			anser6Generated = true;
		}
		clear(0, 0, 64);
		textSize(80);
		text("答えを入力してください。SPACEで確定。", 20, 200);
		textSize(55);
		text("【　[←]キーで中断", 90, 1000);
		text("[↓]キーで1文字削除　】", 700, 1000);
		if (Mk > Ml) {
			fill(255, 255, 0);
			text(Mk, 570, 100);
			text("-", 730, 100);
			text(Ml, 780, 100);
			text("=", 950, 100);
			text("？", 1060, 100);
		}
		else if (Mk < Ml) {
			fill(255, 255, 0);
			text(Ml, 570, 100);
			text("-", 730, 100);
			text(Mk, 780, 100);
			text("=", 950, 100);
			text("？", 1060, 100);
		}
	}

	void MATH::data() {

	}

	MATH* MATH::math1()
	{
		static MATH mathInstance1;
		return &mathInstance1;
	}
	MATH* MATH::math2()
	{
		static MATH mathInstance2;
		return &mathInstance2;
	}
	MATH* MATH::math3()
	{
		static MATH mathInstance3;
		return &mathInstance3;
	}
	MATH* MATH::math4()
	{
		static MATH mathInstance4;
		return &mathInstance4;
	}
	MATH* MATH::math5()
	{
		static MATH mathInstance5;
		return &mathInstance5;
	}
	MATH* MATH::math6()
	{
		static MATH mathInstance6;
		return &mathInstance6;
	}
	void MATH::proc() {
		GAME01::getInput2();
		if (select1 == 0) {
			game();
			if (isTrigger(KEY_P)) {
				math1();
				select1 = 1;
			}
			if (isTrigger(KEY_O)) {
				math2();
				select1 = 2;
			}
			if (isTrigger(KEY_I)) {
				math3();
				select1 = 3;
			}
			if (isTrigger(KEY_U)) {
				math4();
				select1 = 4;
			}
			if (isTrigger(KEY_Y)) {
				math5();
				select1 = 5;
			}
			if (isTrigger(KEY_T)) {
				math6();
				select1 = 6;
			}
			if (isTrigger(KEY_ENTER) && !answerChecked) {
				select1 = 0;
			}
		}
		else if (select1 == 1) {
			MATH* m1 = MATH::math1();
			m1->anser1();
			key();
			if (isTrigger(KEY_LEFT)) {
				inputStrA[0] = '\0';
				inputLenA = 0;
				answerChecked = false;
				answerCorrect = false;
				cont = 1;
				select1 = 0;
			}
			if (!answerChecked) {
				if (isTrigger(KEY_SPACE)) {
					if (inputStrA[0] != '\0') {
						valueA = atoi(inputStrA);
						textSize(50);
						answerCorrect = (m1->Manser == valueA);
						answerChecked = true;
					}
				}
			}
			else {
				// 判定済み → 結果表示
				if (answerCorrect) {
					text("正解！", 700, 400);
					text("Enterで次の問題へ", 700, 500);
					text("Shiftでメニューに戻る", 700, 600);
					cont = 0;
				}
				else {
					text("不正解！", 700, 400);
					text("Shiftでメニューに戻る", 700, 500);
					text("Enterで次の問題へ", 700, 600);
					/*if (select1 = 1) {
						text("答えは", 1000, 400);
						text(Manser, 1300, 400);
						text("です", 1500, 400);
					}*/
				}

				if (isTrigger(KEY_ENTER)) { //正解
					MATH::math1()->anser1Generated = false;
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					answerCorrect = false;
				}
				if (isTrigger(KEY_SHIFT)) { //不正解
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					answerCorrect = false;
					select1 = 0;
				}
			}
		}
		else if (select1 == 2) {
			MATH* m2 = MATH::math2();
			m2->anser2();
			key();
			if (isTrigger(KEY_LEFT)) {
				inputStrA[0] = '\0';
				inputLenA = 0;
				answerChecked = false;
				answerCorrect = false;
				cont = 1;
				select1 = 0;
			}
			if (!answerChecked) {
				if (isTrigger(KEY_SPACE)) {
					if (inputStrA[0] != '\0') {
						valueA = atoi(inputStrA);
						textSize(50);
						answerCorrect = (m2->Manser2 == valueA);
						answerChecked = true;
					}
				}
			}
			else {
				// 判定済み → 結果表示
				if (answerCorrect) {
					text("正解！", 700, 400);
					text("Enterで次の問題へ", 700, 500);
					text("Shiftでメニューに戻る", 700, 600);
					cont = 0;
				}
				else {
					text("不正解！", 700, 400);
					text("Shiftでメニューに戻る", 700, 500);
					text("Enterで次の問題へ", 700, 600);
				}

				if (isTrigger(KEY_ENTER)) { //正解
					MATH::math2()->anser2Generated = false;
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					anser2Generated = false;  // 次回 anser2 で新問題生成
				}
				if (isTrigger(KEY_SHIFT)) { //不正解
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					answerCorrect = false;
					select1 = 0;
				}
			}
		}
		else if (select1 == 3) {
			MATH* m3 = MATH::math3();
			m3->anser3();
			key();
			if (isTrigger(KEY_LEFT)) {
				inputStrA[0] = '\0';
				inputLenA = 0;
				answerChecked = false;
				answerCorrect = false;
				cont = 1;
				select1 = 0;
			}
			if (!answerChecked) {
				if (isTrigger(KEY_SPACE)) {
					if (inputStrA[0] != '\0') {
						valueA = atoi(inputStrA);
						textSize(50);
						answerCorrect = (m3->Manser3 == valueA);
						answerChecked = true;
					}
				}
			}
			else {
				// 判定済み → 結果表示
				if (answerCorrect) {
					text("正解！", 700, 400);
					text("Enterで次の問題へ", 700, 500);
					text("Shiftでメニューに戻る", 700, 600);
					cont = 0;
				}
				else {
					text("不正解！", 700, 400);
					text("Shiftでメニューに戻る", 700, 500);
					text("Enterで次の問題へ", 700, 600);
				}

				if (isTrigger(KEY_ENTER)) { //正解
					MATH::math3()->anser3Generated = false;
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					anser3Generated = false;  // 次回 anser3 で新問題生成
				}
				if (isTrigger(KEY_SHIFT)) { //不正解
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					answerCorrect = false;
					select1 = 0;
				}
			}
			}
		else if (select1 == 4) {
			MATH* m4 = MATH::math4();
			m4->anser4();
			key();
			if (isTrigger(KEY_LEFT)) {
				inputStrA[0] = '\0';
				inputLenA = 0;
				answerChecked = false;
				answerCorrect = false;
				cont = 1;
				select1 = 0;
			}
			if (!answerChecked) {
				if (isTrigger(KEY_SPACE)) {
					if (inputStrA[0] != '\0') {
						valueA = atoi(inputStrA);
						textSize(50);
						answerCorrect = (m4->Manser4 == valueA);
						answerChecked = true;
					}
				}
			}
			else {
				// 判定済み → 結果表示
				if (answerCorrect) {
					text("正解！", 700, 400);
					text("Enterで次の問題へ", 700, 500);
					text("Shiftでメニューに戻る", 700, 600);
					cont = 0;
				}
				else {
					text("不正解！", 700, 400);
					text("Shiftでメニューに戻る", 700, 500);
					text("Enterで次の問題へ", 700, 600);
				}
				if (isTrigger(KEY_ENTER)) { //正解
					MATH::math4()->anser4Generated = false;
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					anser4Generated = false;  // 次回 anser4 で新問題生成
				}
				if (isTrigger(KEY_SHIFT)) { //不正解
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					answerCorrect = false;
					select1 = 0;
				}
			}
		}
		else if (select1 == 5) {
			MATH* m5 = MATH::math5();
			m5->anser5();
			key();
			if (isTrigger(KEY_LEFT)) {
				inputStrA[0] = '\0';
				inputLenA = 0;
				answerChecked = false;
				answerCorrect = false;
				cont = 1;
				select1 = 0;
			}
			if (!answerChecked) {
				if (isTrigger(KEY_SPACE)) {
					if (inputStrA[0] != '\0') {
						valueA = atoi(inputStrA);
						textSize(50);
						answerCorrect = (m5->Manser5 == valueA);
						answerChecked = true;
					}
				}
			}
			else {
				// 判定済み → 結果表示
				if (answerCorrect) {
					text("正解！", 700, 400);
					text("Enterで次の問題へ", 700, 500);
					text("Shiftでメニューに戻る", 700, 600);
					cont = 0;
				}
				else {
					text("不正解！", 700, 400);
					text("Shiftでメニューに戻る", 700, 500);
					text("Enterで次の問題へ", 700, 600);
				}
				if (isTrigger(KEY_ENTER)) { //正解
					MATH::math5()->anser5Generated = false;
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					anser5Generated = false;  // 次回 anser5 で新問題生成
				}
				if (isTrigger(KEY_SHIFT)) { //不正解
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					answerCorrect = false;
					select1 = 0;
				}
			}
		}
		else if (select1 == 6) {
			MATH* m6 = MATH::math6();
			m6->anser6();
			key();
			if (isTrigger(KEY_LEFT)) {
				inputStrA[0] = '\0';
				inputLenA = 0;
				answerChecked = false;
				answerCorrect = false;
				cont = 1;
				select1 = 0;
			}
			if (!answerChecked) {
				if (isTrigger(KEY_SPACE)) {
					if (inputStrA[0] != '\0') {
						valueA = atoi(inputStrA);
						textSize(50);
						answerCorrect = (m6->Manser6 == valueA);
						answerChecked = true;
					}
				}
			}
			else {
				// 判定済み → 結果表示
				if (answerCorrect) {
					text("正解！", 700, 400);
					text("Enterで次の問題へ", 700, 500);
					text("Shiftでメニューに戻る", 700, 600);
					cont = 0;
				}
				else {
					text("不正解！", 700, 400);
					text("Shiftでメニューに戻る", 700, 500);
					text("Enterで次の問題へ", 700, 600);
				}

				if (isTrigger(KEY_ENTER)) { //正解
					MATH::math6()->anser6Generated = false;
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					anser6Generated = false;  // 次回 anser2 で新問題生成
				}
				if (isTrigger(KEY_SHIFT)) { //不正解
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					answerCorrect = false;
					select1 = 0;
				}
			}
			}
		textSize(80);
		fill(255, 255, 255);
		text(inputStrA, 200, 300);  // 文字列表示
		fill(255, 255, 255);
	}
	void MATH::key() {
		//1文字削除（KEY_DOWN）
		if (isTrigger(KEY_DOWN)) {
			if (inputLenA > 0) {
				inputLenA--;
				inputStrA[inputLenA] = '\0';
			}
			return;
		}
		if (inputLenA < 31) {
			if (isTrigger2(KEY_0)) { inputStrA[inputLenA++] = '0'; }
			else if (isTrigger2(KEY_1)) { inputStrA[inputLenA++] = '1'; }
			else if (isTrigger2(KEY_2)) { inputStrA[inputLenA++] = '2'; }
			else if (isTrigger2(KEY_3)) { inputStrA[inputLenA++] = '3'; }
			else if (isTrigger2(KEY_4)) { inputStrA[inputLenA++] = '4'; }
			else if (isTrigger2(KEY_5)) { inputStrA[inputLenA++] = '5'; }
			else if (isTrigger2(KEY_6)) { inputStrA[inputLenA++] = '6'; }
			else if (isTrigger2(KEY_7)) { inputStrA[inputLenA++] = '7'; }
			else if (isTrigger2(KEY_8)) { inputStrA[inputLenA++] = '8'; }
			else if (isTrigger2(KEY_9)) { inputStrA[inputLenA++] = '9'; }
			inputStrA[inputLenA] = '\0'; // 文字列終端
		}
	}
};

