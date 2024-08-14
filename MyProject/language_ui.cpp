﻿
#include "language_ui.h"

#include <magic_enum.hpp>

#include <DxLib.h>

#include "define.h"
#include "string_util.h"

namespace {

constexpr int kTableWidth = 400;
constexpr int kTableColumnHeight = 60;
constexpr int kTableColumnNum = static_cast<int>(magic_enum::enum_count<::match_stick::LanguageRecord::Country>());
constexpr int kTableRow0Width = 60;
constexpr int kTableRow1Width = 340;
constexpr int kTableRowNum = 2;
constexpr int kTableThickness = 3;

constexpr int kTableLeftX = 100;
constexpr int kTableTopY = 130;

constexpr int kButtonWidth = 220;
constexpr int kButtonHeight = 60;
constexpr int kButtonThickness = 3;

constexpr int kButtonLeftX = ::match_stick::Define::kWindowSizeX - kButtonWidth * 3 / 2;
constexpr int kButtonTopY = ::match_stick::Define::kWindowSizeY - 2 * kButtonHeight - 50;
constexpr int kButtonDistance = 10;
constexpr int kButtonNum = 2;

const unsigned int color_back = GetColor(0x21, 0x21, 0x21);
const unsigned int color_white = GetColor(0xda, 0xda, 0xda);
const unsigned int color_hover = GetColor(0x80, 0x80, 0x80);

}  // namespace

namespace match_stick {

LanguageUI::LanguageUI(const std::shared_ptr<const LanguageRecord>& lang,
                       const std::shared_ptr<const DxLibInput>& dxlib_input,
                       const std::shared_ptr<FontLoader>& font_loader_ptr,
                       const std::shared_ptr<ImageLoader>& img_loader_ptr) :
    dxlib_input_(dxlib_input),
    current_country_(lang->getCurrentCountry()),
    hovered_country_(current_country_),
    checked_img_handle_(img_loader_ptr->loadAndGetImageHandle("data/img/icon_checked.png")),
    font_handle_(font_loader_ptr->loadAndGetFontHandle(lang->getCurrentCountry(), "data/font/azuki_font32.dft")),
    small_font_handle_(font_loader_ptr->loadAndGetFontHandle(lang->getCurrentCountry(), "data/font/azuki_font20.dft")) {}

bool LanguageUI::update() {
    updateSelectIndex();

    return true;
}

void LanguageUI::draw() const {
    drawButton();

    drawTable();

    drawText();
}

void LanguageUI::updateSelectIndex() {
    if (dxlib_input_->getInputType() == DxLibInput::InputType::kKeyboard) {
        // キーボード入力
        if (dxlib_input_->getKeyboardPressingCount(KEY_INPUT_DOWN) == 1) {
            select_index_y_++;
        } else if (dxlib_input_->getKeyboardPressingCount(KEY_INPUT_UP) == 1) {
            select_index_y_--;
        }

        // 横移動のときは縦の選択肢をリセット
        if (dxlib_input_->getKeyboardPressingCount(KEY_INPUT_RIGHT) == 1) {
            select_index_x_++;
            select_index_y_ = 0;
        } else if (dxlib_input_->getKeyboardPressingCount(KEY_INPUT_LEFT) == 1) {
            select_index_x_--;
            select_index_y_ = 0;
        }
    } else {
        // マウス入力
        const int mouse_x = dxlib_input_->getCursorPosX();
        const int mouse_y = dxlib_input_->getCursorPosY();

        // テーブル内にホバーしているかチェック
        for (int i = 0; i < kTableColumnNum; i++) {
            const int x1 = kTableLeftX;
            const int x2 = x1 + kTableRow0Width + kTableRow1Width;
            const int y1 = kTableTopY + i * (kTableColumnHeight - kTableThickness);
            const int y2 = y1 + kTableColumnHeight;

            if (x1 <= mouse_x && mouse_x <= x2 && y1 <= mouse_y && mouse_y <= y2) {
                select_index_x_ = 0;
                select_index_y_ = i;
                break;
            }
        }
    }

    // ホバーしている国を更新
    if (select_index_x_ % 2 == 0) {
        hovered_country_ = static_cast<LanguageRecord::Country>(select_index_y_ % kTableColumnNum);
    } else {
        hovered_country_ = current_country_;
    }
}

void LanguageUI::drawText() const {
    const std::string attention_str0{ "Attention!"};
    const std::string attention_str1{"After the change, you need to go back "};
    const std::string attention_str2{"to the title screen to apply the change."};

    const int text_left_x = Define::kWindowSizeX / 2 + 30;

    // テキストの描画
    DrawStringToHandle(text_left_x, kTableTopY, attention_str0.c_str(), color_back, small_font_handle_);
    DrawStringToHandle(text_left_x, kTableTopY + 40, attention_str1.c_str(), color_back, small_font_handle_);
    DrawStringToHandle(text_left_x, kTableTopY + 80, attention_str2.c_str(), color_back, small_font_handle_);
}

void LanguageUI::drawButton() const {
    // ボタンの描画
    for (int i = 0; i < kButtonNum; i++) {
        const int x = kButtonLeftX;
        const int y = kButtonTopY + i * (kButtonHeight + kButtonDistance);

        const unsigned int color = select_index_x_ % 2 == 1 && select_index_y_ % kButtonNum == i ?
            color_hover : color_white;

        DrawBox(x, y, x + kButtonWidth, y + kButtonHeight, color_back, TRUE);

        DrawBox(x + kButtonThickness, y + kButtonThickness,
                x + kButtonWidth - kButtonThickness, y + kButtonHeight - kButtonThickness,
                color, TRUE);
    }
}

void LanguageUI::drawTable() const {
    // テーブルの描画 kTableColumnNum * kTableRowNum のセルを描画
    for (int i = 0; i < kTableColumnNum; i++) {
        // 0列目
        const int x1 = kTableLeftX;
        const int x2 = x1 + kTableRow0Width;
        const int y1 = kTableTopY + i * (kTableColumnHeight - kTableThickness);
        const int y2 = y1 + kTableColumnHeight;
        DrawBox(x1, y1, x2, y2, color_back, TRUE);
        DrawBox(x1 + kTableThickness, y1 + kTableThickness,
                x2 - kTableThickness, y2 - kTableThickness,
                color_white, TRUE);

        // 1列目
        const int x3 = x2 - kTableThickness;
        const int x4 = x3 + kTableRow1Width;
        const unsigned int color = select_index_x_ % 2 == 0 && select_index_y_ % kTableColumnNum == i ?
            color_hover : color_white;
        DrawBox(x3, y1, x4, y2, color_back, TRUE);
        DrawBox(x3 + kTableThickness, y1 + kTableThickness,
                x4 - kTableThickness, y2 - kTableThickness,
                color, TRUE);

        // 文字列の描画
        const LanguageRecord::Country country = static_cast<LanguageRecord::Country>(i);
        const std::string str = string_util::EnumToStringRemoveTopK(country);
        const int text_width = GetDrawStringWidthToHandle(str.c_str(), static_cast<int>(str.length()), font_handle_);
        DrawStringToHandle((x3 + x4 - text_width) / 2, y1 + 10, str.c_str(), color_back, font_handle_);

        // チェックマークの描画
        if (current_country_ == country) {
            DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 0.8, 0.0, checked_img_handle_, TRUE);
        }

        // ホバー中の選択肢にも半透明のチェックマークを表示する
        if (hovered_country_ == country) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
            DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 0.8, 0.0, checked_img_handle_, TRUE);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
    }
}

}  // namespace match_stick
