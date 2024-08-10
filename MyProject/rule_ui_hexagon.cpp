
#include "rule_ui_hexagon.h"

#include <format>
#include <cmath>

#include <DxLib.h>

#include "dxlib_assert.h"
#include "dxlib_debug_print.h"
#include "math_const.h"


namespace match_stick {

RuleUIHexagon::RuleUIHexagon(const std::shared_ptr<const DxLibInput>& input_ptr,
                             const std::shared_ptr<FontLoader>& font_loader,
                             const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr) :
    input_ptr_(input_ptr),
    font_handle_(font_loader->loadAndGetFontHandle("data/font/azuki_font32.dft")),
    sound_effect1_handle_(sound_effect_loader_ptr->loadAndGetSoundHandle("data/sound/selecting3.mp3")),
    sound_effect2_handle_(sound_effect_loader_ptr->loadAndGetSoundHandle("data/sound/selecting2.mp3")) {
    ASSERT_NOT_NULL_PTR(input_ptr_);
}

int RuleUIHexagon::update(const bool hexagon_is_hovered) {
    ++counter_;
    hover_counter_ = hover_counter_ > 0 ? hover_counter_ - 1 : 0;

    hexagon_is_hovered_ = hexagon_is_hovered;

    if (!hexagon_is_hovered_) { return current_pointing_; }

    const int hover_index = getHoverIndex(input_ptr_->getCursorPosX(), input_ptr_->getCursorPosY());

    if (input_ptr_->getInputType() == DxLibInput::InputType::kMouse) {
        // マウスによる操作
        if (current_hover_ != hover_index) {
            current_hover_ = hover_index;
            DEBUG_PRINT(std::format("RuleUIHexagon::update() hover_index: {}", current_hover_ + 1));

            if (current_hover_ != -1 && hover_counter_ == 0) {
                PlaySoundMem(sound_effect1_handle_, DX_PLAYTYPE_BACK);
                hover_counter_ = 3;
            }
        }

        if (input_ptr_->getMousePressingCount(MOUSE_INPUT_LEFT) == 1 && current_hover_ != -1) {
            current_pointing_ = current_hover_;
            DEBUG_PRINT(std::format("RuleUIHexagon::update() current_pointing: {}", current_pointing_ + 1));

            PlaySoundMem(sound_effect2_handle_, DX_PLAYTYPE_BACK);
        }
    } else {
        // キーボードによる操作
        current_hover_ = current_hover_ == -1 ? current_pointing_ : current_hover_;

        const int up_count = input_ptr_->getKeyboardPressingCount(KEY_INPUT_UP);
        if (up_count == 1 || (up_count % 8 == 4 && up_count > 20)) {
            current_hover_ = (current_hover_ - 1 + hexagon_num_) % hexagon_num_;
            DEBUG_PRINT(std::format("RuleUIHexagon::update() current_pointing: {}", current_hover_ + 1));

            PlaySoundMem(sound_effect1_handle_, DX_PLAYTYPE_BACK);
        }

        const int down_count = input_ptr_->getKeyboardPressingCount(KEY_INPUT_DOWN);
        if (down_count == 1 || (down_count % 8 == 4 && down_count > 20)) {
            current_hover_ = (current_hover_ + 1) % hexagon_num_;
            DEBUG_PRINT(std::format("RuleUIHexagon::update() current_pointing: {}", current_hover_ + 1));

            PlaySoundMem(sound_effect1_handle_, DX_PLAYTYPE_BACK);
        }

        if (input_ptr_->getKeyboardPressingCount(KEY_INPUT_Z) == 1) {
            current_pointing_ = current_hover_;
            DEBUG_PRINT(std::format("RuleUIHexagon::update() current_pointing: {}", current_pointing_ + 1));

            PlaySoundMem(sound_effect2_handle_, DX_PLAYTYPE_BACK);
        }
    }

    return current_pointing_;
}

void RuleUIHexagon::draw() const {
    // 互い違いに 10個の六角形を配置
    const unsigned int edge_color = GetColor(0, 0, 0);
    const int fill_color_value = 150 + static_cast<int>(25 * sin(counter_ / 10.0));
    const unsigned int fill_color = GetColor(fill_color_value, fill_color_value, fill_color_value);
    const unsigned int hover_color = GetColor(50, 50, 50);
    const unsigned int text_color = GetColor(255, 255, 255);

    for (int i = 0; i < hexagon_num_ / 2; ++i) {
        const int first_index = 2 * i + 1;

        const int x1 = hexagon_center_x_;
        const int y1 = hexagon_center_y_ + static_cast<int>(i * radius_ * cos(30 * MathConst<double>::kPi / 180) * 2);
        if (first_index == current_hover_ + 1 && hexagon_is_hovered_) {
            drawHexagon(x1, y1, radius_, true, edge_color, hover_color);
        } else {
            drawHexagon(x1, y1, radius_, (first_index == current_pointing_ + 1), edge_color, fill_color);
        }

        // 番号を描画
        const int dif1 = first_index > 9 ? 7 : 0;
        if (first_index == current_hover_ + 1 && hexagon_is_hovered_) {
            DrawFormatStringToHandle(x1 - 10 - dif1, y1 - 15, text_color, font_handle_, "%d", first_index);
        } else {
            DrawFormatStringToHandle(x1 - 10 - dif1, y1 - 15, edge_color, font_handle_, "%d", first_index);
        }

        const int second_index = 2 * i + 2;

        const int x2 = x1 + radius_ * 3 / 2;
        const int y2 = y1 + static_cast<int>(radius_ * cos(30 * MathConst<double>::kPi / 180));
        if (second_index == current_hover_ + 1 && hexagon_is_hovered_) {
            drawHexagon(x2, y2, radius_, true, edge_color, hover_color);
        } else {
            drawHexagon(x2, y2, radius_, (second_index == current_pointing_ + 1), edge_color, fill_color);
        }

        // 番号を描画
        const int dif2 = second_index > 9 ? 7 : 0;
        if (second_index == current_hover_ + 1 && hexagon_is_hovered_) {
            DrawFormatStringToHandle(x2 - 10 - dif2, y2 - 15, text_color, font_handle_, "%d", second_index);
        } else {
            DrawFormatStringToHandle(x2 - 10 - dif2, y2 - 15, edge_color, font_handle_, "%d", second_index);
        }
    }
}

void RuleUIHexagon::drawHexagon(int center_x, int center_y, int radius, bool fill,
                                unsigned int edge_color, unsigned int fill_color) const {
    constexpr int vertex_num = 6;
    constexpr double angle = 360.0 / vertex_num;
    const float thickness = 3.0f;

    const float vertex_x[vertex_num] = {
    static_cast<float>(center_x + radius * cos(angle * 0 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_x + radius * cos(angle * 1 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_x + radius * cos(angle * 2 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_x + radius * cos(angle * 3 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_x + radius * cos(angle * 4 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_x + radius * cos(angle * 5 * MathConst<double>::kPi / 180))
    };

    const float vertex_y[vertex_num] = {
    static_cast<float>(center_y + radius * sin(angle * 0 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_y + radius * sin(angle * 1 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_y + radius * sin(angle * 2 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_y + radius * sin(angle * 3 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_y + radius * sin(angle * 4 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_y + radius * sin(angle * 5 * MathConst<double>::kPi / 180))
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

int RuleUIHexagon::getHoverIndex(int x, int y) const {
    // 互い違いに配置された六角形の内部かどうかを判定
    for (int i = 0; i < hexagon_num_ / 2; ++i) {
        const int x1 = hexagon_center_x_;
        const int y1 = hexagon_center_y_ + static_cast<int>(i * radius_ * cos(30 * MathConst<double>::kPi / 180) * 2);
        if (isInsideHexagon(x, y, x1, y1, radius_)) {
            return 2 * i;
        }

        const int x2 = x1 + radius_ * 3 / 2;
        const int y2 = y1 + static_cast<int>(radius_ * cos(30 * MathConst<double>::kPi / 180));
        if (isInsideHexagon(x, y, x2, y2, radius_)) {
            return 2 * i + 1;
        }
    }

    return -1;
}

bool RuleUIHexagon::isInsideHexagon(int x, int y, int center_x, int center_y, int radius) const {
    constexpr int vertex_num = 6;
    constexpr double angle = 360.0 / vertex_num;

    const float vertex_x[vertex_num] = {
    static_cast<float>(center_x + radius * cos(angle * 0 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_x + radius * cos(angle * 1 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_x + radius * cos(angle * 2 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_x + radius * cos(angle * 3 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_x + radius * cos(angle * 4 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_x + radius * cos(angle * 5 * MathConst<double>::kPi / 180))
    };

    const float vertex_y[vertex_num] = {
    static_cast<float>(center_y + radius * sin(angle * 0 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_y + radius * sin(angle * 1 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_y + radius * sin(angle * 2 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_y + radius * sin(angle * 3 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_y + radius * sin(angle * 4 * MathConst<double>::kPi / 180)),
    static_cast<float>(center_y + radius * sin(angle * 5 * MathConst<double>::kPi / 180))
    };

    // 判定点が六角形の辺のどちら側にあるかを確認するためのヘルパー関数
    auto isLeft = [](float x1, float y1, float x2, float y2, float px, float py) {
        return (x2 - x1) * (py - y1) - (y2 - y1) * (px - x1) > 0;
        };

    bool inside = true;
    for (int i = 0; i < vertex_num; ++i) {
        int next = (i + 1) % vertex_num;
        if (!isLeft(vertex_x[i], vertex_y[i], vertex_x[next], vertex_y[next],
            static_cast<float>(x), static_cast<float>(y))) {
            inside = false;
            break;
        }
    }

    return inside;
}

}  // namespace match_stick
