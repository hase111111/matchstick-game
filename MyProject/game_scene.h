
#pragma once

#include <memory>

#include "dxlib_input.h"
#include "dxlib_resource_loader.h"
#include "entity_updater.h"
#include "i_scene.h"
#include "language_record.h"
#include "scene_change_listener.h"

namespace match_stick {

class GameScene final : public IScene {
public:
    GameScene(const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr,
              const std::shared_ptr<const LanguageRecord> language_record_ptr,
              const std::shared_ptr<const DxLibInput> dxlib_input_ptr,
              const std::shared_ptr<const DxLibResourceLoader> dxlib_resource_loader_ptr);

    ~GameScene() = default;

    bool update() override;

    void draw() const override;

    void onStart(const SceneChangeParameter& parameter) override;

    void onReturnFromOtherScene(const SceneChangeParameter& parameter) override;

private:
    const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
    const std::unique_ptr<EntityUpdater> entity_updater_ptr_;

    const std::shared_ptr<const DxLibInput> dxlib_input_ptr_;

    bool is_scene_change_requested_{ false };
    int scene_change_sound_handle_{ -1 };
};

}  // namespace match_stick
