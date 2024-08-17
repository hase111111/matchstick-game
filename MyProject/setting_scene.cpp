
#include "setting_scene.h"

#include "dxlib_assert.h"
#include "fade_effect.h"
#include "fps_displayer.h"
#include "input_scheme_displayer.h"
#include "setting_back_ground_base.h"

namespace match_stick {

SettingScene::SettingScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                           const std::shared_ptr<const FpsController>& fps_controller_ptr,
                           const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                           const std::shared_ptr<const DxLibInput>& input_ptr,
                           const std::shared_ptr<const FontLoader>& font_loader_ptr,
                           const std::shared_ptr<const ImageLoader>& img_loader_ptr,
                           const std::shared_ptr<const SoundEffectLoader>& sound_effect_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()) {
    // ヌルチェック
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
    ASSERT_NOT_NULL_PTR(fps_controller_ptr);
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(input_ptr);
    ASSERT_NOT_NULL_PTR(font_loader_ptr);
    ASSERT_NOT_NULL_PTR(img_loader_ptr);
    ASSERT_NOT_NULL_PTR(sound_effect_loader_ptr);

    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
    ASSERT_NOT_NULL_PTR(entity_updater_ptr_);

    // エンティティを追加
    entity_updater_ptr_->registerEntity(std::make_unique<SettingBackGroundBase>());
    entity_updater_ptr_->registerEntity(
        std::make_shared<FpsDisplayer>(fps_controller_ptr, language_record_ptr, font_loader_ptr));
    entity_updater_ptr_->registerEntity(std::make_shared<InputSchemeDisplayer>(input_ptr, img_loader_ptr));

    // フェードイン演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeIn, []() {});
    entity_updater_ptr_->registerEntity(fade_effect_ptr);
}

bool SettingScene::update() {
    entity_updater_ptr_->update();

    return true;
}

void SettingScene::draw() const {
    entity_updater_ptr_->draw();
}

}  // namespace match_stick
