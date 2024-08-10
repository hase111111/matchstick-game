﻿
#include "menu_ui.h"

#include <format>

#include <DxLib.h>
#include <magic_enum.hpp>

#include "dxlib_debug_print.h"
#include "define.h"

namespace match_stick {

MenuUI::MenuUI(const std::shared_ptr<const LanguageRecord>& language_record_ptr,
               const std::shared_ptr<const DxLibInput>& input_ptr,
               const std::shared_ptr<FontLoader>& font_loader_ptr,
               const std::shared_ptr<ImageLoader>& img_loader_ptr) :
    input_ptr_(input_ptr),
    font_handle_(font_loader_ptr->loadAndGetFontHandle("data/font/azuki_font32.dft")),
    big_font_handle_(font_loader_ptr->loadAndGetFontHandle("data/font/azuki_font48.dft")) {
    // 画像を読み込む
    bar_image_handle_map_[BarType::kGameStart] = img_loader_ptr->loadAndGetImageHandle("data/img/icon_game.png");
    bar_image_handle_map_[BarType::kRule] = img_loader_ptr->loadAndGetImageHandle("data/img/icon_rule.png");
    bar_image_handle_map_[BarType::kSetting] = img_loader_ptr->loadAndGetImageHandle("data/img/icon_setting.png");
    bar_image_handle_map_[BarType::kReplay] = img_loader_ptr->loadAndGetImageHandle("data/img/icon_replay.png");
    bar_image_handle_map_[BarType::kLanguage] = img_loader_ptr->loadAndGetImageHandle("data/img/icon_language.png");

    // 回転を初期化
    for (const auto bar_type : magic_enum::enum_values<BarType>()) {
        bar_rotation_map_[bar_type] = 0.0;
    }

    // テキストを初期化
    bar_text_map_[BarType::kGameStart] = language_record_ptr->get("menu_game");
    bar_text_map_[BarType::kRule] = language_record_ptr->get("menu_rule");
    bar_text_map_[BarType::kSetting] = language_record_ptr->get("menu_setting");
    bar_text_map_[BarType::kReplay] = language_record_ptr->get("menu_replay");
    bar_text_map_[BarType::kLanguage] = language_record_ptr->get("menu_language");
}

bool MenuUI::update() {
    // 回転を更新
    updateRotation();

    // 選択を更新
    updateSelectedBarType();

    if (selected_bar_type_ != getBarTypeFromIndex()) {
        selected_bar_type_ = getBarTypeFromIndex();
        bar_rotation_map_[selected_bar_type_] = 6.28;
        DEBUG_PRINT(std::format("index_x:={}, index_y:={}",
            selected_bar_index_x_ % kIndexMaxX, selected_bar_index_y_ % kIndexMaxY));
    }

    ++counter_;

    return true;
}

void MenuUI::draw() const {
    drawBar();

    drawButton();
}

void MenuUI::updateRotation() {
    for (auto& pair : bar_rotation_map_) {
        if (pair.second > 0.0) {
            pair.second -= 0.5;
        } else if (pair.second < 0.0) {
            pair.second = 0.0;
        }
    }
}

void MenuUI::updateSelectedBarType() {
    if (input_ptr_->getInputType() == DxLibInput::InputType::kKeyboard) {
        // 横方向の選択
        if (selected_bar_index_y_ % kIndexMaxY == 0 || selected_bar_index_y_ % kIndexMaxY == 2) {
            if (input_ptr_->getKeyboardPressingCount(KEY_INPUT_LEFT) == 1) {
                selected_bar_index_x_ = selected_bar_index_x_ % kIndexMaxX == 2 ? 0 : 2;
            } else if (input_ptr_->getKeyboardPressingCount(KEY_INPUT_RIGHT) == 1) {
                selected_bar_index_x_ = selected_bar_index_x_ % kIndexMaxX == 2 ? 0 : 2;
            }
        } else {
            if (input_ptr_->getKeyboardPressingCount(KEY_INPUT_LEFT) == 1) {
                selected_bar_index_x_ += kIndexMaxX - 1;
            } else if (input_ptr_->getKeyboardPressingCount(KEY_INPUT_RIGHT) == 1) {
                selected_bar_index_x_ += 1;
            }
        }

        // 縦方向の選択
        if (input_ptr_->getKeyboardPressingCount(KEY_INPUT_UP) == 1) {
            selected_bar_index_y_ += kIndexMaxY - 1;
        } else if (input_ptr_->getKeyboardPressingCount(KEY_INPUT_DOWN) == 1) {
            selected_bar_index_y_ += 1;
        }
    } else {
        const int input_x = input_ptr_->getCursorPosX();
        const int input_y = input_ptr_->getCursorPosY();

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < kIndexMaxX; ++j) {
                if (i == 0 && j == 0) { continue; }
                if (i == 0 && j == 1) { continue; }

                const int x = kBarStartX + (kBarWidth + kBarDistance) * j;
                const int y = kBarStartY + (kBarHeight + kBarDistance) * i;

                if (x <= input_x && input_x <= x + kBarWidth &&
                    y <= input_y && input_y <= y + kBarHeight) {
                    selected_bar_index_x_ = j;
                    selected_bar_index_y_ = i;
                }
            }
        }

