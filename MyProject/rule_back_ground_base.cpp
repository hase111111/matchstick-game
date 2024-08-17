
#include "rule_back_ground_base.h"

#include <DxLib.h>

#include "game_const.h"

namespace match_stick {

void RuleBackGroundBase::draw() const {
    const unsigned int color_back = GetColor(0x21, 0x21, 0x21);
    const unsigned int color_white = GetColor(0xda, 0xda, 0xda);

    // 下地
    DrawBox(0, 0, GameConst::kResolutionX, GameConst::kResolutionY, color_white, TRUE);

    // ボックス
    const int box_size_x = GameConst::kResolutionX * 40 / 50;
    const int box_size_y = GameConst::kResolutionY * 42 / 50;
    const int x_dif = GameConst::kResolutionX / 18;
    const int y_dif = -GameConst::kResolutionY / 20;
    const int thick = -GameConst::kResolutionY / 128;
    DrawBox((GameConst::kResolutionX + x_dif - box_size_x) / 2, (GameConst::kResolutionY + y_dif - box_size_y) / 2,
            (GameConst::kResolutionX + x_dif + box_size_x) / 2, (GameConst::kResolutionY + y_dif + box_size_y) / 2,
            color_back, TRUE);
    DrawBox((GameConst::kResolutionX + x_dif - box_size_x) / 2 - thick,
            (GameConst::kResolutionY + y_dif - box_size_y) / 2 - thick,
            (GameConst::kResolutionX + x_dif + box_size_x) / 2 + thick,
            (GameConst::kResolutionY + y_dif + box_size_y) / 2 + thick,
            color_white, TRUE);
}

}  // namespace match_stick
