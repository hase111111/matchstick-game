
#include "menu_back_ground_base.h"

#include <DxLib.h>

#include "define.h"

namespace match_stick {

void MenuBackGroundBase::draw() const {
    const unsigned int color_back = GetColor(0x21, 0x21, 0x21);
    const unsigned int color_white = GetColor(0xda, 0xda, 0xda);

    // 下地
    DrawBox(0, 0, GameConst::kWindowSizeX, GameConst::kWindowSizeY, color_white, TRUE);
}

}  // namespace match_stick
