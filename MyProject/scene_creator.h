﻿
#pragma once

#include <memory>

#include "dxlib_input.h"
#include "dxlib_resource_loader.h"
#include "fps_controller.h"
#include "i_scene.h"
#include "language_record.h"
#include "scene_name.h"
#include "scene_change_listener.h"

namespace match_stick {

class SceneCreator final {
public:
    SceneCreator(
        const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
        const std::shared_ptr<const FpsController>& fps_controller_ptr,
        const std::shared_ptr<LanguageRecord>& language_record_ptr,
        const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
        const std::shared_ptr<DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~SceneCreator() = default;

    std::unique_ptr<IScene> createScene(SceneName scene_name) const;

private:
    const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;

    const std::shared_ptr<const FpsController> fps_controller_ptr_;

    const std::shared_ptr<LanguageRecord> language_record_ptr_;

    const std::shared_ptr<const DxLibInput> dxlib_input_ptr_;

    const std::shared_ptr<DxLibResourceLoader> dxlib_resource_loader_ptr_;
};

}  // namespace match_stick
