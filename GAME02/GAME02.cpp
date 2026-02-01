#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME02.h"
#include<iostream>
#include <time.h>
extern bool EscapeKeyValid;
namespace GAME02{
	//こりゃあもう完全に遊び大全で良いでしょう
	const int cardall = 20;
	int cardimg[cardall];
	int a;
	//ゲーム中ステータス
	int gameselect = 0;
	int gamest = 0;
	int maingame = 0;
	int BGM = 0;
	//ディーラー
	int GDE = 0;
	int randDE1 = 0;
	int randDE2 = 0;
	int randDE3 = 0;
	int randDE4 = 0;
	int randDE5 = 0;
	//自分
	int GME = 0;
	int randME1 = 0;
	int randME2 = 0;
	int randME3 = 0;
	int randME4 = 0;
	int randME5 = 0;
	//カウント
	int Hitcount = 0;
	int Scount = 0;
	int re = 0;
	//音楽
	int Soundgame1 = 0;

	//ヨット
	
	int gameend = 0;
	int role = 3;
	int round = 12;
	int pull = 0;
	int syori = 0;
	//サイコロ画像
	const int diceall = 6;
	int diceimg[diceall];
	//ダイスの目
	int diceME[5] = { 0,0,0,0,0 };
	//出たダイスの目の数
	int diceSU[6] = { 0,0,0,0,0,0 };
	//ロックされたダイスの保存場所
	int diceHOZ[5] = { 0,0,0,0,0 };
	//保存をするかどうかの判断
	unsigned int diceHOZYN[5] = { 0,0,0,0,0 };
	//仮保存場所
	int diceKARI[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	//自分の点数
	int tensuME[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	int sumME123456 = 0;
	int sumMEall = 0;
	//相手の点数
	int tensuME2[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	int sumME2123456 = 0;
	int sumME2all = 0;
	//数が入っているかのフラグ
	int fME[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	int fME2[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	//役成立判定の変数
	int isfour = 0;
	int isfull = 0;
	int isss = 0;
	int isbs = 0;
	int isyot = 0;
	int is3 = 0;
	int is2 = 0;
	int is1 = 0;
	int w4 = 0;
	int w3 = 0;
	int w2 = 0;
	int warning = 0;
	//ターン数
	int tarn = 0;
	//役が成立したか
	int yakuOK = 0;

	int GAME::create() {
		//ここにはゲーム開始時に1回だけ行うものを記述する
		BGM = 0;
		srand(time(0));
		//カードの画像ロード
		cardimg[0] = loadImage("..\\MAIN\\assets\\game02\\0.png");
		cardimg[1] = loadImage("..\\MAIN\\assets\\game02\\1.png");
		cardimg[2] = loadImage("..\\MAIN\\assets\\game02\\2.png");
		cardimg[3] = loadImage("..\\MAIN\\assets\\game02\\3.png");
		cardimg[4] = loadImage("..\\MAIN\\assets\\game02\\4.png");
		cardimg[5] = loadImage("..\\MAIN\\assets\\game02\\5.png");
		cardimg[6] = loadImage("..\\MAIN\\assets\\game02\\6.png");
		cardimg[7] = loadImage("..\\MAIN\\assets\\game02\\7.png");
		cardimg[8] = loadImage("..\\MAIN\\assets\\game02\\8.png");
		cardimg[9] = loadImage("..\\MAIN\\assets\\game02\\9.png");
		cardimg[10] = loadImage("..\\MAIN\\assets\\game02\\10.png");
		cardimg[11] = loadImage("..\\MAIN\\assets\\game02\\11.png");
		cardimg[12] = loadImage("..\\MAIN\\assets\\game02\\12.png");
		cardimg[13] = loadImage("..\\MAIN\\assets\\game02\\13.png");
		diceimg[0] = loadImage("..\\MAIN\\assets\\game02\\dice1.png");
		diceimg[1] = loadImage("..\\MAIN\\assets\\game02\\dice2.png");
		diceimg[2] = loadImage("..\\MAIN\\assets\\game02\\dice3.png");
		diceimg[3] = loadImage("..\\MAIN\\assets\\game02\\dice4.png");
		diceimg[4] = loadImage("..\\MAIN\\assets\\game02\\dice5.png");
		diceimg[5] = loadImage("..\\MAIN\\assets\\game02\\dice6.png");
		//音楽をロード
		Soundgame1 = loadSound("..\\MAIN\\assets\\game02\\BGM.wav");
		//メインループ側でのESCキーでの終了判定を無効化する
		EscapeKeyValid = false;
		textSize(200);
		return 0;
	}
	void GAME::destroy(){
		//ここにはゲーム終了時に1回だけ行うものを記述する
		//メインループ側でのESCキーでの終了判定を有効化する
		EscapeKeyValid = true;
		stopSound(Soundgame1);
		gameselect = 0;
		gamest = 0;
		reset();
	}
	void GAME::reset() {
		GDE = 0;
		GME = 0;
		Scount = 0;
		Hitcount = 0;
		randDE1 = 0;
		randDE2 = 0;
		randDE3 = 0;
		randDE4 = 0;
		randDE5 = 0;
		randME1 = 0;
		randME2 = 0;
		randME3 = 0;
		randME4 = 0;
		randME5 = 0;
		maingame = 0;
		re = 0;
		for (int i = 0; i < 5; i++){
			diceME[i] = 0;
			diceHOZ[i] = 0;
			diceHOZYN[i] = 0;
		}
		for (int i = 0; i < 6; i++) {
			diceSU[i] = 0;
		}
		for (int i = 0; i < 12; i++) {
			diceKARI[i] = 0;
			tensuME[i] = 0;
			tensuME2[i] = 0;
			fME[i] = 0;
			fME2[i] = 0;
		}
		sumME123456 = 0;
		sumMEall = 0;
		sumME2123456 = 0;
		sumME2all = 0;
		role = 3;
		pull = 0;
		isfour = 0;
		isfull = 0;
		isss = 0;
		isbs = 0;
		isyot = 0;
		is3 = 0;
		is2 = 0;
		is1 = 0;
		w4 = 0;
		w3 = 0;
		w2 = 0;
		tarn = 0;
	}
	void GAME::diceroll() {
			yotreset();
		if (isTrigger(KEY_ENTER) && pull == 0 && role != 0 && tarn !=24) {
			for (int i = 0; i < 6; i++) {
				diceSU[i] = 0;
			}
			for (int i = 0; i < 5; i++) {
				diceME[i] = rand() % 6 + 1;
				if ((diceHOZYN[i] % 2) == 1) {
					diceME[i] = diceHOZ[i];
				}
				diceHOZ[i] = diceME[i];
			}
			for (int i = 0; i < 12; i++) {
				diceKARI[i] = 0;
			}
			for (int i = 0; i < 5; i++) {
				for (int j = 1; j <= 6; j++) {
					if (diceME[i] == j) {
						diceSU[j - 1] += 1;
					}
				}
			}
			role--;
			syori = 1;
		}
	}
	void GAME::yaku() {
		textSize(70);
		if (syori != 0) {
			//普通
			for (int h = 0; h <= 5; h++) {
				for (int i = 0; i <= 5; i++) {
					if (diceME[i] == h + 1) {
						diceKARI[h] += h + 1;
					}
				}
			}
			//特殊役
			for (int i = 0; i < 6; i++) {
				if (diceSU[i] == 5) isyot = 1;
				if (diceSU[i] == 4) {
					isfour = 1;
					w4 = i + 1;
				}
				if (diceSU[i] == 3) { 
					is3 = 1;
					w3 = i + 1;
				}
				if (diceSU[i] == 2) { 
					is2 = 1;
					w2 = i + 1;
				}
			}
			//ストレートの判断
			for (int i = 0; i < 6; i++) {
				if (diceME[i] == 1) {
					for (int i = 0; i < 6; i++) {
						if (diceME[i] == 2) {
							for (int i = 0; i < 6; i++) {
								if (diceME[i] == 3) {
									for (int i = 0; i < 6; i++) {
										if (diceME[i] == 4) {
											isss = 1;
											for (int i = 0; i < 6; i++) {
												if (diceME[i] == 5) {
													isbs = 1;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			for (int i = 0; i < 6; i++) {
				if (diceME[i] == 2) {
					for (int i = 0; i < 6; i++) {
						if (diceME[i] == 3) {
							for (int i = 0; i < 6; i++) {
								if (diceME[i] == 4) {
									for (int i = 0; i < 6; i++) {
										if (diceME[i] == 5) {
											isss = 1;
											for (int i = 0; i < 6; i++) {
												if (diceME[i] == 6) {
													isbs = 1;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			for (int i = 0; i < 6; i++) {
				if (diceME[i] == 3) {
					for (int i = 0; i < 6; i++) {
						if (diceME[i] == 4) {
							for (int i = 0; i < 6; i++) {
								if (diceME[i] == 5) {
									for (int i = 0; i < 6; i++) {
										if (diceME[i] == 6) {
											isss = 1;
										}
									}
								}
							}
						}
					}
				}
			}
			//チョイス
			for (int i = 0; i < 5; i++) {
				diceKARI[6] += diceME[i];
			}
			//フォーダイス
			if (isfour == 1) {
				text("フォーダイス！",1000,200);
				diceKARI[7] = 25;
			}
			//フルハウス
			if (is3 == 1 && is2 == 1) {
				text("フルハウス！", 1000, 200);
				diceKARI[8] = (w3 * 3) + (w2 * 2);
			}
			//Sストレート
			if (isss == 1 &&isbs != 1) {
				text("Sストレート！", 1000, 200);
				diceKARI[9] = 15;
			}
			//Bストレート
			if (isbs == 1) {
				text("Bストレート！", 1000, 200);
				diceKARI[10] = 30;
			}
			//ヨット
			if (isyot == 1) {
				text("ヨット！！！", 1000, 200);
				diceKARI[11] = 50;
			}
		}
	}
	void GAME::kakutei() {
		//1Pの時
		if ((tarn % 2) == 0) {
			if (isTrigger(KEY_Q)) {
				if (fME[0] == 0) {
				tensuME[0] = diceKARI[0]; yakuOK = 1;
				sumME123456 += tensuME[0];
				sumMEall += tensuME[0];
				}
				else{
					warning = 1;
				}
				fME[0] = 1;
			}
			if (isTrigger(KEY_W)) {
				if (fME[1] == 0) {
					tensuME[1] = diceKARI[1]; yakuOK = 1;
					sumME123456 += tensuME[1];
					sumMEall += tensuME[1];
				}
				else {
					warning = 1;
				}
				fME[1] = 1;
			}
			if (isTrigger(KEY_E)) {
				if (fME[2] == 0) {
					tensuME[2] = diceKARI[2]; yakuOK = 1;
					sumME123456 += tensuME[2];
					sumMEall += tensuME[2];
				}
				else {
					warning = 1;
				}
				fME[2] = 1;
			}
			if (isTrigger(KEY_R)) {
				if (fME[3] == 0) {
					tensuME[3] = diceKARI[3]; yakuOK = 1;
					sumME123456 += tensuME[3];
					sumMEall += tensuME[3];
				}
				else {
					warning = 1;
				}
				fME[3] = 1;
			}
			if (isTrigger(KEY_T)) {
				if (fME[4] == 0) {
					tensuME[4] = diceKARI[4]; yakuOK = 1;
					sumME123456 += tensuME[4];
					sumMEall += tensuME[4];
				}
				else {
					warning = 1;
				}
				fME[4] = 1;
			}
			if (isTrigger(KEY_Y)) {
				if (fME[5] == 0) {
					tensuME[5] = diceKARI[5]; yakuOK = 1;
					sumME123456 += tensuME[5];
					sumMEall += tensuME[5];
				}
				else {
					warning = 1;
				}
				fME[5] = 1;
			}
			if (isTrigger(KEY_U)) {
				if (fME[6] == 0) {
					tensuME[6] = diceKARI[6]; yakuOK = 1;
					sumMEall += tensuME[6];
				}
				else {
					warning = 1;
				}
				fME[6] = 1;
			}
			if (isTrigger(KEY_I)) {
				if (fME[7] == 0) {
					tensuME[7] = diceKARI[7]; yakuOK = 1;
					sumMEall += tensuME[7];
				}
				else {
					warning = 1;
				}
				fME[7] = 1;
			}
			if (isTrigger(KEY_O)) {
				if (fME[8] == 0) {
					tensuME[8] = diceKARI[8]; yakuOK = 1;
					sumMEall += tensuME[8];
				}
				else {
					warning = 1;
				}
				fME[8] = 1;
			}
			if (isTrigger(KEY_P)) {
				if (fME[9] == 0) {
					tensuME[9] = diceKARI[9]; yakuOK = 1;
					sumMEall += tensuME[9];
				}
				else {
					warning = 1;
				}
				fME[9] = 1;
			}
			if (isTrigger(KEY_A)) {
				if (fME[10] == 0) {
					tensuME[10] = diceKARI[10]; yakuOK = 1;
					sumMEall += tensuME[10];
				}
				else {
					warning = 1;
				}
				fME[10] = 1;
			}
			if (isTrigger(KEY_S)) {
				if (fME[11] == 0) {
					tensuME[11] = diceKARI[11]; yakuOK = 1;
					sumMEall += tensuME[11];
				}
				else {
					warning = 1;
				}
				fME[11] = 1;
			}
		}
		//2Pの時
		if ((tarn % 2) == 1) {
			if (isTrigger(KEY_Q)) {
				if (fME2[0] == 0) {
					tensuME2[0] = diceKARI[0]; yakuOK = 1;
					sumME2123456 += tensuME2[0];
					sumME2all += tensuME2[0];
				}
				else {
					warning = 1;
				}
				fME2[0] = 1;
			}
			if (isTrigger(KEY_W)) {
				if (fME2[1] == 0) {
					tensuME2[1] = diceKARI[1]; yakuOK = 1;
					sumME2123456 += tensuME2[1];
					sumME2all += tensuME2[1];
				}
				else {
					warning = 1;
				}
				fME2[1] = 1;
			}
			if (isTrigger(KEY_E)) {
				if (fME2[2] == 0) {
					tensuME2[2] = diceKARI[2]; yakuOK = 1;
					sumME2123456 += tensuME2[2];
					sumME2all += tensuME2[2];
				}
				else {
					warning = 1;
				}
				fME2[2] = 1;
			}
			if (isTrigger(KEY_R)) {
				if (fME2[3] == 0) {
					tensuME2[3] = diceKARI[3]; yakuOK = 1;
					sumME2123456 += tensuME2[3];
					sumME2all += tensuME2[3];
				}
				else {
					warning = 1;
				}
				fME2[3] = 1;
			}
			if (isTrigger(KEY_T)) {
				if (fME2[4] == 0) {
					tensuME2[4] = diceKARI[4]; yakuOK = 1;
					sumME2123456 += tensuME2[4];
					sumME2all += tensuME2[4];
				}
				else {
					warning = 1;
				}
				fME2[4] = 1;
			}
			if (isTrigger(KEY_Y)) {
				if (fME2[5] == 0) {
					tensuME2[5] = diceKARI[5]; yakuOK = 1;
					sumME2123456 += tensuME2[5];
					sumME2all += tensuME2[5];
				}
				else {
					warning = 1;
				}
				fME2[5] = 1;
			}
			if (isTrigger(KEY_U)) {
				if (fME2[6] == 0) {
					tensuME2[6] = diceKARI[6]; yakuOK = 1;
					sumME2all += tensuME2[6];
				}
				else {
					warning = 1;
				}
				fME2[6] = 1;
			}
			if (isTrigger(KEY_I)) {
				if (fME2[7] == 0) {
					tensuME2[7] = diceKARI[7]; yakuOK = 1;
					sumME2all += tensuME2[7];
				}
				else {
					warning = 1;
				}
				fME2[7] = 1;
			}
			if (isTrigger(KEY_O)) {
				if (fME2[8] == 0) {
					tensuME2[8] = diceKARI[8]; yakuOK = 1;
					sumME2all += tensuME2[8];
				}
				else {
					warning = 1;
				}
				fME2[8] = 1;
			}
			if (isTrigger(KEY_P)) {
				if (fME2[9] == 0) {
					tensuME2[9] = diceKARI[9]; yakuOK = 1;
					sumME2all += tensuME2[9];
				}
				else {
					warning = 1;
				}
				fME2[9] = 1;
			}
			if (isTrigger(KEY_A)) {
				if (fME2[10] == 0) {
					tensuME2[10] = diceKARI[10]; yakuOK = 1;
					sumME2all += tensuME2[10];
				}
				else {
					warning = 1;
				}
				fME2[10] = 1;
			}
			if (isTrigger(KEY_S)) {
				if (fME2[11] == 0) {
					tensuME2[11] = diceKARI[11]; yakuOK = 1;
					sumME2all += tensuME2[11];
				}
				else {
					warning = 1;
				}
				fME2[11] = 1;
			}
		}
		if (yakuOK == 1){
			yotreset();
			role = 3;
			pull = 0;
			syori = 0;
			tarn++;
			yakuOK = 0;
			warning = 0;
			for (int i = 0; i < 5; i++){
				diceHOZYN[i] = 0;
			}
		}
	}
	void GAME::lock() {
		if (isTrigger(KEY_Z)) {
			diceHOZYN[0] += 1;
		}
		if (isTrigger(KEY_X)) {
			diceHOZYN[1] += 1;
		}
		if (isTrigger(KEY_C)) {
			diceHOZYN[2] += 1;
		}
		if (isTrigger(KEY_V)) {
			diceHOZYN[3] += 1;
		}
		if (isTrigger(KEY_B)) {
			diceHOZYN[4] += 1;
		}
	}
	void GAME::yotreset() {
		for (int i = 0; i < 12; i++) {
			diceKARI[i] = 0;
		}
		isfour = 0;
		isfull = 0;
		isss = 0;
		isbs = 0;
		isyot = 0;
		is3 = 0;
		is2 = 0;
		is1 = 0;
		w4 = 0;
		w3 = 0;
		w2 = 0;
	}
	void GAME::UI() {
		clear(0, 80, 0);
		if (tarn != 24) {
			image(diceimg[diceME[0] - 1], 650, 200);
			image(diceimg[diceME[1] - 1], 900, 200);
			image(diceimg[diceME[2] - 1], 1150, 200);
			image(diceimg[diceME[3] - 1], 1400, 200);
			image(diceimg[diceME[4] - 1], 1650, 200);
		}
		strokeWeight(10);
		stroke(255);
		line(0, 600, 1920, 600);
		line(294, 0, 294, 330);
		line(588, 0, 588, 600);
		line(0, 330, 588, 330);
		line(147, 600, 147, 1080);
		line(294, 600, 294, 1080);
		line(441, 600, 441, 1080);
		line(588, 600, 588, 1080);
		line(735, 600, 735, 1080);
		line(882, 600, 882, 1080);
		line(1029, 600, 1029, 1080);
		line(1176, 600, 1176, 1080);
		line(1323, 600, 1323, 1080);
		line(1470, 600, 1470, 1080);
		line(1617, 600, 1617, 1080);
		line(1764, 600, 1764, 1080);
		textSize(30);
		text("ボタン", 30, 1000);
		textSize(23);
		text("エース", 185, 900);//1
		text("デュース", 314, 900);//2
		text("トレイ", 471, 900);//3
		text("フォー", 618, 900);//4
		text("ファイブ", 755, 900);//5
		text("シックス", 902, 900);//6
		text("チョイス", 1049, 900);//tyois
		text("フォーダイス", 1178, 900);//four dise
		text("フルハウス", 1330, 900);//full house
		text("Ｓストレート", 1473, 900);//ss
		text("Ｂストレート", 1618, 900);//bs
		text("ヨット", 1780, 900);//yot
		textSize(50);
		text("1～6の小計", 0, 140);
		text("合計", 0, 250);
		text("1～6の小計", 300, 140);
		text("合計", 300, 250);
		textSize(70);
		text(sumME123456, 0, 200);
		text(sumMEall, 0, 320);
		text(sumME2123456, 300, 200);
		text(sumME2all, 300, 320);
		text("Q", 202, 1030);
		text("W", 350, 1030);
		text("E", 495, 1030);
		text("R", 645, 1030);
		text("T", 790, 1030);
		text("Y", 940, 1030);
		text("U", 1080, 1030);
		text("I", 1230, 1030);
		text("O", 1380, 1030);
		text("P", 1530, 1030);
		text("A", 1670, 1030);
		text("S", 1820, 1030);
		if (tarn != 24) {
			text("Z", 760, 510);
			text("X", 1010, 510);
			text("C", 1260, 510);
			text("V", 1510, 510);
			text("B", 1760, 510);
		}
		if (warning == 1) {
			text("既に数が入っています", 600, 600);
		}
		
		text(tensuME[0], 157, 700);//1
		text(tensuME[1], 304, 700);//2
		text(tensuME[2], 451, 700);//3
		text(tensuME[3], 598, 700);//4
		text(tensuME[4], 745, 700);//5
		text(tensuME[5], 892, 700);//6
		text(tensuME[6], 1039, 700);//tyois
		text(tensuME[7], 1186, 700);//four dise
		text(tensuME[8], 1333, 700);//full house
		text(tensuME[9], 1480, 700);//ss
		text(tensuME[10], 1627, 700);//bs
		text(tensuME[11], 1774, 700);//yot
		text(tensuME2[0], 157, 800);//1
		text(tensuME2[1], 304, 800);//2
		text(tensuME2[2], 451, 800);//3
		text(tensuME2[3], 598, 800);//4
		text(tensuME2[4], 745, 800);//5
		text(tensuME2[5], 892, 800);//6
		text(tensuME2[6], 1039, 800);//tyois
		text(tensuME2[7], 1186, 800);//four dise
		text(tensuME2[8], 1333, 800);//full house
		text(tensuME2[9], 1480, 800);//ss
		text(tensuME2[10], 1627, 800);//bs
		text(tensuME2[11], 1774, 800);//yot
		//合計部分
		
		//プレイヤー表示
		text("1P", 10, 700);
		text("1P", 0, 70);
		text("2P", 10, 800);
		text("2P", 300, 70);
		if ((tarn % 2) == 0) {
			fill(255, 0, 0);
			text("1P", 10, 700);
		}
		if ((tarn % 2) == 1) {
			fill(0, 0, 255);
			text("2P", 10, 800);
		}
		fill(255);
	}
	void GAME::help() {
		//マウスカーソルを合わせたら詳細が表示される
		if (mouseY >= 600) {
			textSize(45);
			if (mouseX > 147 && mouseX < 294){
				text("エース",0,400);
				text("1のサイコロの出目の数", 0, 460);
			
			}
			if (mouseX > 294 && mouseX < 441) {
				text("デュース", 0, 400);
				text("2のサイコロの出目の数", 0, 460);
				
			}
			if (mouseX > 441 && mouseX < 588) {
				text("トレイ", 0, 400);
				text("3のサイコロの出目の数", 0, 460);
				
			}
			if (mouseX > 588 && mouseX < 735) {
				text("フォー", 0, 400);
				text("4のサイコロの出目の数", 0, 460);
				
			}
			if (mouseX > 735 && mouseX < 882) {
				text("ファイブ", 0, 400);
				text("5のサイコロの出目の数", 0, 460);
				
			}
			if (mouseX > 882 && mouseX < 1029) {
				text("シックス", 0, 400);
				text("6のサイコロの出目の数", 0, 460);
				
			}
			if (mouseX > 1029 && mouseX < 1176) {
				text("チョイス", 0, 400);
				text("全てのサイコロを足した数", 0, 460);
			}
			if (mouseX > 1176 && mouseX < 1323) {
				text("フォーダイス", 0, 400);
				text("4つ同じサイコロが揃った役", 0, 460);
			}
			if (mouseX > 1323 && mouseX < 1470) {
				text("フルハウス", 0, 400);
				text("3つと2つのサイコロの役", 0, 460);
			}
			if (mouseX > 1470 && mouseX < 1617) {
				text("Sストレート", 0, 400);
				text("サイコロの数が4つ並んだ役", 0, 460);
				text("点数:15点固定", 0, 520);
			}
			if (mouseX > 1617 && mouseX < 1764) {
				text("Bストレート", 0, 400);
				text("サイコロの数が5つ並んだ役", 0, 460);
				text("点数:30点固定", 0, 520);
			}
			if (mouseX > 1764 && mouseX < 1920) {
				text("ヨット", 0, 400);
				text("5つ同じサイコロが揃った役", 0, 460);
				text("点数:50点固定", 0, 520);
			}
		}
	}	 
	void GAME::proc() {
		clear(0,80,0);
		stroke(255);
		strokeWeight(10);
		text("十字キー左右でセレクト", 0, 1060);
		line(600, 0, 1200, 1080);
		textSize(100);
		text("←ブラックジャック", 50, 900);
		text("ヨット→", 1400, 300);
		textSize(70);
		//ゲームの説明を入力する
		if (isTrigger(KEY_LEFT) && gameselect == 0) { gameselect = 1; }
		if (isTrigger(KEY_RIGHT) && gameselect == 0) { gameselect = 2; }
		//ゲーム１
		if (gameselect == 1) {
			//BGM　ON
			if (BGM == 0) {
				playLoopSound(Soundgame1);//音楽再生
				BGM = 1;
			}
			if (gamest == 0) {
				//タイトル
				clear(0, 80, 0);
				textSize(150);
				text("ブラックジャック", 350, 250);
				textSize(110);
				text("スペースキーを押してスタート", 200, 900);
				text("21に近い方が勝利！", 500, 600);
				if (isTrigger(KEY_SPACE)) {//ゲームに入る
					gamest = 1;
				}
			}
			if (gamest != 0) {
				if (maingame != 100) {
					//ディーラーと自分の1、2枚目準備
					randDE1 = rand() % 10 + 1;
					GDE += randDE1;
					randDE2 = rand() % 10 + 1;
					GDE += randDE2;
					randME1 = rand() % 10 + 1;
					GME += randME1;
					randME2 = rand() % 10 + 1;
					GME += randME2;
					maingame = 100;
				}
				clear(0, 80, 0);
				//ディーラーカード準備
				image(cardimg[randDE1], 100, 50);
				image(cardimg[randDE2], 200, 50);
				image(cardimg[randDE3], 300, 50);
				image(cardimg[randDE4], 400, 50);
				image(cardimg[randDE5], 500, 50);
				//自分カード準備
				image(cardimg[randME1], 1100, 50);
				image(cardimg[randME2], 1200, 50);
				image(cardimg[randME3], 1300, 50);
				image(cardimg[randME4], 1400, 50);
				image(cardimg[randME5], 1500, 50);
				textSize(70);
				text("ディーラーの数", 100, 560);
				text(GDE, 100, 650);
				text("自分の数", 1100, 560);
				text(GME, 1100, 650);
				textSize(200);
				text("VS", 850, 400);
				if (Scount == 0) {    //勝負が決まっていない間
					textSize(50);
					text("ヒットなら方向キー上･スタンドならenterキー", 850, 1080);
					text("＊カードは5枚まで", 1475, 1020);
				}
				//ヒット
				if (isTrigger(KEY_UP)) {
					//キーを押すたびにカード表示
					if (Hitcount == 0) {
						randME3 = rand() % 10 + 1;
						GME += randME3;
					}
					if (Hitcount == 1) {
						randME4 = rand() % 10 + 1;
						GME += randME4;
					}
					if (Hitcount == 2) {
						randME5 = rand() % 10 + 1;
						GME += randME5;
					}
					Hitcount++;
				}
				//ブラックジャックなら即勝ち
				if (GME == 21) {
					Scount = 5;
					re = 1;
				}
				if (Scount == 0) {//勝負が決まるまでしか押せない
					if (isTrigger(KEY_ENTER)) {    //スタンド
						re = 1;
						//ディーラーのカード2枚目以降表示
						if (GDE <= 18) {
							randDE3 = rand() % 10 + 1;
							GDE += randDE3;
						}
						if (GDE <= 18) {
							randDE4 = rand() % 10 + 1;
							GDE += randDE4;
						}
						if (GDE <= 18) {
							randDE5 = rand() % 10 + 1;
							GDE += randDE5;
						}
						//勝利条件
						if (GDE > GME && GDE <= 21) {
							Scount = 3;
						}
						if (GDE < GME && GME <= 21) {
							Scount = 4;
						}
						if (GDE > 21) {
							Scount = 2;
						}
						if (GME > 21) {
							Scount = 1;
						}
						if (GDE > 21 && GME > 21) {
							Scount = 6;
						}
						if (GDE == GME) {
							Scount = 6;
						}
						if (GDE == 21 && (GME != 21 || GME > 21)) {
							Scount = 7;
						}
					}
				}
				//勝利判定
				switch (Scount) {
				case 1:
					textSize(110);
					text("バースト！", 750, 800);
					text("YOU LOSE", 750, 900);
					break;
				case 2:
					textSize(110);
					text("ディーラーがバースト！", 350, 800);
					text("YOU WIN!", 750, 900);
					break;
				case 3:
					textSize(110);
					text("YOU LOSE", 750, 900);
					break;
				case 4:
					textSize(110);
					text("YOU WIN!", 750, 900);
					break;
				case 5:
					textSize(110);
					text("ブラックジャック！！！！！", 200, 800);
					text("VICTORY!!!!", 680, 900);
					break;
				case 6:
					textSize(110);
					text("DRAW", 850, 900);
					break;
				case 7:
					textSize(110);
					text("ディーラーがブラックジャック", 200, 800);
					text("YOU LOSE...", 680, 900);
				}
				//リセット
				if (re == 1) {
					textSize(50);
					text("以降のカードが見たい場合は方向キー上", 1020, 1080);
					text("方向キー下でリスタート", 1370, 1020);
					if (isTrigger(KEY_DOWN)) {
						reset();
					}
				}
			}
		}
		//ゲーム２
		if (gameselect == 2) {
			//BGM　ON
			if (BGM == 0) {
				playLoopSound(Soundgame1);//音楽再生
				BGM = 1;
			}
			if (gamest == 0) {
				//タイトル
				clear(0, 80, 0);
				textSize(150);
				text("ヨット", 700, 250);
				textSize(110);
				text("スペースキーを押してスタート", 200, 900);
				text("5つのサイコロで高得点を目指せ！", 150, 600);
				if (isTrigger(KEY_SPACE)) {//ゲームに入る
					gamest = 1;
				}
			}
			if (gamest != 0) {
				UI();
				help();
				//サイコロを振る回数表示
				if (pull == 0 && tarn !=0) {
					textSize(70);
					text("引ける回数:", 600, 100);
					text(role, 1000, 100);
				}
				//サイコロを振る前のロール状態
				if (role == 3) {
					diceME[0] = rand() % 6 + 1;
					diceME[1] = rand() % 6 + 1;
					diceME[2] = rand() % 6 + 1;
					diceME[3] = rand() % 6 + 1;
					diceME[4] = rand() % 6 + 1;
				}
				//数を入れる
				diceroll();
				//引ける回数がなくなったら押せない
				if (role == 0) { pull = 1; }
				if (role != 3) {
					//数の処理
					yaku();
					kakutei();
					lock();
				}
				//12回ずつ行動したあと勝利者発表
				if (tarn == 24){
					if (sumMEall > sumME2all) {
						text("1Pの勝利！", 1100, 350);
					}
					if (sumMEall < sumME2all) {
						text("2Pの勝利！", 1100, 350);
					}
					if (sumMEall == sumME2all) {
						text("DRAW", 1100, 350);
					}
				}
			}
		}
		fill(255);
		textSize(50);
		text("ESCキーでメニューに戻る", 1330, 50);
		if (isTrigger(KEY_ESCAPE) && gameselect == 0) {
			main()->backToMenu();
		}
		if (isTrigger(KEY_ESCAPE) && gameselect != 0) {
			gameselect = 0;
			gamest = 0;
			stopSound(Soundgame1);
			BGM = 0;
			reset();
		}
	}
}
