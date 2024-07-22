
#pragma once

#include <memory>

#include "scene_change_listener.h"
#include "scene_stack.h"

namespace match_stick
{

class SceneChangeExecuter final
{
public:
    SceneChangeExecuter() = delete;  //!< デフォルトコンストラクタは使用不可．

    SceneChangeExecuter(
        const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
        const std::shared_ptr<SceneStack>& scene_stack_ptr);

    void Execute();

private:
    std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
    std::shared_ptr<SceneStack> scene_stack_ptr_;
};

}  // namespace match_stick
