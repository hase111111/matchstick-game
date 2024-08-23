
#pragma once

#include <memory>

#include "dxlib_input.h"
#include "i_scene.h"
#include "scene_change_listener.h"

namespace match_stick {

class DebugScene final : public IScene {
public:
    DebugScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
               const std::shared_ptr<const DxLibInput>& input_ptr);
    ~DebugScene() = default;

    bool update() override;

    void draw() const override;

    void onStart(const SceneChangeParameter& parameter) override;

    void onReturnFromOtherScene(const SceneChangeParameter& parameter) override;

private:
    std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
    std::shared_ptr<const DxLibInput> dxlib_input_ptr_;
};

}  // namespace match_stick
