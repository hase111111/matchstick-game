
#pragma once

#include <memory>
#include <stack>

#include "i_scene.h"
#include "image_loader.h"
#include "scene_change_parameter.h"
#include "scene_creator.h"
#include "scene_name.h"

namespace match_stick {

class SceneStack final {
public:
    SceneStack(std::unique_ptr<SceneCreator>&& scene_creator_ptr);

    bool updateTopScene();
    void drawTopScene() const;

    void addNewScene(SceneName scene_name, const SceneChangeParameter& parameter);
    void deleteNowScene(int delete_num, const SceneChangeParameter& parameter);
    void deleteAllScene();

private:
    void initializeScene();

    //! シーンを格納する配列．スタック．
    std::stack<std::unique_ptr<IScene>> scene_ptr_stack_;

    //!< シーンを生成するクラス．
    const std::unique_ptr<SceneCreator> scene_creator_ptr_;
};

}  // namespace match_stick
