
#pragma once

#include <memory>

#include "dxlib_keyboard.h"
#include "dxlib_renderer.h"
#include "entity_updater.h"
#include "font_loader.h"
#include "i_scene.h"
#include "image_loader.h"
#include "language_record.h"
#include "scene_change_listener.h"
#include "sound_effect_loader.h"

namespace match_stick {

class TitleScene final : public IScene {
public:
    TitleScene(
        std::shared_ptr<SceneChangeListener> scene_change_listener_ptr,
        std::shared_ptr<const LanguageRecord> language_record_ptr,
        std::shared_ptr<const DxLibKeyboard> keyboard_ptr,
        std::shared_ptr<FontLoader> font_loader_ptr,
        std::shared_ptr<ImageLoader> img_loader_ptr,
        std::shared_ptr<SoundEffectLoader> sound_effect_loader_ptr);

    ~TitleScene() = default;

    bool update() override;

    void draw() const override;

    void onStart(const SceneChangeParameter& parameter) override;

    void onReturnFromOtherScene(const SceneChangeParameter& parameter) override;

private:
    std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
    std::shared_ptr<const DxLibKeyboard> keyboard_ptr_;

    std::unique_ptr<DxLibRenderer> dxlib_renderer_ptr_;
    std::unique_ptr<EntityUpdater> entity_updater_ptr_;

};

}  // namespace match_stick
