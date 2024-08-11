
#include "title_scene.h"

#include <DxLib.h>

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
                       const std::shared_ptr<const DxLibInput>& input_ptr,
                       const std::shared_ptr<FontLoader>& font_loader_ptr,
                       const std::shared_ptr<ImageLoader>& img_loader_ptr,
                       const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    input_ptr_(input_ptr),
    sound_effect_loader_ptr_(sound_effect_loader_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()) {
    // タイトルのエンティティを登録
    entity_updater_ptr_->registerEntity(std::make_shared<TitleBackGroundBase>(img_loader_ptr));
    entity_updater_ptr_->registerEntity(std::make_shared<TitleLogo>(input_ptr, language_record_ptr, font_loader_ptr));
    entity_updater_ptr_->registerEntity(std::make_shared<TitleHandAnimation>(img_loader_ptr));

    entity_updater_ptr_->registerEntity(std::make_shared<FpsDisplayer>(fps_controller_ptr, language_record_ptr, font_loader_ptr));

    entity_updater_ptr_->registerEntity(std::make_shared<InputSchemeDisplayer>(input_ptr, img_loader_ptr));

    // シーン遷移用のエンティティを登録
    entity_updater_ptr_->registerEntity(std::make_shared<TitleSceneSwitcher>(input_ptr, sound_effect_loader_ptr,
        std::bind(&TitleScene::callbackForSceneChange, this)));
}

bool TitleScene::update() {
    if (input_ptr_->getKeyboardPressingCount(KEY_INPUT_ESCAPE) == 1) {
        return false;
    }

    entity_updater_ptr_->update();

    return true;
}

void TitleScene::draw() const {
    entity_updater_ptr_->draw();
}

void TitleScene::onReturnFromOtherScene(const SceneChangeParameter&) {
    // フェードイン演出を追加
    auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeIn, []() {});
    entity_updater_ptr_->registerEntity(fade_effect_ptr);

    // シーン遷移用のエンティティを登録
    entity_updater_ptr_->registerEntity(std::make_shared<TitleSceneSwitcher>(input_ptr_, sound_effect_loader_ptr_,
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
