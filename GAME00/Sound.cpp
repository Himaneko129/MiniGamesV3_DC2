#include "../../libOne/inc/libOne.h"
#include "Sound.h"
#include <cmath>

namespace GAME00 {

    static int titleBGM = -1;
    static int stageBGM = -1;
    static int currentBGMIndex = -1;

    static BGMType current = BGMType::NONE;

    void initBGM()
    {
        titleBGM = loadSound("assets/GAME00/title.wav");
        stageBGM = loadSound("assets/GAME00/stage.wav");
    }


    void playBGM(BGMType type)
    {
        if (current == type) return;

        stopBGM();
        current = type;

        switch (type) {
        case BGMType::TITLE:
            currentBGMIndex = titleBGM;
            break;
        case BGMType::STAGE:
            currentBGMIndex = stageBGM;
            break;
        default:
            currentBGMIndex = -1;
            return;
        }

        playSound(currentBGMIndex);
    }



    void stopBGM()
    {
        if (currentBGMIndex >= 0) {
            stopSound(currentBGMIndex);
            currentBGMIndex = -1;
        }
        current = BGMType::NONE;
    }

    void setBGMVolume(int volPercent)
    {
        if (currentBGMIndex < 0) return;
        setVolume(currentBGMIndex, volumeToDS(volPercent));
    }

    long volumeToDS(int volPercent)
    {
        if (volPercent <= 0) return -10000;
        if (volPercent >= 100) return 0;

        float v = volPercent / 100.0f;

        float db = log10f(v) * 2000.0f;

        if (db < -10000) db = -10000;
        if (db > 0) db = 0;

        return (long)db;
    }


}
