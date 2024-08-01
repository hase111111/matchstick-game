
#include "game_scene.h"

#include "fade_effect.h"
#include "game_back_ground_base.h"
#include "game_log.h"

namespace match_stick {

GameScene::GameScene(std::shared_ptr<SceneChangeListener> scene_change_listener_ptr,
                     std::shared_ptr<const LanguageRecord> language_record_ptr,
                     std::shared_ptr<const DxLibInput> input_ptr,
                     std::shared_ptr<FontLoader> font_loader_ptr,
                     std::shared_ptr<ImageLoader> img_loader_ptr,
                     std::shared_ptr<SoundEffectLoader> sound_effect_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    input_ptr_(input_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()) {
    // 表示する entity を登録
    entity_updater_ptr_->registerEntity(std::make_shared<GameBackGroundBase>());
    entity_updater_ptr_->registerEntity(std::make_shared<GameLog>(language_record_ptr, font_loader_ptr));

    entity_updater_ptr_->registerEntity(std::make_shared<FadeEffect>(60, FadeEffect::FadeType::kFadeIn, []() {}));
}

bool GameScene::update() {
    entity_updater_ptr_->update();
    return true;
}

void GameScene::draw() const {
    entity_updater_ptr_->draw();
}

void GameScene::onStart(const SceneChangeParameter&) {}

void GameScene::onReturnFromOtherScene(const SceneChangeParameter&) {}

}  // namespace match_stick
