
#include "setting_scene.h"

namespace match_stick {

SettingScene::SettingScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                           const std::shared_ptr<const FpsController>& entity_updater_ptr,
                           const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                           const std::shared_ptr<const DxLibInput>& input_ptr,
                           const std::shared_ptr<const FontLoader>& font_loader_ptr,
                           const std::shared_ptr<const ImageLoader>& img_loader_ptr,
                           const std::shared_ptr<const SoundEffectLoader>& sound_effect_loader_ptr) {}

bool SettingScene::update() {
    return true;
}

void SettingScene::draw() const {}

}  // namespace match_stick
