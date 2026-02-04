#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME07.h"
#include <time.h> 
#include<string>
namespace GAME07   
{				   
	int GAME::create()
	{
		State = TITLE;
		taroturaImg = loadImage("..\\main\\assets\\game07\\tarot_ura.png");
		tarot0Img = loadImage("..\\main\\assets\\game07\\00_fool.png");
		tarot1Img = loadImage("..\\main\\assets\\game07\\01_magician.png");
		tarot2Img = loadImage("..\\main\\assets\\game07\\02_high_priestess.png");
		tarot3Img = loadImage("..\\main\\assets\\game07\\03_empress.png");
		tarot4Img = loadImage("..\\main\\assets\\game07\\04_enperor.png");
		tarot5Img = loadImage("..\\main\\assets\\game07\\05_hierophant.png");
		tarot6Img = loadImage("..\\main\\assets\\game07\\06_lovers.png");
		tarot7Img = loadImage("..\\main\\assets\\game07\\07_chariot.png");
		tarot8Img= loadImage("..\\main\\assets\\game07\\08_justice.png");
		tarot9Img = loadImage("..\\main\\assets\\game07\\09_hermit.png");
		tarot10Img = loadImage("..\\main\\assets\\game07\\10_wheel.png");
		tarot11Img = loadImage("..\\main\\assets\\game07\\11_strength.png");
		tarot12Img = loadImage("..\\main\\assets\\game07\\12_hanged.png");
		tarot13Img = loadImage("..\\main\\assets\\game07\\13_death.png");
		tarot14Img = loadImage("..\\main\\assets\\game07\\14_temperance.png");
		tarot15Img = loadImage("..\\main\\assets\\game07\\15_devil.png");
		tarot16Img = loadImage("..\\main\\assets\\game07\\16_tower.png");
		tarot17Img = loadImage("..\\main\\assets\\game07\\17_star.png");
		tarot18Img = loadImage("..\\main\\assets\\game07\\18_moon.png");
		tarot19Img = loadImage("..\\main\\assets\\game07\\19_sun.png");
		tarot20Img = loadImage("..\\main\\assets\\game07\\20_judgement.png");
		tarot21Img = loadImage("..\\main\\assets\\game07\\21_world.png");

		tarotSnd=loadSound("..\\main\\assets\\game07\\tarot.wav");
		clearSnd = loadSound("..\\main\\assets\\game07\\clear.wav");
		hangedSnd = loadSound("..\\main\\assets\\game07\\hanged.wav");

		srand(time(NULL));
		return 0;  
	}

	void GAME::destroy()
	{

	}

	void GAME::proc()
	{
		if (State != TITLE)Draw();
		if (State == TITLE)Title();
		else if (State == RULE)Rule();
		else if (State == INIT)Init();
		else if (State == ENEMY)Enemy();
		else if (State == JUDGE)Judge();
		else if (State == JUDGE_ENEMY) Judge();
		else if (State == PLAYER)Player();
		else if (State == WIN)Win();
		else if (State == LOSE)Lose();
		else if (State == TIE)Tie();
	}

