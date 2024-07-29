
#include "title_scene.h"

#include <DxLib.h>

#include "title_back_ground_base.h"
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
    dxlib_renderer_ptr_(std::make_unique<DxLibRenderer>()),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()) {

    dxlib_renderer_ptr_->registerRenderable(std::make_shared<TitleBackGroundBase>(img_loader_ptr));

    auto title_logo_ptr_ = std::make_shared<TitleLogo>(language_record_ptr, font_loader_ptr);
    dxlib_renderer_ptr_->registerRenderable(title_logo_ptr_);
    entity_updater_ptr_->registerEntity(title_logo_ptr_);
}

bool TitleScene::update() {
    if (keyboard_ptr_->getPressingCount(KEY_INPUT_ESCAPE) == 1) {
        return false;
    }

    entity_updater_ptr_->update();

    return true;
}

void TitleScene::draw() const {
    dxlib_renderer_ptr_->draw();
}

void TitleScene::onStart(const SceneChangeParameter& parameter) {

}

void TitleScene::onReturnFromOtherScene(const SceneChangeParameter& parameter) {

}

}  // namespace match_stick
