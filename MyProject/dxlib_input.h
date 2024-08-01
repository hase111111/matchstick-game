
#pragma once

#include "dxlib_keyboard.h"
#include "dxlib_mouse.h"

namespace match_stick {

class DxLibInput final {
public:
    enum class InputType {
        kKeyboard,
        kMouse,
    };

    DxLibInput() = default;
    ~DxLibInput() = default;

    void update();

    inline int getKeyboardPressingCount(const int key_code) const {
        return keyboard_.getPressingCount(key_code);
    }

    inline int getKeyboardReleasingCount(const int key_code) const {
        return keyboard_.getReleasingCount(key_code);
    }

    inline bool isAnyKeyboardPressed() const {
        return keyboard_.isAnyKeyPressed();
    }

    inline int getMousePressingCount(const int mouse_code) const {
        return mouse_.getPressingCount(mouse_code);
    }

    inline int getMouseReleasingCount(const int mouse_code) const {
        return mouse_.getReleasingCount(mouse_code);
    }

    inline int getCursorPosX() const {
        return mouse_.GetCursorPosX();
    }

    inline int getCursorPosY() const {
        return mouse_.getCursorPosY();
    }

    inline int getDiffPosX() const {
        return mouse_.getDiffPosX();
    }

    inline int getDiffPosY() const {
        return mouse_.getDiffPosY();
    }

    inline double getDiffPos() const {
        return mouse_.getDiffPos();
    }

    inline int getMouseWheelRot() const {
        return mouse_.getWheelRot();
    }

    inline bool isAnyMousePressed() const {
        return mouse_.isAnyButtonPressed();
    }

    InputType getInputType() const;

private:
    DxLibKeyboard keyboard_;
    DxLibMouse mouse_;

    InputType input_type_{ InputType::kKeyboard };
};

}  // namespace match_stick
