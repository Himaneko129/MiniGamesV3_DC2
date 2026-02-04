#pragma once
#include "../MAIN/GAME_BASE.h"
namespace GAME05
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
        class GAME_STRUCT* game_struct = {};
        class PLAYER* player = {};
        class MAP* map = {};
        class TITLE* title = {};
        class SELECT* select = {};
        class MAP2* map2 = {};
        class MAP3* map3 = {};
        FILE* fp = {};

    };
}
