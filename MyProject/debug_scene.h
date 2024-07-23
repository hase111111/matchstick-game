
#pragma once

#include "i_scene.h"

namespace match_stick {

class DebugScene final : public IScene {
public:
    DebugScene() = default;
    ~DebugScene() = default;

    bool update() override;

    void draw() const override;

    void onStart(const SceneChangeParameter& parameter) override;

    void onReturnFromOtherScene(const SceneChangeParameter& parameter) override;
};

}  // namespace match_stick
