
#include "scene_stack.h"

#include "dxlib_assert.h"

namespace match_stick
{

SceneStack::SceneStack(std::unique_ptr<SceneCreator>&& scene_creator_ptr) :
    scene_creator_ptr_(std::move(scene_creator_ptr))
{
    InitializeScene();
}

bool SceneStack::UpdateTopScene()
{
    ASSERT(!scene_ptr_stack_.empty(), "The scene does not exist.");

    return scene_ptr_stack_.top()->Update();
}

void SceneStack::DrawTopScene() const
{
    ASSERT(!scene_ptr_stack_.empty(), "The scene does not exist.");

    scene_ptr_stack_.top()->Draw();
}

void SceneStack::AddNewScene(const SceneName scene_name, const SceneChangeParameter& parameter)
{
    auto new_scene_ptr = scene_creator_ptr_->CreateScene(scene_name);

    new_scene_ptr->OnStart(parameter);  // パラメータを渡して，初期化処理を行う．

    scene_ptr_stack_.push(std::move(new_scene_ptr));
}

void SceneStack::DeleteNowScene(const int delete_num, const SceneChangeParameter& parameter)
{
    ASSERT(delete_num <= scene_ptr_stack_.size(), "The number of scenes to delete is invalid.");

    // 引数の数だけシーンを削除する．
    for (int i = 0; i < delete_num; ++i)
    {
        scene_ptr_stack_.pop();
    }

    ASSERT(!scene_ptr_stack_.empty(), "The scene does not exist.");  // 冗長になるが，確認する．

    // 削除後のシーンに対して，引数のパラメータを渡して，初期化処理を行う．
    scene_ptr_stack_.top()->OnReturnFromOtherScene(parameter);
}

void SceneStack::DeleteAllScene()
{
    // シーンを全て削除する．
    while (!scene_ptr_stack_.empty())
    {
        scene_ptr_stack_.pop();
    }

    // 初期シーンを再度生成する．
    InitializeScene();
}

void SceneStack::InitializeScene()
{
    auto first_scene_ptr = scene_creator_ptr_->CreateScene(SceneName::kTitle);
    SceneChangeParameter parameter;

    first_scene_ptr->OnStart(parameter);  // 空のパラメータを渡して，初期化処理を行う．

    scene_ptr_stack_.push(std::move(first_scene_ptr));
}

}  // namespace match_stick
