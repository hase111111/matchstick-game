
#include "title_scene_switcher.h"

#include <DxLib.h>

namespace match_stick {

TitleSceneSwitcher::TitleSceneSwitcher(const std::shared_ptr<const DxLibInput>& input_ptr,
                                       const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr,
                                       const std::function<void()>& scene_change_func) :
    dxlib_input_ptr_(input_ptr),
    scene_change_func_(scene_change_func),
    scene_change_sound_handle_(dxlib_resource_loader_ptr->getSoundHandle("data/sound/op.mp3")) {}

bool TitleSceneSwitcher::update() {
    if (dxlib_input_ptr_->getMousePressingCount(MOUSE_INPUT_LEFT) == 1 ||
        dxlib_input_ptr_->getKeyboardPressingCount(KEY_INPUT_Z) == 1) {
        // シーン遷移
        scene_change_func_();

        PlaySoundMem(scene_change_sound_handle_, DX_PLAYTYPE_BACK);

        return false;
    }

    return true;
}

}  // namespace match_stick
