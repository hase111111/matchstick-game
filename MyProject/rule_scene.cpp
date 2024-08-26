
#include "rule_scene.h"

#include "dxlib_assert.h"
#include "dxlib_debug_print.h"
#include "fade_effect.h"
#include "fps_displayer.h"
#include "input_scheme_displayer.h"
#include "rule_back_ground_base.h"
#include "rule_ui.h"

namespace match_stick {

RuleScene::RuleScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                     const std::shared_ptr<const FpsController>& fps_controller_ptr,
                     const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                     const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
                     const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()) {
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
    ASSERT_NOT_NULL_PTR(fps_controller_ptr);
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);

    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
    ASSERT_NOT_NULL_PTR(entity_updater_ptr_);

    // ルール画面のエンティティを登録
    entity_updater_ptr_->registerEntity(std::make_shared<FpsDisplayer>(
        fps_controller_ptr, language_record_ptr, dxlib_resource_loader_ptr));

    entity_updater_ptr_->registerEntity(std::make_shared<InputSchemeDisplayer>(
        dxlib_input_ptr, dxlib_resource_loader_ptr));

    entity_updater_ptr_->registerEntity(std::make_shared<RuleBackGroundBase>());

    const auto rule_ui_ptr = std::make_shared<RuleUI>(language_record_ptr, dxlib_input_ptr, dxlib_resource_loader_ptr,
        std::bind(&RuleScene::callBackReturnButton, this));
    entity_updater_ptr_->registerEntity(rule_ui_ptr);

    // フェードイン演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(60, FadeEffect::FadeType::kFadeIn, []() {});
    entity_updater_ptr_->registerEntity(fade_effect_ptr);
}

bool RuleScene::update() {
    entity_updater_ptr_->update();

    return true;
}

void RuleScene::draw() const {
    entity_updater_ptr_->draw();
}

void RuleScene::onReturnFromOtherScene(const SceneChangeParameter&) {
    DEBUG_PRINT_IMPORTANT("Now, RuleScene is returned from other scene.");
}

void RuleScene::callBackReturnButton() {
    // フェードアウト演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(60, FadeEffect::FadeType::kFadeOut, [this]() {
        scene_change_listener_ptr_->requestDeleteScene(1, SceneChangeParameter{});
    });

    entity_updater_ptr_->registerEntity(fade_effect_ptr);
}

}  // namespace match_stick

