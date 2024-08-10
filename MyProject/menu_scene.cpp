
#include "menu_scene.h"

#include "dxlib_debug_print.h"
#include "fade_effect.h"
#include "fps_displayer.h"
#include "input_scheme_displayer.h"
#include "menu_back_ground_base.h"
#include "menu_ui.h"

namespace match_stick {

MenuScene::MenuScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                     const std::shared_ptr<const FpsController>& entity_updater_ptr,
                     const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                     const std::shared_ptr<const DxLibInput>& input_ptr,
                     const std::shared_ptr<FontLoader>& font_loader_ptr,
                     const std::shared_ptr<ImageLoader>& img_loader_ptr,
                     const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()) {
    DEBUG_PRINT("MenuScene Constructor called");

    // ルール画面のエンティティを登録
    entity_updater_ptr_->registerEntity(std::make_shared<FpsDisplayer>(entity_updater_ptr, font_loader_ptr));
    entity_updater_ptr_->registerEntity(std::make_shared<InputSchemeDisplayer>(input_ptr, img_loader_ptr));
    entity_updater_ptr_->registerEntity(std::make_shared<MenuBackGroundBase>());
    entity_updater_ptr_->registerEntity(std::make_shared<MenuUI>(language_record_ptr, input_ptr, font_loader_ptr, img_loader_ptr));

    // フェードイン演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeIn, []() {});
    entity_updater_ptr_->registerEntity(fade_effect_ptr);
}

bool MenuScene::update() {
    entity_updater_ptr_->update();

    return true;
}

void MenuScene::draw() const {
    entity_updater_ptr_->draw();
}

}  // namespace match_stick

