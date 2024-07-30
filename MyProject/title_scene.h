
#pragma once

#include <memory>

#include "dxlib_keyboard.h"
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
        const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
        const std::shared_ptr<const LanguageRecord>& language_record_ptr,
        const std::shared_ptr<const DxLibKeyboard>& keyboard_ptr,
        const std::shared_ptr<FontLoader>& font_loader_ptr,
        const std::shared_ptr<ImageLoader>& img_loader_ptr,
        const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr);

    ~TitleScene() = default;

    bool update() override;

    void draw() const override;

    void onStart(const SceneChangeParameter&) override {};

    void onReturnFromOtherScene(const SceneChangeParameter& parameter) override;

private:
    std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
    std::shared_ptr<const DxLibKeyboard> keyboard_ptr_;

    std::unique_ptr<EntityUpdater> entity_updater_ptr_;

    bool is_scene_change_requested_{ false };
    int scene_change_sound_handle_{ -1 };
};

}  // namespace match_stick