        if (kBarStartX <= input_x && input_x <= kBarStartX + kBarWidth * 2 + kBarDistance &&
                   kBarStartY <= input_y && input_y <= kBarStartY + kBarHeight) {
            selected_bar_index_x_ = 0;
            selected_bar_index_y_ = 0;
        }

        // 下のボタン
        if (Define::kWindowSizeX - kButtonWidth * 2 - kButtonRight <= input_x &&
            input_x <= Define::kWindowSizeX - kButtonRight &&
            Define::kWindowSizeY - kButtonBottom - kButtonHeight <= input_y &&
            input_y <= Define::kWindowSizeY - kButtonBottom) {
            selected_bar_index_x_ = 0;
            selected_bar_index_y_ = 2;
        }

        if (Define::kWindowSizeX - kButtonWidth - kButtonRight <= input_x &&
            input_x <= Define::kWindowSizeX - kButtonRight &&
            Define::kWindowSizeY - kButtonBottom - kButtonHeight <= input_y &&
            input_y <= Define::kWindowSizeY - kButtonBottom) {
            selected_bar_index_x_ = 2;
            selected_bar_index_y_ = 2;
        }
    }
}

MenuUI::BarType MenuUI::getBarTypeFromIndex() const {
    const int index_x = selected_bar_index_x_ % kIndexMaxX;
    const int index_y = selected_bar_index_y_ % kIndexMaxY;

    if ((index_x == 0 && index_y == 0) || (index_x == 1 && index_y == 0)) {
        return BarType::kGameStart;
    } else if (index_x == 2 && index_y == 0) {
        return BarType::kRule;
    } else if (index_x == 0 && index_y == 1) {
        return BarType::kSetting;
    } else if (index_x == 1 && index_y == 1) {
        return BarType::kReplay;
    } else if (index_x == 2 && index_y == 1) {
        return BarType::kLanguage;
    }

    return BarType::kNone;
}

