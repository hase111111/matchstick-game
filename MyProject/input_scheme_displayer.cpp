
#include "input_scheme_displayer.h"

#include <DxLib.h>

#include "dxlib_assert.h"

namespace match_stick {

InputSchemeDisplayer::InputSchemeDisplayer(
    const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
    const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr) :
    dxlib_input_ptr_(dxlib_input_ptr),
    keyboard_image_handle_(dxlib_resource_loader_ptr->getImageHandle("data/img/icon_keyboard.png")),
    mouse_image_handle_(dxlib_resource_loader_ptr->getImageHandle("data/img/icon_mouse.png")) {
    // nullptr チェック
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);

    ASSERT_NOT_NULL_PTR(dxlib_input_ptr_);
}

void InputSchemeDisplayer::draw() const {
    const int left_pos = 5;
    const int top_pos = 5;

    if (dxlib_input_ptr_->getInputType() == DxLibInput::InputType::kKeyboard) {
        DrawGraph(left_pos, top_pos, keyboard_image_handle_, TRUE);
    } else if (dxlib_input_ptr_->getInputType() == DxLibInput::InputType::kMouse) {
        DrawGraph(left_pos, top_pos, mouse_image_handle_, TRUE);
    }
}

}  // namespace match_stick

