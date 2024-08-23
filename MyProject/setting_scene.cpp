
#include "setting_scene.h"

#include "dxlib_assert.h"
#include "dxlib_debug_print.h"
#include "fade_effect.h"
#include "fps_displayer.h"
#include "input_scheme_displayer.h"
#include "setting_back_ground_base.h"

namespace match_stick {

SettingScene::SettingScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                           const std::shared_ptr<const FpsController>& fps_controller_ptr,
                           const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                           const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
                           const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()) {
    // ヌルチェック
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
    ASSERT_NOT_NULL_PTR(fps_controller_ptr);
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);

    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
    ASSERT_NOT_NULL_PTR(entity_updater_ptr_);

    // エンティティを追加
    entity_updater_ptr_->registerEntity(std::make_unique<SettingBackGroundBase>());
    entity_updater_ptr_->registerEntity(std::make_shared<FpsDisplayer>(
        fps_controller_ptr, language_record_ptr, dxlib_resource_loader_ptr));
    entity_updater_ptr_->registerEntity(std::make_shared<InputSchemeDisplayer>(
        dxlib_input_ptr, dxlib_resource_loader_ptr));

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

void SettingScene::onReturnFromOtherScene(const SceneChangeParameter&) {
    DEBUG_PRINT_IMPORTANT("Now, SettingScene is returned from other scene.");
}

}  // namespace match_stick
