#pragma once

namespace GAME00 {

    enum class BGMType {
        NONE,
        TITLE,
        STAGE
    };

    void initBGM();
    void playBGM(BGMType type);
    void stopBGM();
    void setBGMVolume(int volPercent);
    long volumeToDS(int volPercent);
}
