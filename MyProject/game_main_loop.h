
#pragma once

#include <memory>

#include "dxlib_input.h"
#include "fps_controller.h"
#include "game_setting_record.h"
#include "scene_change_executer.h"
#include "scene_change_listener.h"
#include "scene_stack.h"

namespace match_stick {

class GameMainLoop {
public:
    GameMainLoop(const std::shared_ptr<const GameSettingRecord>& game_setting_record);
    ~GameMainLoop() = default;

    bool loop();

private:
    std::shared_ptr<SceneStack> initializeSceneStack() const;

    const std::shared_ptr<DxLibInput> dxlib_input_ptr_;

    const std::shared_ptr<FpsController> fps_controller_;

    const std::shared_ptr<const GameSettingRecord> game_setting_record_ptr_;

    const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
    const std::shared_ptr<SceneStack> scene_stack_ptr_;
    SceneChangeExecuter scene_change_executer_;
};

}  // namespace match_stick
