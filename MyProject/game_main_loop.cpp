
#include "game_main_loop.h"

#include <DxLib.h>

#include "keyboard.h"


namespace match_stick {

GameMainLoop::GameMainLoop() :
    keyboard_ptr_(std::make_shared<DxLibKeyboard>()),
    mouse_ptr_(std::make_shared<DxLibMouse>()),
    fps_controller_{ 60 },
    scene_change_listener_ptr_(std::make_shared<SceneChangeListener>()),
    scene_stack_ptr_(initializeSceneStack()),
    scene_change_executer_{ scene_change_listener_ptr_, scene_stack_ptr_ } {
}

bool GameMainLoop::loop()
{
    //入力を取得
    keyboard_ptr_->update();
    mouse_ptr_->update();

    // シーンのスタックの一番上を実行する．
    if (!scene_stack_ptr_->UpdateTopScene())
    {
        return false;
    }

    // 処理が重い場合はここでコマ落ちさせる．
    if (!fps_controller_.skipDrawScene())
    {
        // スクリーンを消す．
        if (ClearDrawScreen() != 0)
        {
            return false;
        }

        // 描画する．
        scene_stack_ptr_->DrawTopScene();

        // スクリーンに表示する．
        if (ScreenFlip() != 0)
        {
            return false;
        }
    }

    // FPSを調整するための処理．
    fps_controller_.wait();

    // シーンの変更を実行する．
    scene_change_executer_.Execute();

    return true;
}

std::shared_ptr<SceneStack> GameMainLoop::initializeSceneStack() const
{
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
    ASSERT_NOT_NULL_PTR(keyboard_ptr_);
    ASSERT_NOT_NULL_PTR(mouse_ptr_);

    LanguageRecordInitializer language_record_initializer;
    const std::shared_ptr<const LanguageRecord> language_record_ptr = std::make_shared<const LanguageRecord>(language_record_initializer.Initialize());

    auto scene_creator_ptr = std::make_unique<SceneCreator>(
        scene_change_listener_ptr_,
        language_record_ptr,
        keyboard_ptr_, mouse_ptr_,
        std::make_shared<BgmPlayer>(), std::make_shared<FontLoader>(),
        std::make_shared<ImageLoader>(), std::make_shared<SoundEffectLoader>());

    auto scene_stack_ptr = std::make_shared<SceneStack>(std::move(scene_creator_ptr));

    return scene_stack_ptr;
}

}  // namespace match_stick
