
#pragma once

#include <memory>

#include "dxlib_input.h"
#include "entity_updater.h"
#include "font_loader.h"
#include "fps_controller.h"
#include "i_scene.h"
#include "image_loader.h"
#include "language_record.h"
#include "scene_change_listener.h"
#include "sound_effect_loader.h"

namespace match_stick {

class MenuScene final : public IScene {
public:
    MenuScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
              const std::shared_ptr<const FpsController>& entity_updater_ptr,
              const std::shared_ptr<const LanguageRecord>& language_record_ptr,
              const std::shared_ptr<const DxLibInput>& input_ptr,
              const std::shared_ptr<FontLoader>& font_loader_ptr,
              const std::shared_ptr<ImageLoader>& img_loader_ptr,
              const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr);

    ~MenuScene();

    bool update() override;

    void draw() const override;

    void onStart(const SceneChangeParameter&) override {};

    void onReturnFromOtherScene(const SceneChangeParameter&) override;

private:
    const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;

    std::unique_ptr<EntityUpdater> entity_updater_ptr_;

    void sceneBackCallback();

    void sceneChangeCallback(SceneName scene_name);

    bool now_scene_change_{ false };

    bool game_end_{ false };
};

}  // namespace match_stick
