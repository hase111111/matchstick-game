﻿
#pragma once

#include <memory>

#include "dxlib_input.h"
#include "dxlib_resource_loader.h"
#include "entity_updater.h"
#include "fps_controller.h"
#include "i_scene.h"
#include "language_record.h"
#include "scene_change_listener.h"
#include "setting_scene_ui_creator.h"

namespace match_stick {

class SettingScene final : public IScene {
public:
    SettingScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                 const std::shared_ptr<const FpsController>& fps_controller_ptr,
                 const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                 const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
                 const std::shared_ptr<DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~SettingScene() = default;

    bool update() override;

    void draw() const override;

    void onStart(const SceneChangeParameter&) override {};

    void onReturnFromOtherScene(const SceneChangeParameter&) override;

private:
    const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;

    const std::unique_ptr<EntityUpdater> entity_updater_ptr_;

    const std::unique_ptr<SettingSceneUiCreator> setting_scene_ui_creator_ptr_;
};

}  // namespace match_stick
