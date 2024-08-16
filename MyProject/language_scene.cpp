﻿
#include "language_scene.h"

#include "dxlib_assert.h"
#include "fade_effect.h"
#include "fps_displayer.h"
#include "input_scheme_displayer.h"
#include "language_back_ground_base.h"
#include "language_ui.h"

namespace match_stick {

LanguageScene::LanguageScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                             const std::shared_ptr<const FpsController>& fps_controller_ptr,
                             const std::shared_ptr<LanguageRecord>& lang,
                             const std::shared_ptr<const DxLibInput>& input_ptr,
                             const std::shared_ptr<FontLoader>& font_loader_ptr,
                             const std::shared_ptr<ImageLoader>& img_loader_ptr,
                             const std::shared_ptr<SoundEffectLoader>& sound_effect_loader) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()) {
    // ポインタのチェック
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
    ASSERT_NOT_NULL_PTR(fps_controller_ptr);
    ASSERT_NOT_NULL_PTR(lang);
    ASSERT_NOT_NULL_PTR(input_ptr);
    ASSERT_NOT_NULL_PTR(font_loader_ptr);
    ASSERT_NOT_NULL_PTR(img_loader_ptr);
    ASSERT_NOT_NULL_PTR(sound_effect_loader);

    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
    ASSERT_NOT_NULL_PTR(entity_updater_ptr_);

    // エンティティの登録
    entity_updater_ptr_->registerEntity(
        std::make_shared<LanguageBackGroundBase>(lang, font_loader_ptr, img_loader_ptr));

    const auto on_back_button_clicked = [this]() {
        auto scene_change_func = [this]() {
            scene_change_listener_ptr_->requestDeleteAllScene();
            };

        entity_updater_ptr_->registerEntity(
            std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, scene_change_func));
        };

    entity_updater_ptr_->registerEntity(std::make_shared<LanguageUI>(
        lang, input_ptr, font_loader_ptr, img_loader_ptr, sound_effect_loader, on_back_button_clicked));

    // FPS 表示エンティティの登録
    entity_updater_ptr_->registerEntity(std::make_shared<FpsDisplayer>(fps_controller_ptr, lang, font_loader_ptr));

    // 入力スキーム表示エンティティの登録
    entity_updater_ptr_->registerEntity(std::make_shared<InputSchemeDisplayer>(input_ptr, img_loader_ptr));

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

}  // namespace match_stick
