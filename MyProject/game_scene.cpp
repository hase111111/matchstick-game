
#include "game_scene.h"

#include "dxlib_assert.h"
#include "fade_effect.h"
#include "game_back_ground_base.h"
#include "game_log.h"
#include "input_scheme_displayer.h"

namespace match_stick {

GameScene::GameScene(const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr,
                     const std::shared_ptr<const LanguageRecord> language_record_ptr,
                     const std::shared_ptr<const DxLibInput> dxlib_input_ptr,
                     const std::shared_ptr<const DxLibResourceLoader> dxlib_resource_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()),
    dxlib_input_ptr_(dxlib_input_ptr) {
    // nullptr チェック
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);

    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
    ASSERT_NOT_NULL_PTR(entity_updater_ptr_);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr_);

    // 表示する entity を登録
    entity_updater_ptr_->registerEntity(std::make_shared<GameBackGroundBase>());
    entity_updater_ptr_->registerEntity(std::make_shared<GameLog>(language_record_ptr, dxlib_resource_loader_ptr));

    entity_updater_ptr_->registerEntity(std::make_shared<FadeEffect>(60, FadeEffect::FadeType::kFadeIn, []() {}));

    entity_updater_ptr_->registerEntity(std::make_shared<InputSchemeDisplayer>(dxlib_input_ptr_, dxlib_resource_loader_ptr));
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
