
#include "debug_scene.h"

#include <DxLib.h>

namespace match_stick {

bool DebugScene::update() {
    return true;
}

void DebugScene::draw() const {
    DrawString(0, 0, "Debug Scene", GetColor(255, 255, 255));
}

void DebugScene::onStart(const SceneChangeParameter& parameter) {
}

void match_stick::DebugScene::onReturnFromOtherScene(const SceneChangeParameter& parameter) {
}

}  // namespace match_stick
