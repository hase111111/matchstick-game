
#include "language_ui.h"

#include <DxLib.h>

#include "define.h"

namespace {

constexpr int kTableWidth = 400;
constexpr int kTableColumnHeight = 60;
constexpr int kTableColumnNum = 2;
constexpr int kTableRow0Width = 60;
constexpr int kTableRow1Width = 340;
constexpr int kTableRowNum = 2;
constexpr int kTableThickness = 3;

constexpr int kTableLeftX = 100;
constexpr int kTableTopY = 60;

constexpr int kButtonWidth = 220;
constexpr int kButtonHeight = 60;
constexpr int kButtonThickness = 3;

constexpr int kButtonLeftX = ::match_stick::Define::kWindowSizeX - kButtonWidth * 3 / 2;
constexpr int kButtonTopY = ::match_stick::Define::kWindowSizeY - 2 * kButtonHeight - 50;
constexpr int kButtonDistance = 10;

const unsigned int color_back = GetColor(0x21, 0x21, 0x21);
const unsigned int color_white = GetColor(0xda, 0xda, 0xda);

}  // namespace

namespace match_stick {

LanguageUI::LanguageUI(const std::shared_ptr<const DxLibInput>& dxlib_input) :
    dxlib_input_(dxlib_input) {}

bool LanguageUI::update() {
    updateSelectIndex();

    return true;
}

void LanguageUI::draw() const {
    drawButton();

    drawTable();
}

void LanguageUI::updateSelectIndex() {
    if (dxlib_input_->getInputType() == DxLibInput::InputType::kKeyboard) {
        // キーボード入力
        if (dxlib_input_->getKeyboardPressingCount(KEY_INPUT_DOWN)) {
            select_index_y_++;
        } else if (dxlib_input_->getKeyboardPressingCount(KEY_INPUT_UP)) {
            select_index_y_--;
        }

        if (dxlib_input_->getKeyboardPressingCount(KEY_INPUT_RIGHT)) {
            select_index_x_++;
        } else if (dxlib_input_->getKeyboardPressingCount(KEY_INPUT_LEFT)) {
            select_index_x_--;
        }
    } else {
        // マウス入力

    }
}

void LanguageUI::drawButton() const {
    // ボタンの描画
    for (int i = 0; i < 2; i++) {
        const int x = kButtonLeftX;
        const int y = kButtonTopY + i * (kButtonHeight + kButtonDistance);
        DrawBox(x, y, x + kButtonWidth, y + kButtonHeight, color_back, TRUE);

        DrawBox(x + kButtonThickness, y + kButtonThickness,
                x + kButtonWidth - kButtonThickness, y + kButtonHeight - kButtonThickness,
                color_white, TRUE);
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
        const int x3 = x2;
        const int x4 = x3 + kTableRow1Width;
        DrawBox(x3, y1, x4, y2, color_back, TRUE);
        DrawBox(x3 + kTableThickness, y1 + kTableThickness,
                       x4 - kTableThickness, y2 - kTableThickness,
                                      color_white, TRUE);
    }

}

}  // namespace match_stick
