﻿
#include "dxlib_input.h"

#include "dxlib_debug_print.h"

namespace match_stick {

void DxLibInput::update() {
    constexpr double kMouseSensitivity = 1.0;

    keyboard_.update();
    mouse_.update();

    // 現在の入力方法を更新
    if (input_type_ == InputType::kKeyboard && !keyboard_.isAnyKeyPressed()) {
        if (mouse_.isAnyButtonPressed()) {
            DEBUG_PRINT("Mouse is pressed");
            input_type_ = InputType::kMouse;
        }

        if (mouse_.getDiffPos() > kMouseSensitivity) {
            DEBUG_PRINT("Mouse is moved");
            input_type_ = InputType::kMouse;
        }
    } else if (input_type_ == InputType::kMouse) {
        if (keyboard_.isAnyKeyPressed()) {
            DEBUG_PRINT("Keyboard is pressed");
            input_type_ = InputType::kKeyboard;
        }
    }
}

DxLibInput::InputType DxLibInput::getInputType() const {
    return input_type_;
}

}  // namespace match_stick
