﻿
#include "rule_scene.h"

#include "dxlib_assert.h"
#include "fade_effect.h"
#include "fps_displayer.h"
#include "input_scheme_displayer.h"
#include "rule_back_ground_base.h"
#include "rule_ui.h"

namespace match_stick {

RuleScene::RuleScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                     const std::shared_ptr<const FpsController>& entity_updater_ptr,
                     const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                     const std::shared_ptr<const DxLibInput>& input_ptr,
                     const std::shared_ptr<const FontLoader>& font_loader_ptr,
                     const std::shared_ptr<const ImageLoader>& img_loader_ptr,
                     const std::shared_ptr<const SoundEffectLoader>& sound_effect_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()) {
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
    ASSERT_NOT_NULL_PTR(entity_updater_ptr);
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(input_ptr);
    ASSERT_NOT_NULL_PTR(font_loader_ptr);
    ASSERT_NOT_NULL_PTR(img_loader_ptr);
    ASSERT_NOT_NULL_PTR(sound_effect_loader_ptr);

    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
    ASSERT_NOT_NULL_PTR(entity_updater_ptr_);

    // ルール画面のエンティティを登録
    entity_updater_ptr_->registerEntity(
        std::make_shared<FpsDisplayer>(entity_updater_ptr, language_record_ptr, font_loader_ptr));
    entity_updater_ptr_->registerEntity(std::make_shared<InputSchemeDisplayer>(input_ptr, img_loader_ptr));

    entity_updater_ptr_->registerEntity(std::make_shared<RuleBackGroundBase>());
    const auto rule_ui_ptr = std::make_shared<RuleUI>(language_record_ptr, input_ptr, font_loader_ptr,
        sound_effect_loader_ptr, std::bind(&RuleScene::callBackReturnButton, this));
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

void RuleScene::callBackReturnButton() {
    // フェードアウト演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(60, FadeEffect::FadeType::kFadeOut, [this]() {
        scene_change_listener_ptr_->requestDeleteScene(1, SceneChangeParameter{});
    });

    entity_updater_ptr_->registerEntity(fade_effect_ptr);
}

}  // namespace match_stick

