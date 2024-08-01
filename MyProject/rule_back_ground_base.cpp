
#include "rule_back_ground_base.h"

#include <DxLib.h>

#include "define.h"

namespace match_stick {

void RuleBackGroundBase::draw() const {
    const unsigned int color_back = GetColor(0x21, 0x21, 0x21);
    const unsigned int color_white = GetColor(0xda, 0xda, 0xda);

    // 下地
    DrawBox(0, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, color_white, TRUE);

    //ボックス
    const int box_size_x = Define::WIN_SIZEX * 40 / 50;
    const int box_size_y = Define::WIN_SIZEY * 43 / 50;
    const int x_dif = Define::WIN_SIZEX / 18;
    const int y_dif = -Define::WIN_SIZEY / 20;
    const int thick = -Define::WIN_SIZEY / 128;
    DrawBox((Define::WIN_SIZEX + x_dif - box_size_x) / 2, (Define::WIN_SIZEY + y_dif - box_size_y) / 2,
            (Define::WIN_SIZEX + x_dif + box_size_x) / 2, (Define::WIN_SIZEY + y_dif + box_size_y) / 2,
            color_back, TRUE);
    DrawBox((Define::WIN_SIZEX + x_dif - box_size_x) / 2 - thick, (Define::WIN_SIZEY + y_dif - box_size_y) / 2 - thick,
            (Define::WIN_SIZEX + x_dif + box_size_x) / 2 + thick, (Define::WIN_SIZEY + y_dif + box_size_y) / 2 + thick,
            color_white, TRUE);

    ////文字を描画
    //std::string str = std::to_string(m_page + 1) + " / " + std::to_string(m_page_MAX);
    //DrawFormatStringToHandle((Define::WIN_SIZEX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font)) / 2, Define::WIN_SIZEY * 53 / 64, GetColor(0, 0, 0), m_font, str.c_str());

    //str = "左右キーでページ切り替え　　ESCで戻る";
    //DrawFormatStringToHandle(Define::WIN_SIZEX * 5 / 8 - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font) / 2, Define::WIN_SIZEY * 15 / 16, GetColor(0, 0, 0), m_font, str.c_str());
}

}  // namespace match_stick
