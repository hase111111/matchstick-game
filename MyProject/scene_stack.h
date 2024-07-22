
#pragma once

#include <memory>
#include <stack>

#include "i_scene.h"
#include "image_loader.h"
#include "scene_change_parameter.h"
#include "scene_creator.h"
#include "scene_name.h"

namespace match_stick
{

class SceneStack final
{
public:
    SceneStack(std::unique_ptr<SceneCreator>&& scene_creator_ptr);

    bool UpdateTopScene();
    void DrawTopScene() const;

    void AddNewScene(SceneName scene_name, const SceneChangeParameter& parameter);
    void DeleteNowScene(int delete_num, const SceneChangeParameter& parameter);
    void DeleteAllScene();

private:
    void InitializeScene();

    std::stack<std::unique_ptr<IScene>> scene_ptr_stack_;  //!< シーンを格納する配列．スタック．

    const std::unique_ptr<SceneCreator> scene_creator_ptr_;  //!< シーンを生成するクラス．
};

}  // namespace match_stick
