
#include "rule_text.h"

#include <format>

#include <DxLib.h>

#include "define.h"
#include "dxlib_assert.h"
#include "dxlib_debug_print.h"
#include "math_const.h"

namespace match_stick {

RuleText::RuleText(const std::shared_ptr<const LanguageRecord>& lang,
                   const std::shared_ptr<FontLoader>& font_loader) :
    rule_text_(createRuleText(lang)),
    need_hyphen_(LanguageRecord::isEnglish(lang->getCurrentCountry())),
    big_font_handle_(font_loader->loadAndGetFontHandle(lang->getCurrentCountry(), "data/font/azuki_font32.dft")),
    small_font_handle_(font_loader->loadAndGetFontHandle(lang->getCurrentCountry(), "data/font/azuki_font24.dft")),
    box_left_(getBoxLeft()),
    box_top_(getBoxTop()),
    box_right_(getBoxRight()),
    box_bottom_(getBoxBottom()),
    current_country_(lang->getCurrentCountry()) {
    // ポインタが nullptr でないことを確認
    ASSERT_NOT_NULL_PTR(lang);
    ASSERT_NOT_NULL_PTR(font_loader);

    // ルールのテキストを更新
    updateDrawText();
}

void RuleText::update(const int number) {
    ++counter_;

    if (number_ != number) {
        DEBUG_PRINT(std::format("RuleText::update: number_:{}(index is {}) -> number:{}(index is {})",
            number_ + 1, number_, number + 1, number));

        hexagon_angle_velocity_ = MathConst<double>::kPi * 0.5;

        number_ = number;

        updateDrawText();
    }

    hexagon_angle_velocity_ = (hexagon_angle_velocity_ > 0.0) ?
        hexagon_angle_velocity_ - MathConst<double>::kPi * 0.05 : 0.0;
}

void RuleText::draw() const {
    drawNumberBox();

    drawText();
}

void RuleText::updateDrawText() {
    draw_text_.clear();

    if (rule_text_.size() <= number_) {
        DEBUG_PRINT(std::format("RuleText::updateDrawText: rule_text_ size:{} is less than number_:{}",
            rule_text_.size(), number_));
        return;
    }

    const int text_length = LanguageRecord::isEnglish(current_country_) ? 54 : 84;

    for (const auto& text : rule_text_[number_]) {
        // 文字列が，text_lengthを超える場合は，改行する
        if (text.size() > text_length) {
            for (size_t i = 0; i < text.size(); i += text_length) {
                std::string add_text = text.substr(i, text_length);

                if (need_hyphen_ && i + text_length < text.size() &&
                    add_text.back() != ' ' && text[i + text_length] != ' ') {
                    add_text += "-";
                }

                // テキストの先頭の空白を削除
                if (add_text.front() == ' ') {
                    add_text = add_text.substr(1);
                }

                draw_text_.push_back(add_text);
            }
        } else {
            draw_text_.push_back(text);
        }
    }
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

void RuleText::drawNumberBox() const {
    const int center_x = box_left_ + Define::kWindowSizeX / 20;
    const int center_y = box_top_ + Define::kWindowSizeY / 12;
    const int radius = 35;
    const double angle_offset = counter_ * MathConst<double>::kPi / 180 - hexagon_angle_velocity_;
    const unsigned int edge_color = GetColor(0, 0, 0);
    const unsigned int fill_color = GetColor(255, 255, 255);

    drawHexagon(center_x, center_y, radius, false, angle_offset, edge_color, fill_color);

    // 現在の number を表示
    const std::string text = std::to_string(number_ + 1);
    const int text_width = GetDrawStringWidthToHandle(text.c_str(), static_cast<int>(text.size()), big_font_handle_);
    const int text_x = center_x - text_width / 2;
    const int text_y = center_y - 16;

    DrawStringToHandle(text_x, text_y, text.c_str(), GetColor(0, 0, 0), big_font_handle_);
}

void RuleText::drawText() const {
    if (draw_text_.size() == 0) {
        return;
    }

    // タイトルを表示
    const std::string title = draw_text_[0];
    const int title_width = GetDrawStringWidthToHandle(title.c_str(), static_cast<int>(title.size()), big_font_handle_);

    DrawStringToHandle((box_left_ + box_right_ - title_width) / 2, box_top_ + 50,
                       title.c_str(), GetColor(0, 0, 0), big_font_handle_);

    // ルールのテキストを表示
    for (int i = 1; i < draw_text_.size(); ++i) {
        const std::string text = draw_text_[i];

        DrawStringToHandle(box_left_ + 40, box_top_ + 75 + 35 * i,
            text.c_str(), GetColor(0, 0, 0), small_font_handle_);
    }
}

std::vector<std::vector<std::string>> RuleText::createRuleText(
    const std::shared_ptr<const LanguageRecord>& language_record_ptr) const {
    // ルールのテキストを作成
    std::vector<std::vector<std::string>> result;

    const int text_num = 16;

    for (int i = 0; i < text_num; i++) {
        std::vector<std::string> rule_text;

        int j = 0;

        while (true) {
            std::string rule_text_key = std::format("rule_text_{}_{}", i, j);

            if (!language_record_ptr->has(rule_text_key)) {
                break;
            }

            rule_text.push_back(language_record_ptr->get(rule_text_key));

            ++j;
        }

        result.push_back(rule_text);
    }

    return result;
}

int RuleText::getBoxLeft() const {
    const int box_size_x = Define::kWindowSizeX * 40 / 50;
    const int x_dif = Define::kWindowSizeX / 18;
    return (Define::kWindowSizeX + x_dif - box_size_x) / 2;
}

int RuleText::getBoxTop() const {
    const int box_size_y = Define::kWindowSizeY * 42 / 50;
    const int y_dif = -Define::kWindowSizeY / 20;
    return (Define::kWindowSizeY + y_dif - box_size_y) / 2;
}

int RuleText::getBoxRight() const {
    const int box_size_x = Define::kWindowSizeX * 40 / 50;
    const int x_dif = Define::kWindowSizeX / 18;
    return (Define::kWindowSizeX + x_dif + box_size_x) / 2;
}

int RuleText::getBoxBottom() const {
    const int box_size_y = Define::kWindowSizeY * 42 / 50;
    const int y_dif = -Define::kWindowSizeY / 20;
    return (Define::kWindowSizeY + y_dif + box_size_y) / 2;
}

}  // namespace match_stick
