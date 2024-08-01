
#include "dxlib_input.h"

#include "dxlib_debug_print.h"

namespace match_stick {

void DxLibInput::update() {
    keyboard_.update();
    mouse_.update();

    // 現在の入力方法を更新
    if (input_type_ == InputType::kKeyboard) {
        if (mouse_.isAnyButtonPressed()) {
            DEBUG_PRINT("DxLibInput::update() Mouse is pressed");
            input_type_ = InputType::kMouse;
        }
    } else if (input_type_ == InputType::kMouse) {
        if (keyboard_.isAnyKeyPressed()) {
            DEBUG_PRINT("DxLibInput::update() Keyboard is pressed");
            input_type_ = InputType::kKeyboard;
        }
    }
}

DxLibInput::InputType DxLibInput::getInputType() const {
    return input_type_;
}

}  // namespace match_stick
