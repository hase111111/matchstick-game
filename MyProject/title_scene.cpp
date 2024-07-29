
#include "title_scene.h"

#include <DxLib.h>

#include "fade_effect.h"
#include "title_back_ground_base.h"
#include "title_hand_animation.h"
#include "title_logo.h"

namespace match_stick {

TitleScene::TitleScene(
    std::shared_ptr<SceneChangeListener> scene_change_listener_ptr,
    std::shared_ptr<const LanguageRecord> language_record_ptr,
    std::shared_ptr<const DxLibKeyboard> keyboard_ptr,
    std::shared_ptr<FontLoader> font_loader_ptr,
    std::shared_ptr<ImageLoader> img_loader_ptr,
    std::shared_ptr<SoundEffectLoader> sound_effect_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    keyboard_ptr_(keyboard_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()) {
    entity_updater_ptr_->registerEntity(std::make_shared<TitleBackGroundBase>(img_loader_ptr));

    auto title_logo_ptr_ = std::make_shared<TitleLogo>(language_record_ptr, font_loader_ptr);
    entity_updater_ptr_->registerEntity(title_logo_ptr_);

    auto title_hand_animation_ptr_ = std::make_shared<TitleHandAnimation>(img_loader_ptr);
    entity_updater_ptr_->registerEntity(title_hand_animation_ptr_);

    scene_change_sound_handle_ = sound_effect_loader_ptr->loadAndGetSoundHandle("data/sound/op.mp3");
}

bool TitleScene::update() {
    if (keyboard_ptr_->getPressingCount(KEY_INPUT_ESCAPE) == 1) {
        return false;
    }

    if (keyboard_ptr_->isAnyKeyPressed() && !is_scene_change_requested_) {
        auto scene_change_func = [this]() {
            scene_change_listener_ptr_->requestAddScene(SceneName::kDebug, SceneChangeParameter{});
            };
        auto fade_effect_ptr = std::make_shared<FadeEffect>(60, FadeEffect::FadeType::kFadeOut, scene_change_func);

        entity_updater_ptr_->registerEntity(fade_effect_ptr);

        is_scene_change_requested_ = true;

        // シーン遷移時の効果音を再生
        PlaySoundMem(scene_change_sound_handle_, DX_PLAYTYPE_BACK);
    }

    entity_updater_ptr_->update();

    return true;
}

void TitleScene::draw() const {
    entity_updater_ptr_->draw();
}

void TitleScene::onReturnFromOtherScene(const SceneChangeParameter&) {
    is_scene_change_requested_ = false;

    // フェードイン演出を追加
    auto fade_effect_ptr = std::make_shared<FadeEffect>(60, FadeEffect::FadeType::kFadeIn, []() {});
    entity_updater_ptr_->registerEntity(fade_effect_ptr);
}

}  // namespace match_stick
