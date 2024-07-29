
#include "scene_switcher_title.h"

#include <DxLib.h>

namespace match_stick {

SceneSwitcherTitle::SceneSwitcherTitle(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const DxLibKeyboard>& keyboard_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    keyboard_ptr_(keyboard_ptr) {
}

void SceneSwitcherTitle::update() {
    if (keyboard_ptr_->isAnyKeyPressed()) {
    }
}

}  // namespace match_stick
