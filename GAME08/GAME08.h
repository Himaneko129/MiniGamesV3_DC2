#pragma once
#include "../MAIN/MAIN.h"
#include "../MAIN/GAME_BASE.h"
#include "Board.h"

namespace GAME08
{
    class GAME :public GAME_BASE{
    public:
        GAME(class MAIN* main);
        ~GAME() {}

        int create()override;
        void proc()override;
        void destroy()override;

    private:

        Board* board; // É`ÉFÉXî’
        
    };
}