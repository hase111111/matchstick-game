﻿
#include "rule_ui.h"

#include <cmath>

#include <DxLib.h>

#include "game_const.h"
#include "dxlib_assert.h"
#include "math_const.h"

namespace match_stick {

RuleUI::RuleUI(const std::shared_ptr<const LanguageRecord>& language_record_ptr,
               const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
               const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr,
               std::function<void()> on_button_pressed) :
    on_button_pressed_(on_button_pressed),
    dxlib_input_ptr_(dxlib_input_ptr),
    rule_ui_hexagon_(language_record_ptr, dxlib_input_ptr, dxlib_resource_loader_ptr),
    rule_text_(language_record_ptr, dxlib_resource_loader_ptr),
    font24_handle_(dxlib_resource_loader_ptr->getFontHandle(language_record_ptr->getCurrentCountry(),
        "data/font/azuki_font24.dft")),
    sound_effect1_handle_(dxlib_resource_loader_ptr->getSoundHandle("data/sound/selecting3.mp3")),
    sound_effect2_handle_(dxlib_resource_loader_ptr->getSoundHandle("data/sound/selecting2.mp3")),
    button_text_(language_record_ptr->getValue("rule_back_scene")) {
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);
}

bool RuleUI::update() {
    if (already_button_pressed_) {
        return true;
    }

    const int pointing_numer = rule_ui_hexagon_.update(!is_button_hovered_);

    rule_text_.update(pointing_numer);

    updateButton();

    return true;
}

void RuleUI::draw() const {
    rule_ui_hexagon_.draw();

    rule_text_.draw();

    drawButton();
}

void RuleUI::drawButton() const {
    const int button_width = GameConst::kResolutionX / 6;
    const int button_height = GameConst::kResolutionY / 12;
    const int button_x = GameConst::kResolutionX - button_width - 5;
    const int button_y = GameConst::kResolutionY - button_height - 5;
    const int button_text_width =
        GetDrawStringWidthToHandle(button_text_.c_str(), static_cast<int>(button_text_.size()), font24_handle_);

    if (is_button_hovered_) {
        DrawBox(button_x, button_y, button_x + button_width, button_y + button_height, GetColor(50, 50, 50), TRUE);
        DrawStringToHandle(button_x + (button_width - button_text_width) / 2 - 5, button_y + button_height / 2 - 10,
                           button_text_.c_str(), GetColor(255, 255, 255), font24_handle_);
    } else {
        DrawStringToHandle(button_x + (button_width - button_text_width) / 2 - 5, button_y + button_height / 2 - 10,
                           button_text_.c_str(), GetColor(0, 0, 0), font24_handle_);
    }

    DrawBoxAA(static_cast<float>(button_x), static_cast<float>(button_y),
              static_cast<float>(button_x + button_width),
              static_cast<float>(button_y + button_height), GetColor(0, 0, 0), FALSE, 3.0);
}

bool RuleUI::isButtonHovered() const {
    const int button_width = GameConst::kResolutionX / 6;
    const int button_height = GameConst::kResolutionY / 12;
    const int button_x = GameConst::kResolutionX - button_width - 5;
    const int button_y = GameConst::kResolutionY - button_height - 5;

    const int mouse_x = dxlib_input_ptr_->getCursorPosX();
    const int mouse_y = dxlib_input_ptr_->getCursorPosY();

    return button_x <= mouse_x && mouse_x <= button_x + button_width &&
        button_y <= mouse_y && mouse_y <= button_y + button_height;
}

void RuleUI::updateButton() {
    if (dxlib_input_ptr_->getInputType() == DxLibInput::InputType::kMouse) {
        if (isButtonHovered() && !is_button_hovered_) {
            PlaySoundMem(sound_effect1_handle_, DX_PLAYTYPE_BACK);
            is_button_hovered_ = true;
        } else if (!isButtonHovered() && is_button_hovered_) {
            is_button_hovered_ = false;
        }

        if (is_button_hovered_ && dxlib_input_ptr_->getMousePressingCount(MOUSE_INPUT_LEFT) == 1) {
            already_button_pressed_ = true;
            PlaySoundMem(sound_effect2_handle_, DX_PLAYTYPE_BACK);
            on_button_pressed_();
        }
    } else {
        if (dxlib_input_ptr_->getKeyboardPressingCount(KEY_INPUT_LEFT) == 1 ||
            dxlib_input_ptr_->getKeyboardPressingCount(KEY_INPUT_RIGHT) == 1) {
            PlaySoundMem(sound_effect1_handle_, DX_PLAYTYPE_BACK);
            is_button_hovered_ = !is_button_hovered_;
        }

        if (is_button_hovered_ && dxlib_input_ptr_->getKeyboardPressingCount(KEY_INPUT_Z) == 1) {
            already_button_pressed_ = true;
            PlaySoundMem(sound_effect2_handle_, DX_PLAYTYPE_BACK);
            on_button_pressed_();
        }
    }
}

}  // namespace match_stick
