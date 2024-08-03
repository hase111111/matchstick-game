
#include "rule_text.h"

#include <DxLib.h>

#include "define.h"
#include "math_const.h"

namespace match_stick {

RuleText::RuleText(const std::shared_ptr<FontLoader>& font_loader) :
    font_handle_(font_loader->loadAndGetFontHandle("data/font/azuki_font32.dft")),
    box_left_(getBoxLeft()),
    box_top_(getBoxTop()),
    box_right_(getBoxRight()),
    box_bottom_(getBoxBottom()) {}

void RuleText::update(const int number) {
    ++counter_;

    number_ = number;
}

void RuleText::draw() const {
    const int center_x = box_left_ + Define::WIN_SIZEX / 20;
    const int center_y = box_top_ + Define::WIN_SIZEY / 12;
    const int radius = 35;
    const double angle_offset = counter_ * 0.005;
    const unsigned int edge_color = GetColor(0, 0, 0);
    const unsigned int fill_color = GetColor(255, 255, 255);

    drawHexagon(center_x, center_y, radius, false, angle_offset, edge_color, fill_color);

    // 現在の number を表示
    const std::string text = std::to_string(number_ + 1);
    const int text_width = GetDrawStringWidthToHandle(text.c_str(), static_cast<int>(text.size()), font_handle_);
    const int text_x = center_x - text_width / 2;
    const int text_y = center_y - 16;

    DrawStringToHandle(text_x, text_y, text.c_str(), GetColor(0, 0, 0), font_handle_);

}

void RuleText::drawHexagon(const int center_x, const int center_y, const int radius,
                           const bool fill, const double angle_offset,
                           const unsigned int edge_color, const unsigned int fill_color) const {
    constexpr int vertex_num = 6;
    const double angle = 360.0 / vertex_num;
    const float thickness = 3.0f;

    const float vertex_x[vertex_num] = {
    static_cast<float>(center_x + radius * cos(angle * 0 * MathConst<double>::kPi / 180 + angle_offset)),
    static_cast<float>(center_x + radius * cos(angle * 1 * MathConst<double>::kPi / 180 + angle_offset)),
    static_cast<float>(center_x + radius * cos(angle * 2 * MathConst<double>::kPi / 180 + angle_offset)),
    static_cast<float>(center_x + radius * cos(angle * 3 * MathConst<double>::kPi / 180 + angle_offset)),
    static_cast<float>(center_x + radius * cos(angle * 4 * MathConst<double>::kPi / 180 + angle_offset)),
    static_cast<float>(center_x + radius * cos(angle * 5 * MathConst<double>::kPi / 180 + angle_offset))
    };

    const float vertex_y[vertex_num] = {
    static_cast<float>(center_y + radius * sin(angle * 0 * MathConst<double>::kPi / 180 + angle_offset)),
    static_cast<float>(center_y + radius * sin(angle * 1 * MathConst<double>::kPi / 180 + angle_offset)),
    static_cast<float>(center_y + radius * sin(angle * 2 * MathConst<double>::kPi / 180 + angle_offset)),
    static_cast<float>(center_y + radius * sin(angle * 3 * MathConst<double>::kPi / 180 + angle_offset)),
    static_cast<float>(center_y + radius * sin(angle * 4 * MathConst<double>::kPi / 180 + angle_offset)),
    static_cast<float>(center_y + radius * sin(angle * 5 * MathConst<double>::kPi / 180 + angle_offset))
    };

    if (fill) {
        // 塗りつぶし
        DrawTriangleAA(vertex_x[0], vertex_y[0], vertex_x[1], vertex_y[1], vertex_x[5], vertex_y[5], fill_color, TRUE);
        DrawTriangleAA(vertex_x[1], vertex_y[1], vertex_x[2] - 1, vertex_y[2], vertex_x[5], vertex_y[5],
                       fill_color, TRUE);
        DrawTriangleAA(vertex_x[2], vertex_y[2], vertex_x[3], vertex_y[3], vertex_x[4], vertex_y[4], fill_color, TRUE);
        DrawTriangleAA(vertex_x[2], vertex_y[2], vertex_x[4], vertex_y[4], vertex_x[5] + 1, vertex_y[5],
                       fill_color, TRUE);
    }

    for (int i = 0; i < vertex_num; ++i) {
        DrawLineAA(vertex_x[i], vertex_y[i],
                   vertex_x[(i + 1) % vertex_num], vertex_y[(i + 1) % vertex_num],
                   edge_color, thickness);
    }
}

int RuleText::getBoxLeft() const {
    const int box_size_x = Define::WIN_SIZEX * 40 / 50;
    const int x_dif = Define::WIN_SIZEX / 18;
    return (Define::WIN_SIZEX + x_dif - box_size_x) / 2;
}

int RuleText::getBoxTop() const {
    const int box_size_y = Define::WIN_SIZEY * 42 / 50;
    const int y_dif = -Define::WIN_SIZEY / 20;
    return (Define::WIN_SIZEY + y_dif - box_size_y) / 2;
}

int RuleText::getBoxRight() const {
    const int box_size_x = Define::WIN_SIZEX * 40 / 50;
    const int x_dif = Define::WIN_SIZEX / 18;
    return (Define::WIN_SIZEX + x_dif + box_size_x) / 2;
}

int RuleText::getBoxBottom() const {
    const int box_size_y = Define::WIN_SIZEY * 42 / 50;
    const int y_dif = -Define::WIN_SIZEY / 20;
    return (Define::WIN_SIZEY + y_dif + box_size_y) / 2;
}

}  // namespace match_stick
