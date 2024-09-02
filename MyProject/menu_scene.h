
#pragma once

#include <memory>

#include "dxlib_input.h"
#include "dxlib_resource_loader.h"
#include "entity_updater.h"
#include "fps_controller.h"
#include "i_scene.h"
#include "language_record.h"
#include "scene_change_listener.h"

namespace match_stick {

class MenuScene final : public IScene {
public:
    MenuScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
              const std::shared_ptr<const FpsController>& fps_controller_ptr,
              const std::shared_ptr<const LanguageRecord>& language_record_ptr,
              const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
              const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~MenuScene() = default;

    bool update() override;

    void draw() const override;

    void onStart(const SceneChangeParameter&) override {};

    void onReturnFromOtherScene(const SceneChangeParameter&) override;

private:
    const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;

    const std::unique_ptr<EntityUpdater> entity_updater_ptr_;

    void initUI(const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
                const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr);

    bool now_scene_change_{ false };

    bool game_end_{ false };
};

}  // namespace match_stick
