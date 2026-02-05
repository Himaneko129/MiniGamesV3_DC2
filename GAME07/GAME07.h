#pragma once
#include "../MAIN/GAME_BASE.h"
#define TOTAL_CARDS 48
#define ARCANA_TYPES 22
namespace GAME07
{
    class GAME :
        public GAME_BASE
    {
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        void proc();
        void destroy();
    private:
        enum GameState {
            TITLE,
            INIT,
            ENEMY,
            PLAYER,
            WIN,
            LOSE,
            DRAW,
            TIE,
            JUDGE,
            JUDGE_ENEMY,
            RULE
        };
        GameState State = TITLE;
        void Title();
        void Rule();
        void Init();
        void Player();
        void Enemy();
        void Win();
        void Lose();
        void Draw();
        void Tie();
        void Judge();

        void applyEffect(int id);
        void updateMemory(int idx, int id);
        int taroturaImg;
        int tarot0Img;
        int tarot1Img;
        int tarot2Img;
        int tarot3Img;
        int tarot4Img;
        int tarot5Img;
        int tarot6Img;
        int tarot7Img;
        int tarot8Img;
        int tarot9Img;
        int tarot10Img;
        int tarot11Img;
        int tarot12Img;
        int tarot13Img;
        int tarot14Img;
        int tarot15Img;
        int tarot16Img;
        int tarot17Img;
        int tarot18Img;
        int tarot19Img;
        int tarot20Img;
        int tarot21Img;

        int tarotSnd;
        int clearSnd;
        int hangedSnd;

        int firstCardIdx = 0;    
        int secondCardIdx = 0;   
        int waitTimer;
        int memory[TOTAL_CARDS];

        float memory_accuracy = 0.5f;//“G‚Ì‹L‰¯—Í

        typedef enum { STATE_HIDDEN, STATE_REVEALED, STATE_TAKEN } CardState;
        typedef enum { POS_UPRIGHT, POS_REVERSED } Position;
        typedef struct {
            int id;             
            Position position;  
            CardState state;    
            int x, y;           
        } Card;
        Card board[TOTAL_CARDS];
        int score_player = 0;
        int score_cpu = 0;
        bool is_reversed_world = false; 
        int cards_remaining = TOTAL_CARDS;
        bool is_player_turn = true;
    };
   
}
