﻿
#pragma once

#include <memory>

#include "dxlib_keyboard.h"
#include "dxlib_mouse.h"
#include "fps_controller.h"
#include "scene_change_executer.h"
#include "scene_change_listener.h"
#include "scene_stack.h"

namespace match_stick {

class GameMainLoop {
public:
    GameMainLoop();
    ~GameMainLoop() = default;

    bool loop();

private:
    std::shared_ptr<SceneStack> initializeSceneStack() const;

    std::shared_ptr<DxLibKeyboard> keyboard_ptr_;
    std::shared_ptr<DxLibMouse> mouse_ptr_;

    std::shared_ptr<FpsController> fps_controller_;

    const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
    const std::shared_ptr<SceneStack> scene_stack_ptr_;
    SceneChangeExecuter scene_change_executer_;
};

}  // namespace match_stick
