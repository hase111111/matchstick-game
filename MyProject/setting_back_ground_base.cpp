
#include "setting_back_ground_base.h"

#include <DxLib.h>

#include "game_const.h"

namespace match_stick {

void SettingBackGroundBase::draw() const {
    const unsigned int color_white = GetColor(0xda, 0xda, 0xda);

    DrawBox(0, 0, GameConst::kResolutionX, GameConst::kResolutionY, color_white, TRUE);
}

}  // namespace match_stick
