
#include "menu_scene.h"

#include <DxLib.h>

#include "dxlib_assert.h"
#include "dxlib_debug_print.h"
#include "fade_effect.h"
#include "fps_displayer.h"
#include "input_scheme_displayer.h"
#include "menu_back_ground_base.h"
#include "menu_ui.h"

namespace match_stick {

MenuScene::MenuScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                     const std::shared_ptr<const FpsController>& fps_controller_ptr,
                     const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                     const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
                     const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()),
    sound_effect_handle_(dxlib_resource_loader_ptr->getSoundHandle("data/sound/selecting2.mp3")) {
    // ポインタが nullptr でないことを確認
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
    ASSERT_NOT_NULL_PTR(fps_controller_ptr);
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);

    ASSERT_NOT_NULL_PTR(entity_updater_ptr_);
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);

    // ルール画面のエンティティを登録
    entity_updater_ptr_->registerEntity(std::make_shared<FpsDisplayer>(
        fps_controller_ptr, language_record_ptr, dxlib_resource_loader_ptr));
    entity_updater_ptr_->registerEntity(std::make_shared<InputSchemeDisplayer>(dxlib_input_ptr, dxlib_resource_loader_ptr));
    entity_updater_ptr_->registerEntity(std::make_shared<MenuBackGroundBase>());

    const auto game_end_callback = [this]() { game_end_ = true; };
    const auto scene_back_callback = [this]() { sceneBackCallback(); };
    const auto scene_change_callback = [this](const SceneName scene_name) { sceneChangeCallback(scene_name); };

    entity_updater_ptr_->registerEntity(std::make_shared<MenuUI>(language_record_ptr, dxlib_input_ptr, dxlib_resource_loader_ptr,
        game_end_callback, scene_back_callback, scene_change_callback));

    // フェードイン演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeIn, []() {});
    entity_updater_ptr_->registerEntity(fade_effect_ptr);
}

bool MenuScene::update() {
    entity_updater_ptr_->update();

    // ゲーム終了フラグが立っていたら，ゲームを終了する．
    if (game_end_) {
        return false;
    }

    return true;
}

void MenuScene::draw() const {
    entity_updater_ptr_->draw();
}

void MenuScene::onReturnFromOtherScene(const SceneChangeParameter&) {
    DEBUG_PRINT_IMPORTANT("Now, MenuScene::onReturnFromOtherScene is called.");

    // フェードイン演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeIn, []() {});
    entity_updater_ptr_->registerEntity(fade_effect_ptr);

    // フラグをリセット
    now_scene_change_ = false;
}

void MenuScene::sceneBackCallback() {
    if (now_scene_change_) {
        return;
    }

    DEBUG_PRINT("MenuScene::sceneBackCallback called");

    now_scene_change_ = true;

    // フェードアウト演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, [this]() {
        scene_change_listener_ptr_->requestDeleteScene(1, SceneChangeParameter{});
    });

    entity_updater_ptr_->registerEntity(fade_effect_ptr);

    // サウンドを再生
    PlaySoundMem(sound_effect_handle_, DX_PLAYTYPE_BACK);
}

void MenuScene::sceneChangeCallback(const SceneName scene_name) {
    if (now_scene_change_) {
        return;
    }

    DEBUG_PRINT("MenuScene::sceneChangeCallback called");

    now_scene_change_ = true;

    // フェードアウト演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, [this, scene_name]() {
        scene_change_listener_ptr_->requestAddScene(scene_name, SceneChangeParameter{});
    });

    entity_updater_ptr_->registerEntity(fade_effect_ptr);

    // サウンドを再生
    PlaySoundMem(sound_effect_handle_, DX_PLAYTYPE_BACK);
}

}  // namespace match_stick

