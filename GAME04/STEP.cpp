#include "../../libOne/inc/libOne.h"
#include "STEP.h"
#include "GAME04.h"

namespace GAME04 {

    extern float scrollX;

    void STEP::draw()
    {
        rect(x - scrollX, y, w, h);
    }

}
