
#include "rule_back_ground_base.h"

#include <DxLib.h>

#include "define.h"

namespace match_stick {

void RuleBackGroundBase::draw() const {
    const unsigned int color_back = GetColor(0x21, 0x21, 0x21);
    const unsigned int color_white = GetColor(0xda, 0xda, 0xda);

    // 下地
    DrawBox(0, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, color_white, TRUE);

    // ボックス
    const int box_size_x = Define::WIN_SIZEX * 40 / 50;
    const int box_size_y = Define::WIN_SIZEY * 42 / 50;
    const int x_dif = Define::WIN_SIZEX / 18;
    const int y_dif = -Define::WIN_SIZEY / 20;
    const int thick = -Define::WIN_SIZEY / 128;
    DrawBox((Define::WIN_SIZEX + x_dif - box_size_x) / 2, (Define::WIN_SIZEY + y_dif - box_size_y) / 2,
            (Define::WIN_SIZEX + x_dif + box_size_x) / 2, (Define::WIN_SIZEY + y_dif + box_size_y) / 2,
            color_back, TRUE);
    DrawBox((Define::WIN_SIZEX + x_dif - box_size_x) / 2 - thick, (Define::WIN_SIZEY + y_dif - box_size_y) / 2 - thick,
            (Define::WIN_SIZEX + x_dif + box_size_x) / 2 + thick, (Define::WIN_SIZEY + y_dif + box_size_y) / 2 + thick,
            color_white, TRUE);
}

}  // namespace match_stick
