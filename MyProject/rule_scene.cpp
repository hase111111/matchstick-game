
#include "rule_scene.h"

namespace match_stick {

RuleScene::RuleScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                     const std::shared_ptr<const FpsController>& entity_updater_ptr,
                     const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                     const std::shared_ptr<const DxLibKeyboard>& keyboard_ptr,
                     const std::shared_ptr<FontLoader>& font_loader_ptr,
                     const std::shared_ptr<ImageLoader>& img_loader_ptr,
                     const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr) {}

bool RuleScene::update() {
    return false;
}

void RuleScene::draw() const {}

void RuleScene::onReturnFromOtherScene(const SceneChangeParameter& parameter) {}

}  // namespace match_stick

