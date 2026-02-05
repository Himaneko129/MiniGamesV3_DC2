#pragma once
#include"../MAIN/GAME_BASE.h"
#include"MATH.h"
#include"kanji.h"
namespace GAME01
{
    class GAME :
        public GAME_BASE
    {
    private:
        int currentScene = 0;
    public:
        int c2 = 1;
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        void proc();
        void destroy();
        void draw();
        MATH* math();
        KANJI* kanji();
        bool scene1;
    };
}

