
#include "setting_back_ground_base.h"

#include <DxLib.h>

#include "define.h"

namespace match_stick {

void SettingBackGroundBase::draw() const {
    DrawBox(0, 0, Define::kWindowSizeX, Define::kWindowSizeY, GetColor(255, 255, 255), TRUE);
}

}  // namespace match_stick
