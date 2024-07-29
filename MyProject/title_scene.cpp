
#include "title_scene.h"

#include <DxLib.h>

#include "title_back_ground_base.h"

namespace match_stick {

TitleScene::TitleScene(
    std::shared_ptr<SceneChangeListener> scene_change_listener_ptr,
    std::shared_ptr<const LanguageRecord> language_record_ptr,
    std::shared_ptr<const DxLibKeyboard> keyboard_ptr,
    std::shared_ptr<FontLoader> font_loader_ptr,
    std::shared_ptr<ImageLoader> img_loader_ptr,
    std::shared_ptr<SoundEffectLoader> sound_effect_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    language_record_ptr_(language_record_ptr),
    keyboard_ptr_(keyboard_ptr),
    font_loader_ptr_(font_loader_ptr),
    img_loader_ptr_(img_loader_ptr),
    sound_effect_loader_ptr_(sound_effect_loader_ptr),
    dxlib_renderer_ptr_(std::make_unique<DxLibRenderer>()) {

    dxlib_renderer_ptr_->Register(std::make_shared<TitleBackGroundBase>(img_loader_ptr_));
}

bool TitleScene::update() {
    if (keyboard_ptr_->getPressingCount(KEY_INPUT_ESCAPE) == 1) {
        return false;
    }

    return true;
}

void TitleScene::draw() const {
    DrawString(0, 0, "Title Scene", GetColor(255, 255, 255));

    dxlib_renderer_ptr_->Draw();

}

void TitleScene::onStart(const SceneChangeParameter& parameter) {

}

void TitleScene::onReturnFromOtherScene(const SceneChangeParameter& parameter) {

}

}  // namespace match_stick
