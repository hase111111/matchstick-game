
#include "input_scheme_displayer.h"

#include <DxLib.h>

namespace match_stick {

InputSchemeDisplayer::InputSchemeDisplayer(const std::shared_ptr<const DxLibInput>& input_ptr,
                                           const std::shared_ptr<ImageLoader>& font_loader_ptr) :
    input_ptr_(input_ptr),
    keyboard_image_handle_(font_loader_ptr->loadAndGetImageHandle("data/img/icon_keyboard.png")),
    mouse_image_handle_(font_loader_ptr->loadAndGetImageHandle("data/img/icon_mouse.png")) {}

void InputSchemeDisplayer::draw() const {
    const int left_pos = 5;
    const int top_pos = 5;

    if (input_ptr_->getInputType() == DxLibInput::InputType::kKeyboard) {
        DrawGraph(left_pos, top_pos, keyboard_image_handle_, TRUE);
    } else if (input_ptr_->getInputType() == DxLibInput::InputType::kMouse) {
        DrawGraph(left_pos, top_pos, mouse_image_handle_, TRUE);
    }
}

}  // namespace match_stick

