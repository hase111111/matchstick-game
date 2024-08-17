
#include "rule_back_ground_base.h"

#include <DxLib.h>

#include "define.h"

namespace match_stick {

void RuleBackGroundBase::draw() const {
    const unsigned int color_back = GetColor(0x21, 0x21, 0x21);
    const unsigned int color_white = GetColor(0xda, 0xda, 0xda);

    // 下地
    DrawBox(0, 0, GameConst::kWindowSizeX, GameConst::kWindowSizeY, color_white, TRUE);

    // ボックス
    const int box_size_x = GameConst::kWindowSizeX * 40 / 50;
    const int box_size_y = GameConst::kWindowSizeY * 42 / 50;
    const int x_dif = GameConst::kWindowSizeX / 18;
    const int y_dif = -GameConst::kWindowSizeY / 20;
    const int thick = -GameConst::kWindowSizeY / 128;
    DrawBox((GameConst::kWindowSizeX + x_dif - box_size_x) / 2, (GameConst::kWindowSizeY + y_dif - box_size_y) / 2,
            (GameConst::kWindowSizeX + x_dif + box_size_x) / 2, (GameConst::kWindowSizeY + y_dif + box_size_y) / 2,
            color_back, TRUE);
    DrawBox((GameConst::kWindowSizeX + x_dif - box_size_x) / 2 - thick, (GameConst::kWindowSizeY + y_dif - box_size_y) / 2 - thick,
            (GameConst::kWindowSizeX + x_dif + box_size_x) / 2 + thick, (GameConst::kWindowSizeY + y_dif + box_size_y) / 2 + thick,
            color_white, TRUE);
}

}  // namespace match_stick
