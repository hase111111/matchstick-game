
#include "language_ui.h"

#include <DxLib.h>

namespace match_stick {

LanguageUI::LanguageUI(const std::shared_ptr<const DxLibInput>& dxlib_input) :
    dxlib_input_(dxlib_input) {}

bool LanguageUI::update() {
    updateSelectIndex();

    return true;
}

void LanguageUI::draw() const {

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

}  // namespace match_stick
