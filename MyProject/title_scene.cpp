
#include "title_scene.h"

#include <DxLib.h>

#include "dxlib_assert.h"
#include "dxlib_debug_print.h"
#include "fade_effect.h"
#include "fps_displayer.h"
#include "input_scheme_displayer.h"
#include "title_back_ground_base.h"
#include "title_hand_animation.h"
#include "title_logo.h"
#include "title_scene_switcher.h"

namespace match_stick {

TitleScene::TitleScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                       const std::shared_ptr<const FpsController>& fps_controller_ptr,
                       const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                       const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
                       const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()),
    dxlib_input_ptr_(dxlib_input_ptr),
    dxlib_resource_loader_ptr_(dxlib_resource_loader_ptr) {
    // nullptr チェック
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
    ASSERT_NOT_NULL_PTR(fps_controller_ptr);
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);

    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
    ASSERT_NOT_NULL_PTR(entity_updater_ptr_);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr_);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr_);

    // タイトルのエンティティを登録
    entity_updater_ptr_->registerEntity(std::make_shared<TitleBackGroundBase>(dxlib_resource_loader_ptr));

    entity_updater_ptr_->registerEntity(std::make_shared<TitleLogo>(
        dxlib_input_ptr, language_record_ptr, dxlib_resource_loader_ptr));

    entity_updater_ptr_->registerEntity(std::make_shared<TitleHandAnimation>(dxlib_resource_loader_ptr));

    entity_updater_ptr_->registerEntity(std::make_shared<FpsDisplayer>(
        fps_controller_ptr, language_record_ptr, dxlib_resource_loader_ptr_));

    entity_updater_ptr_->registerEntity(std::make_shared<InputSchemeDisplayer>(
        dxlib_input_ptr_, dxlib_resource_loader_ptr_));

    // シーン遷移用のエンティティを登録
    entity_updater_ptr_->registerEntity(std::make_shared<TitleSceneSwitcher>(
        dxlib_input_ptr_, dxlib_resource_loader_ptr_, std::bind(&TitleScene::callbackForSceneChange, this)));

    // フェードイン演出を追加
    auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeIn, []() {});
    entity_updater_ptr_->registerEntity(fade_effect_ptr);
}

bool TitleScene::update() {
    if (dxlib_input_ptr_->getKeyboardPressingCount(KEY_INPUT_ESCAPE) == 1) {
        return false;
    }

    entity_updater_ptr_->update();

    return true;
}

void TitleScene::draw() const {
    entity_updater_ptr_->draw();
}

void TitleScene::onReturnFromOtherScene(const SceneChangeParameter&) {
    DEBUG_PRINT_IMPORTANT("Now, TitleScene is returned from other scene.");

    // フェードイン演出を追加
    auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeIn, []() {});
    entity_updater_ptr_->registerEntity(fade_effect_ptr);

    // シーン遷移用のエンティティを登録
    entity_updater_ptr_->registerEntity(std::make_shared<TitleSceneSwitcher>(dxlib_input_ptr_, dxlib_resource_loader_ptr_,
        std::bind(&TitleScene::callbackForSceneChange, this)));
}

void TitleScene::callbackForSceneChange() {
    auto scene_change_func = [this]() {
        scene_change_listener_ptr_->requestAddScene(SceneName::kMenu, SceneChangeParameter{});
        };

    auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, scene_change_func);

    entity_updater_ptr_->registerEntity(fade_effect_ptr);
}

}  // namespace match_stick
