
#include "scene_stack.h"

#include "dxlib_assert.h"

namespace match_stick
{

SceneStack::SceneStack(std::unique_ptr<SceneCreator>&& scene_creator_ptr) :
    scene_creator_ptr_(std::move(scene_creator_ptr))
{
    initializeScene();
}

bool SceneStack::updateTopScene()
{
    ASSERT(!scene_ptr_stack_.empty(), "The scene does not exist.");

    return scene_ptr_stack_.top()->update();
}

void SceneStack::drawTopScene() const
{
    ASSERT(!scene_ptr_stack_.empty(), "The scene does not exist.");

    scene_ptr_stack_.top()->draw();
}

void SceneStack::addNewScene(const SceneName scene_name, const SceneChangeParameter& parameter)
{
    auto new_scene_ptr = scene_creator_ptr_->createScene(scene_name);

    new_scene_ptr->onStart(parameter);  // パラメータを渡して，初期化処理を行う．

    scene_ptr_stack_.push(std::move(new_scene_ptr));
}

void SceneStack::deleteNowScene(const int delete_num, const SceneChangeParameter& parameter)
{
    ASSERT(delete_num <= scene_ptr_stack_.size(), "The number of scenes to delete is invalid.");

    // 引数の数だけシーンを削除する．
    for (int i = 0; i < delete_num; ++i)
    {
        scene_ptr_stack_.pop();
    }

    ASSERT(!scene_ptr_stack_.empty(), "The scene does not exist.");  // 冗長になるが，確認する．

    // 削除後のシーンに対して，引数のパラメータを渡して，初期化処理を行う．
    scene_ptr_stack_.top()->onReturnFromOtherScene(parameter);
}

void SceneStack::deleteAllScene()
{
    // シーンを全て削除する．
    while (!scene_ptr_stack_.empty())
    {
        scene_ptr_stack_.pop();
    }

    // 初期シーンを再度生成する．
    initializeScene();
}

void SceneStack::initializeScene()
{
    auto first_scene_ptr = scene_creator_ptr_->createScene(SceneName::kDebug);
    SceneChangeParameter parameter;

    first_scene_ptr->onStart(parameter);  // 空のパラメータを渡して，初期化処理を行う．

    scene_ptr_stack_.push(std::move(first_scene_ptr));
}

}  // namespace match_stick
