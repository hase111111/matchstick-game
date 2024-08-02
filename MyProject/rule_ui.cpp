﻿
#include "rule_ui.h"

#include <cmath>

#include <DxLib.h>

#include "define.h"
#include "math_const.h"

namespace match_stick {

RuleUI::RuleUI(std::function<void()> on_button_pressed,
               const std::shared_ptr<const DxLibInput>& input_ptr,
               const std::shared_ptr<FontLoader>& font_loader,
               const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr) :
    on_button_pressed_(on_button_pressed),
    input_ptr_(input_ptr),
    rule_ui_hexagon_(input_ptr, font_loader, sound_effect_loader_ptr),
    font_handle_(font_loader->loadAndGetFontHandle("data/font/azuki_font24.dft")),
    sound_effect1_handle_(sound_effect_loader_ptr->loadAndGetSoundHandle("data/sound/selecting1.mp3")),
    sound_effect2_handle_(sound_effect_loader_ptr->loadAndGetSoundHandle("data/sound/hand_cancel.mp3")) {}

bool RuleUI::update() {
    if (already_button_pressed_) {
        return true;
    }

    rule_ui_hexagon_.update(!is_button_hovered_);

    updateButton();

    return true;
}

void RuleUI::draw() const {
    rule_ui_hexagon_.draw();

    drawButton();
}

void RuleUI::drawButton() const {
    const int button_width = Define::WIN_SIZEX / 6;
    const int button_height = Define::WIN_SIZEY / 12;
    const int button_x = Define::WIN_SIZEX - button_width - 5;
    const int button_y = Define::WIN_SIZEY - button_height - 5;

    if (is_button_hovered_) {
        DrawBox(button_x, button_y, button_x + button_width, button_y + button_height, GetColor(50, 50, 50), TRUE);
        DrawStringToHandle(button_x + 5, button_y + button_height / 2 - 10,
                           "前画面に戻る", GetColor(255, 255, 255), font_handle_);
    } else {
        DrawStringToHandle(button_x + 5, button_y + button_height / 2 - 10,
                           "前画面に戻る", GetColor(0, 0, 0), font_handle_);
    }

    DrawBoxAA(static_cast<float>(button_x), static_cast<float>(button_y),
              static_cast<float>(button_x + button_width),
              static_cast<float>(button_y + button_height), GetColor(0, 0, 0), FALSE, 3.0);
}

bool RuleUI::isButtonHovered() const {
    const int button_width = Define::WIN_SIZEX / 6;
    const int button_height = Define::WIN_SIZEY / 12;
    const int button_x = Define::WIN_SIZEX - button_width - 5;
    const int button_y = Define::WIN_SIZEY - button_height - 5;

    const int mouse_x = input_ptr_->getCursorPosX();
    const int mouse_y = input_ptr_->getCursorPosY();

    return button_x <= mouse_x && mouse_x <= button_x + button_width &&
        button_y <= mouse_y && mouse_y <= button_y + button_height;
}

void RuleUI::updateButton() {
    if (input_ptr_->getInputType() == DxLibInput::InputType::kMouse) {
        if (isButtonHovered() && !is_button_hovered_) {
            PlaySoundMem(sound_effect1_handle_, DX_PLAYTYPE_BACK);
            is_button_hovered_ = true;
        } else if (!isButtonHovered() && is_button_hovered_) {
            is_button_hovered_ = false;
        }

        if (is_button_hovered_ && input_ptr_->getMousePressingCount(MOUSE_INPUT_LEFT) == 1) {
            already_button_pressed_ = true;
            PlaySoundMem(sound_effect2_handle_, DX_PLAYTYPE_BACK);
            on_button_pressed_();
        }
    } else {
        if (input_ptr_->getKeyboardPressingCount(KEY_INPUT_LEFT) == 1 ||
            input_ptr_->getKeyboardPressingCount(KEY_INPUT_RIGHT) == 1) {
            PlaySoundMem(sound_effect1_handle_, DX_PLAYTYPE_BACK);
            is_button_hovered_ = !is_button_hovered_;
        }

        if (is_button_hovered_ && input_ptr_->getKeyboardPressingCount(KEY_INPUT_Z) == 1) {
            already_button_pressed_ = true;
            PlaySoundMem(sound_effect2_handle_, DX_PLAYTYPE_BACK);
            on_button_pressed_();
        }
    }
}

}  // namespace match_stick
