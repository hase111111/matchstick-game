
#include "debug_scene.h"

#include <DxLib.h>

#include "dxlib_debug_print.h"
#include "match_game_field.h"

namespace match_stick {

DebugScene::DebugScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                       const std::shared_ptr<const DxLibInput>& input_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    input_ptr_(input_ptr) {
    MatchGameRule rule;
    rule.negative_number_valid = true;
    rule.five_over_valid = true;
    rule.self_harm_valid = true;
    MatchGameField field;
    field = MatchGameField::createInitialField(rule);
    DEBUG_PRINT(field.toString());

    // 勝敗が決まるまで繰り返す
    while (true) {
        auto next_field_list = field.createNextFieldList(rule);
        if (next_field_list.empty()) {
            break;
        }

        int size = static_cast<int>(next_field_list.size());
        int index = GetRand(size - 1);
        field = std::get<0>(next_field_list[index]);
        DEBUG_PRINT(std::get<0>(next_field_list[index]).toString() + " " + std::get<1>(next_field_list[index]).toString());

        if (field.getState(rule) != MatchGameField::State::kGameContinue) {
            break;
        }
    }
}

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
