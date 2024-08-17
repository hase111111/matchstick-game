
#include "setting_back_ground_base.h"

#include <DxLib.h>

#include "game_const.h"

namespace match_stick {

void SettingBackGroundBase::draw() const {
    DrawBox(0, 0, GameConst::kResolutionX, GameConst::kResolutionY, GetColor(255, 255, 255), TRUE);
}

}  // namespace match_stick
