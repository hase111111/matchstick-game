
#include "menu_back_ground_base.h"

#include <DxLib.h>

#include "game_const.h"

namespace match_stick {

void MenuBackGroundBase::draw() const {
    // 下地
    DrawBox(0, 0, GameConst::kResolutionX, GameConst::kResolutionY, GameConst::kWhiteColor, TRUE);
}

}  // namespace match_stick
