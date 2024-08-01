
#include "debug_scene.h"

#include <DxLib.h>

namespace match_stick {

DebugScene::DebugScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                       const std::shared_ptr<const DxLibInput>& input_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    input_ptr_(input_ptr) {}

bool DebugScene::update() {
    if (input_ptr_->getKeyboardPressingCount(KEY_INPUT_ESCAPE) == 1) {
        return false;
    }

    if (input_ptr_->getKeyboardPressingCount(KEY_INPUT_R) == 1) {
        scene_change_listener_ptr_->requestDeleteScene(1, SceneChangeParameter{});
    }

    return true;
}

void DebugScene::draw() const {
    DrawString(0, 0, "Debug Scene", GetColor(255, 255, 255));
}

void DebugScene::onStart(const SceneChangeParameter&) {}

void match_stick::DebugScene::onReturnFromOtherScene(const SceneChangeParameter&) {}

}  // namespace match_stick
