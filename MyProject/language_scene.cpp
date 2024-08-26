
#include "language_scene.h"

#include <functional>

#include "dxlib_assert.h"
#include "dxlib_debug_print.h"
#include "fade_effect.h"
#include "fps_displayer.h"
#include "input_scheme_displayer.h"
#include "language_back_ground_base.h"
#include "language_ui.h"

namespace match_stick {

LanguageScene::LanguageScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                             const std::shared_ptr<const FpsController>& fps_controller_ptr,
                             const std::shared_ptr<LanguageRecord>& language_record_ptr,
                             const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
                             const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()) {
    // ポインタのチェック
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
    ASSERT_NOT_NULL_PTR(fps_controller_ptr);
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);

    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
    ASSERT_NOT_NULL_PTR(entity_updater_ptr_);

    // エンティティの登録
    entity_updater_ptr_->registerEntity(
        std::make_shared<LanguageBackGroundBase>(language_record_ptr, dxlib_resource_loader_ptr));

    const auto on_back_button_clicked = [this]() {
        auto scene_change_func = [this]() {
            scene_change_listener_ptr_->requestDeleteAllScene();
            };

        entity_updater_ptr_->registerEntity(
            std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, scene_change_func));
        };

    entity_updater_ptr_->registerEntity(std::make_shared<LanguageUI>(
        language_record_ptr, dxlib_input_ptr, dxlib_resource_loader_ptr,
        std::bind(&LanguageScene::callBackOnBackButtonClicked, this, std::placeholders::_1)));

    // FPS 表示エンティティの登録
    entity_updater_ptr_->registerEntity(std::make_shared<FpsDisplayer>(
        fps_controller_ptr, language_record_ptr, dxlib_resource_loader_ptr));

    // 入力スキーム表示エンティティの登録
    entity_updater_ptr_->registerEntity(std::make_shared<InputSchemeDisplayer>(
        dxlib_input_ptr, dxlib_resource_loader_ptr));

    // フェードイン演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(60, FadeEffect::FadeType::kFadeIn, []() {});
    entity_updater_ptr_->registerEntity(fade_effect_ptr);
}

bool LanguageScene::update() {
    // エンティティの更新
    entity_updater_ptr_->update();

    return true;
}

void LanguageScene::draw() const {
    // エンティティの描画
    entity_updater_ptr_->draw();
}

void LanguageScene::callBackOnBackButtonClicked(const bool back_one_scene) {
    // バックボタンが押されたときの処理
    DEBUG_PRINT_IMPORTANT("Back button is clicked.");

    auto scene_change_func = [this]() { scene_change_listener_ptr_->requestDeleteScene(1, SceneChangeParameter{}); };
    auto all_delete_func = [this]() { scene_change_listener_ptr_->requestDeleteAllScene(); };

    if (back_one_scene) {
        entity_updater_ptr_->registerEntity(
            std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, scene_change_func));
    } else {
        entity_updater_ptr_->registerEntity(
            std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, all_delete_func));
    }
}

}  // namespace match_stick
