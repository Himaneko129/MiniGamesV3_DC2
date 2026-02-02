#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME01.h"
#include "time.h"
#include"math.h"
#include"kanji.h"
namespace GAME01
{
	int GAME::create()  //1回限り
	{
		return 0;
	}

	void GAME::destroy()
	{

	}

	MATH* GAME::math()
	{
		static MATH mathInstance;
		return &mathInstance;
	}

	KANJI* GAME::kanji()
	{
		static KANJI kanjiInstance;
		return &kanjiInstance;
	}

	void GAME::draw()
	{
		clear(0, 0, 64);
		textSize(80);
		fill(255, 255, 0);
		text("脳トレ", 820, 100);
		textSize(50);
		fill(255);
		text("ENTERキーでメニューに戻る", 620, 980);
		fill(0, 255, 0);
		rect(100, 200, 800, 300);
		textSize(60);
		fill(0);
		text("四則演算/「M」KEYを押す", 100, 380);
		textSize(30);
		fill(255);
		text("四則の演算をするモードです。※不正解でも次に進めます。", 900, 380);
		fill(255, 0, 0);
		rect(100, 600, 800, 300);
		textSize(60);
		fill(0);
		text("漢字問題/「K」KEYを押す", 100, 780);
		textSize(30);
		fill(255);
		text("様々な漢字の問題を解くモードです。※不正解でも次に進めます。", 900, 780);
		if (MATH::cont == 1) {
			textSize(50);
			fill(255);
			text("計算:コンテニュー", 520, 1080);
		}
		if (KANJI::cont == 1) {
			textSize(50);
			fill(255);
			text("漢字:コンテニュー", 1220, 1080);
		}
		return;
	}

	void GAME::proc() {
		if (currentScene== 0) {
			draw();
			if (isTrigger(KEY_M)) {
				currentScene = 1;
			}
			if (isTrigger(KEY_K)) {
				KANJI* k = KANJI::kanji1();
				k->initialize();
				currentScene = 2;
			}
			if (isTrigger(KEY_ENTER)) {
				MATH::cont = 0;
				KANJI::cont = 0;
				/*Kanser1Generated = false;*/
				main()->backToMenu();
			}
		}
		else if (currentScene == 1) {
			MATH* Imath = GAME::math();
			Imath->proc();
			if (isTrigger(KEY_LEFT)) {
				currentScene = 0;
			}
		}
		else if (currentScene == 2) {
			KANJI* Ikanji = GAME::kanji();
			Ikanji->proc();
			if (isTrigger(KEY_LEFT)) {
				currentScene = 0;
			}
		}
	}
}