	void GAME::Title() {
		rectMode(CORNER);
		clear(0,100,0);
		fill(200,200,0);
		textSize(150);
		text("タロット神経衰弱", 350, 400);
		
		textSize(100);
		text("SPACEキー:プレイ", 500, 600);
		rectMode(CENTER);
		image(taroturaImg, 300, 300,0, 0.6);
		image(tarot0Img, 300, 300,0, 0.4);
		if (isTrigger(KEY_SPACE)) {
			State = INIT;
		}
		text("Rキー:遊び方", 500, 750);
		if (isTrigger(KEY_R)) {
			State=RULE;
		}
		fill(255, 0, 0);
		textSize(80);
		text("Enterでメニューに戻る", 150, height);
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}
	void GAME::Rule() {
		clear(0, 100, 0);
		text("このゲームは2人のプレイヤーが交互にカードをめくり図柄を揃えるゲームです", 50, 100);
		text("カードには正位置と逆位置があり正位置のカードを揃えるとポイントが加算され", 50, 150);
		text("逆位置のカードを揃えると減算されます", 50, 200);
		text("全てのカードがなくなった時、よりポイントが多いプレイヤーの勝利です", 50, 250);
		fill(255, 255, 0);
		text("一部のカードは正位置で揃える事で特殊な効果を発揮します", 50, 400);
		fill(255);
		text("「吊るされた男」のカードを正位置で揃えると以降のポイントの加算と減算が", 50, 450);
		text("逆転し、「愚者」のカードを正位置で揃えると元の仕様に戻ります", 50, 500);
		rectMode(CORNER);
		image(tarot12Img, 50, 550, 0, 0.5);
		image(tarot12Img, 150, 550, 0, 0.5);
		image(tarot0Img, 350, 550, 0, 0.5);
		image(tarot0Img, 450, 550, 0, 0.5);
		text("場に残っているカードの種類や相手との点数差を見て上手く「吊るされた男」の", 50, 800);
		text("効果を活用してみましょう", 50, 850);
		text("タイトルに戻る:SPACE", 50, 1000);
		if (isTrigger(KEY_SPACE)) {
			State = TITLE;
		}
	}
	void GAME::Init() {
		clear(0, 100, 0);
		
		firstCardIdx = -1;    
		secondCardIdx = -1;   
		waitTimer = 0;
		cards_remaining = 48; 
		is_reversed_world = false; 

		score_player = 0;
		score_cpu = 0;
		int idx = 0;
		for (int i = 0; i < TOTAL_CARDS; i++) memory[i] = -1;
		int special_ids[] = { 0, 12 };
		for (int i = 0; i < 2; i++) {
			int id = special_ids[i];
			for (int k = 0; k < 2; k++) { 
				Position p = (k == 0) ? POS_UPRIGHT : POS_REVERSED;
				for (int j = 0; j < 2; j++) {
					board[idx].id = id;
					board[idx].position = p;
					board[idx].state = STATE_HIDDEN;
					idx++;
				}
			}
		}

		int ratio_patterns[3][2] = { {8, 12}, {10, 10}, {12, 8} };
		int p_idx = rand() % 3;
		int num_upright_pairs = ratio_patterns[p_idx][0];

		int normal_ids[20];
		int n_idx = 0;
		for (int i = 1; i <= 21; i++) {
			if (i == 12) continue;
			normal_ids[n_idx++] = i;
		}

		for (int i = 0; i < 20; i++) {
			int r = rand() % 20;
			int tmp = normal_ids[i];
			normal_ids[i] = normal_ids[r];
			normal_ids[r] = tmp;
		}

		for (int i = 0; i < 20; i++) {
			Position pair_pos = (i < num_upright_pairs) ? POS_UPRIGHT : POS_REVERSED;
			for (int j = 0; j < 2; j++) {
				board[idx].id = normal_ids[i];
				board[idx].position = pair_pos;
				board[idx].state = STATE_HIDDEN;
				idx++;
			}
		}

		for (int i = 0; i < TOTAL_CARDS; i++) {
			int r = rand() % TOTAL_CARDS;
			Card temp = board[i];
			board[i] = board[r];
			board[r] = temp;
		}
		int cols = 8;                         
		int rows = 6;                         
		int card_w = 100;                     
		int card_h = 150;                     
		int spacing_x = 20;                   
		int spacing_y = 20;                   

		int total_w = cols * card_w + (cols - 1) * spacing_x;
		int total_h = rows * card_h + (rows - 1) * spacing_y;

		int start_x = (width - total_w) / 2;
		int start_y = (height - total_h) / 2 + 50;

		for (int i = 0; i < TOTAL_CARDS; i++) {
			int col = i % cols;
			int row = i / cols;
			board[i].x = start_x + col * (card_w + spacing_x);
			board[i].y = start_y + row * (card_h + spacing_y);
		}
		State = PLAYER;
	}
	void GAME::Draw() {
		clear(0, 100, 0); 

		fill(255);
		textSize(50);
		if (is_reversed_world) {
			text("FIELD: HANGED MAN", 10, 50);
		}
		else {
			text("FIELD: NORMAL", 10, 50);
		}
		

		std::string s = "PLAYER: " + std::to_string(score_player) + "  CPU: " + std::to_string(score_cpu);
		text(s.c_str(), 1400, 50);

		for (int i = 0; i < TOTAL_CARDS; i++) {
			if (board[i].state == STATE_TAKEN) continue;

			if (board[i].state == STATE_HIDDEN) {
				image(taroturaImg, board[i].x, board[i].y, 0, 0.6);
			}
			else {
				int targetImg;
				switch (board[i].id) {
				case 0:  targetImg = tarot0Img; break; 
				case 1:  targetImg = tarot1Img; break;
				case 2:  targetImg = tarot2Img; break;
				case 3:  targetImg = tarot3Img; break;
				case 4:  targetImg = tarot4Img; break;
				case 5:  targetImg = tarot5Img; break;
				case 6:  targetImg = tarot6Img; break;
				case 7:  targetImg = tarot7Img; break;
				case 8:  targetImg = tarot8Img; break;
				case 9:  targetImg = tarot9Img; break;
				case 10: targetImg = tarot10Img; break;
				case 11: targetImg = tarot11Img; break;
				case 12: targetImg = tarot12Img; break;
				case 13: targetImg = tarot13Img; break;
				case 14: targetImg = tarot14Img; break;
				case 15: targetImg = tarot15Img; break;
				case 16: targetImg = tarot16Img; break;
				case 17: targetImg = tarot17Img; break;
				case 18: targetImg = tarot18Img; break;
				case 19: targetImg = tarot19Img; break;
				case 20: targetImg = tarot20Img; break;
				case 21: targetImg = tarot21Img; break;
				default: targetImg = taroturaImg; break;
				}
				int angle = (board[i].position == POS_REVERSED) ? 180 : 0;
				image(targetImg, board[i].x, board[i].y, angle, 0.4);
			}
		}

	}
	void GAME::Player() {
		text("PLAYER TURN", 10, 100);
		if (isTrigger(MOUSE_LBUTTON)) {
			for (int i = 0; i < TOTAL_CARDS; i++) {
				if (board[i].state == STATE_HIDDEN) {
					if (mouseX >= board[i].x-50 && mouseX <= board[i].x +50 &&
						mouseY >= board[i].y-75 && mouseY <= board[i].y + 75) {

						board[i].state = STATE_REVEALED; 
						playSound(tarotSnd);
						updateMemory(i, board[i].id);
						if (firstCardIdx == -1) {
							firstCardIdx = i;
						}
						else {
							secondCardIdx = i;
							State = JUDGE;
							waitTimer = 0;
						}
						break;
					}
				}
			}
		}
		text("Enterでメニューへ", 0, height);
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
		
	}
	void GAME::Enemy(){
		text("ENEMY TURN", 10, 100);
		waitTimer++;

		if (firstCardIdx == -1) {
			if (waitTimer < 60) return; 

			int first = -1;

			for (int i = 0; i < TOTAL_CARDS; i++) {
				for (int j = i + 1; j < TOTAL_CARDS; j++) {
					if (memory[i] != -1 && memory[i] == memory[j] &&
						board[i].state == STATE_HIDDEN && board[j].state == STATE_HIDDEN) {

						bool isSpecial = (memory[i] == 0 || memory[i] == 12);
						if (isSpecial && board[i].position != board[j].position) continue;

						int predict_pts = (board[i].position == POS_UPRIGHT) ? 1 : -1;
						predict_pts *= -1; 
						if (is_reversed_world) predict_pts *= -1;

						if (predict_pts > 0) {
							first = i;
							break;
						}
					}
				}
				if (first != -1) break;
			}

			if (first == -1) {
				do {
					first = rand() % TOTAL_CARDS;
				} while (board[first].state != STATE_HIDDEN);
			}

			board[first].state = STATE_REVEALED;
			playSound(tarotSnd);
			updateMemory(first, board[first].id);
			firstCardIdx = first;

			waitTimer = 0; 
			return; 
		}

		else {
			if (waitTimer < 180) return;  

			int second = -1;
			int first = firstCardIdx; 

			for (int i = 0; i < TOTAL_CARDS; i++) {
				if (i != first && memory[i] == board[first].id && board[i].state == STATE_HIDDEN) {

					bool isSpecial = (board[first].id == 0 || board[first].id == 12);
					if (isSpecial && board[i].position != board[first].position) continue;

					int predict_pts = (board[first].position == POS_UPRIGHT) ? 1 : -1;
					predict_pts *= -1; 
					if (is_reversed_world) predict_pts *= -1;

					if (predict_pts > 0) {
						second = i;
						break;
					}
				}
			}

			if (second == -1) {
				do {
					second = rand() % TOTAL_CARDS;
				} while (second == first || board[second].state != STATE_HIDDEN);
			}

			board[second].state = STATE_REVEALED;
			playSound(tarotSnd);
			updateMemory(second, board[second].id);
			secondCardIdx = second;

			State = JUDGE_ENEMY;
			waitTimer = 0;
		}
		
	}
	void GAME::Judge() {
		if (State == JUDGE) {
			text("PLAYER TURN", 10, 100);
		}
		if (State == JUDGE_ENEMY) {
			text("ENEMY TURN", 10, 100);
		}
		waitTimer++;
		if (waitTimer < 60) return;

		if (board[firstCardIdx].id == board[secondCardIdx].id) {
			Position p1 = board[firstCardIdx].position;
			Position p2 = board[secondCardIdx].position;

			bool isSpecial = (board[firstCardIdx].id == 0 || board[firstCardIdx].id == 12);
			if (isSpecial && p1 != p2) {
				board[firstCardIdx].state = STATE_HIDDEN;
				board[secondCardIdx].state = STATE_HIDDEN;
				State = (State == JUDGE) ? ENEMY : PLAYER;
				goto RESET_JUDGE;
			}

			int pts = 0;
			if (p1 == POS_UPRIGHT && p2 == POS_UPRIGHT) { 
				pts = 1;
			}
			else if (p1 == POS_REVERSED && p2 == POS_REVERSED) pts = -1; 

			if (State == JUDGE_ENEMY) {
				pts *= -1;
			}

			if (is_reversed_world) {
				pts *= -1;
			}

			if (State == JUDGE) {
				score_player += pts;
				playSound(clearSnd);
				if (p1 == POS_UPRIGHT && p2 == POS_UPRIGHT) {
					applyEffect(board[firstCardIdx].id);
				}
			}
			else {
				score_cpu += pts;
				if (p1 == POS_REVERSED && p2 == POS_REVERSED) {
					applyEffect(board[firstCardIdx].id);
				}
			}

			board[firstCardIdx].state = STATE_TAKEN;
			board[secondCardIdx].state = STATE_TAKEN;
			cards_remaining -= 2;

			if (cards_remaining <= 0) {
				if (score_player > score_cpu) State = WIN;
				else if (score_player < score_cpu) State = LOSE;
				else State = TIE;
				return;
			}

			State = (State == JUDGE) ? PLAYER : ENEMY;
		}
		else {
			board[firstCardIdx].state = STATE_HIDDEN;
			board[secondCardIdx].state = STATE_HIDDEN;
			State = (State == JUDGE) ? ENEMY : PLAYER;
		}

	RESET_JUDGE:
		firstCardIdx = -1;
		secondCardIdx = -1;
		waitTimer = 0;
	}
	void GAME::Win() {
		clear(0, 50, 100); 
		fill(255, 215, 0); 
		textSize(150);
		text("YOU WIN", 700, 400);
		fill(255);
		textSize(50);
		text("タイトルに戻る:SPACE", 700, 800);
		if (isTrigger(KEY_SPACE)) {
			State = TITLE;
		}
	}
	void GAME::Lose() {
		clear(50, 0, 0);  
		fill(200, 0, 0);
		textSize(150);
		text("YOU LOSE", 700, 400);
		fill(255);
		textSize(50);
		text("タイトルに戻る:SPACE", 700, 800);
		if (isTrigger(KEY_SPACE)) {
			State = TITLE;
		}
	}
	void GAME::Tie() {
		clear(50, 50, 50); 
		fill(255);
		textSize(150);
		text("DRAW", 800, 400);
		fill(255);
		textSize(50);
		text("タイトルに戻る:SPACE", 700, 800);
		if (isTrigger(KEY_SPACE)) {
			State = TITLE;
		}
	}
	void GAME::applyEffect(int id) {
		if (id == 12) { 
			is_reversed_world = !is_reversed_world; 
			playSound(hangedSnd);
		}
		else if (id == 0) {
			is_reversed_world = false;
		}
	}
	void GAME::updateMemory(int idx,int id) {
		if ((float)rand() / RAND_MAX < memory_accuracy) {
			memory[idx] = id;
		}
	}
	
}
