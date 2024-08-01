﻿
#include "title_scene_switcher.h"

#include <DxLib.h>

namespace match_stick {

TitleSceneSwitcher::TitleSceneSwitcher(const std::shared_ptr<const DxLibInput>& input_ptr,
                                       const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr,
                                       const std::function<void()>& scene_change_func) :
    input_ptr_(input_ptr),
    scene_change_func_(scene_change_func),
    scene_change_sound_handle_(sound_effect_loader_ptr->loadAndGetSoundHandle("data/sound/op.mp3")) {}

bool TitleSceneSwitcher::update() {
    if (input_ptr_->getMousePressingCount(MOUSE_INPUT_LEFT) == 1 ||
        input_ptr_->getKeyboardPressingCount(KEY_INPUT_Z) == 1) {
        // シーン遷移
        scene_change_func_();

        PlaySoundMem(scene_change_sound_handle_, DX_PLAYTYPE_BACK);

        return false;
    }

    return true;
}

}  // namespace match_stick
