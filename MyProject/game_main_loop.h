
#pragma once

#include <memory>

#include "fps_controller.h"
#include "SceneManager.h"

namespace match_stick {

class GameMainLoop {
public:
    GameMainLoop();
    ~GameMainLoop() = default;

    bool loop();

private:
    SceneManger scene_manager_;
    FpsController fps_controller_;
};

}  // namespace match_stick
