#pragma once
#include "../MAIN/GAME_BASE.h"
namespace GAME02
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
        void reset();
        void diceroll();
        void yaku();
        void kakutei();
        void yotreset();
        void UI();
        void lock();
        void help();
    };
}
