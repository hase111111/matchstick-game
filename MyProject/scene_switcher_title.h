
#pragma once

#include <memory>

#include "dxlib_keyboard.h"
#include "i_updatable_entity.h"
#include "scene_change_listener.h"

namespace match_stick {

class SceneSwitcherTitle final : public IUpdatableEntity {
public:
    SceneSwitcherTitle(
        const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
        const std::shared_ptr<const DxLibKeyboard>& keyboard_ptr);
    ~SceneSwitcherTitle() = default;

    void update() override;

private:
    const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
    const std::shared_ptr<const DxLibKeyboard> keyboard_ptr_;
};

}  // namespace match_stick