void MenuUI::drawBar() const {
    const unsigned int bar_color = GetColor(0x61, 0x61, 0x61);
    const unsigned int bar_inner_color = GetColor(0xe5, 0xe5, 0xe5);
    const unsigned int bar_hovered_color = GetColor(0xc0, 0xc0, 0xc0);

    // 縦2 × 横3のバーを描画
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            const BarType bar_type = static_cast<BarType>(j + i * 3 - 1);

            if (i == 0 && j == 0) { continue; }
            if (i == 0 && j == 1) { continue; }

            DrawBox(kBarStartX + (kBarWidth + kBarDistance) * j,
                    kBarStartY + (kBarHeight + kBarDistance) * i,
                    kBarStartX + (kBarWidth + kBarDistance) * j + kBarWidth,
                    kBarStartY + (kBarHeight + kBarDistance) * i + kBarHeight,
                    bar_color, TRUE);

            DrawBox(kBarStartX + (kBarWidth + kBarDistance) * j + kBarThickness,
                    kBarStartY + (kBarHeight + kBarDistance) * i + kBarThickness,
                    kBarStartX + (kBarWidth + kBarDistance) * j + kBarWidth - kBarThickness,
                    kBarStartY + (kBarHeight + kBarDistance) * i + kBarHeight - kBarThickness,
                    (bar_type == selected_bar_type_) ? bar_hovered_color : bar_inner_color, TRUE);

            // 画像を描画
            const int image_handle = bar_image_handle_map_.at(bar_type);
            DrawRotaGraph(kBarStartX + (kBarWidth + kBarDistance) * j + kBarWidth / 2,
                          kBarStartY + (kBarHeight + kBarDistance) * i + kBarHeight * 2 / 3,
                          0.8, bar_rotation_map_.at(bar_type), image_handle, TRUE);

            // テキストを描画
            const int text_width = GetDrawStringWidthToHandle(bar_text_map_.at(bar_type).c_str(),
                static_cast<int>(bar_text_map_.at(bar_type).size()), font_handle_);
            DrawStringToHandle(kBarStartX + (kBarWidth + kBarDistance) * j + kBarWidth / 2 - text_width / 2,
                               kBarStartY + (kBarHeight + kBarDistance) * i + kBarHeight / 5 - 20,
                               bar_text_map_.at(bar_type).c_str(),
                               GetColor(0x00, 0x00, 0x00), font_handle_);
        }
    }

    // 左上のバーは2つのバーを合わせたもの
    DrawBox(kBarStartX, kBarStartY, kBarStartX + kBarWidth * 2 + kBarDistance, kBarStartY + kBarHeight,
            bar_color, TRUE);

    DrawBox(kBarStartX + kBarThickness,
            kBarStartY + kBarThickness,
            kBarStartX + kBarWidth * 2 + kBarDistance - kBarThickness,
            kBarStartY + kBarHeight - kBarThickness,
            (BarType::kGameStart == selected_bar_type_) ? bar_hovered_color : bar_inner_color, TRUE);

    // 画像を描画
    const int image_handle = bar_image_handle_map_.at(BarType::kGameStart);
    DrawRotaGraph(kBarStartX + kBarWidth / 3 + kBarDistance / 2,
                  kBarStartY + kBarHeight / 2,
                  1.0, bar_rotation_map_.at(BarType::kGameStart), image_handle, TRUE);

    // テキストを描画
    const int text_width = GetDrawStringWidthToHandle(bar_text_map_.at(BarType::kGameStart).c_str(),
            static_cast<int>(bar_text_map_.at(BarType::kGameStart).size()), big_font_handle_);
    DrawStringToHandle(kBarStartX + kBarWidth * 5 / 4 + kBarDistance / 2 - text_width / 2,
                       kBarStartY + kBarHeight / 3 - 20,
                       bar_text_map_.at(BarType::kGameStart).c_str(),
                       GetColor(0x00, 0x00, 0x00), big_font_handle_);
}

void MenuUI::drawButton() const {
    const unsigned int bar_color = GetColor(0x61, 0x61, 0x61);
    const unsigned int bar_inner_color = GetColor(0xda, 0xda, 0xda);
    const unsigned int bar_hovered_color = GetColor(0xc0, 0xc0, 0xc0);

    const int index_x = selected_bar_index_x_ % kIndexMaxX;
    const int index_y = selected_bar_index_y_ % kIndexMaxY;

    // ボタンを描画
    for (int i = 0; i < 2; ++i) {
        DrawBox(Define::kWindowSizeX - kButtonWidth + i * (kButtonWidth + kBarThickness) - kButtonRight,
                Define::kWindowSizeY - kButtonBottom,
                Define::kWindowSizeX - kButtonWidth * 2 + i * (kButtonWidth + kBarThickness) - kButtonRight,
                Define::kWindowSizeY - kButtonBottom - kButtonHeight,
                bar_color, TRUE);

        unsigned int color = bar_inner_color;

        if (index_y == 2 && (index_x == 0 || index_x == 1) && i == 0) {
            color = bar_hovered_color;
        }

        if (index_y == 2 && index_x == 2 && i == 1) {
            color = bar_hovered_color;
        }

        DrawBox(Define::kWindowSizeX - kButtonWidth + i * (kButtonWidth + kBarThickness) - kButtonRight - kBarThickness,
            Define::kWindowSizeY - kButtonBottom - kBarThickness,
            Define::kWindowSizeX - kButtonWidth * 2 + i * (kButtonWidth + kBarThickness) - kButtonRight + kBarThickness,
            Define::kWindowSizeY - kButtonBottom - kButtonHeight + kBarThickness,
            color, TRUE);
    }
}

}  // namespace match_stick
