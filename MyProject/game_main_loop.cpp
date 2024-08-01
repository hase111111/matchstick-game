
//! @file game_main_loop.cpp
//! @copyright 2024 Taisei Hasegawa
//! @brief
//! 
//!  ----------------------------------------------------------------------------
//! | ##   ##   ##   ######   ####  ##   ##   #####  ###### ####   ####  ###  ## |
//! | ### ###  ####  # ## #  ##  ## ##   ##  ##   ## # ## #  ##   ##  ##  ##  ## |
//! | ####### ##  ##   ##   ##      ##   ##  #         ##    ##  ##       ## ##  |
//! | ####### ##  ##   ##   ##      #######   #####    ##    ##  ##       ####   |
//! | ## # ## ######   ##   ##      ##   ##       ##   ##    ##  ##       ## ##  |
//! | ##   ## ##  ##   ##    ##  ## ##   ##  ##   ##   ##    ##   ##  ##  ##  ## |
//! | ##   ## ##  ##  ####    ####  ##   ##   #####   ####  ####   ####  ###  ## |
//!  ----------------------------------------------------------------------------
//!

#include "game_main_loop.h"

#include <utility>

#include <DxLib.h>

#include "language_record_initializer.h"


namespace match_stick {

GameMainLoop::GameMainLoop() :
    input_ptr_(std::make_shared<DxLibInput>()),
    fps_controller_(std::make_shared<FpsController>(60)),
    scene_change_listener_ptr_(std::make_shared<SceneChangeListener>()),
    scene_stack_ptr_(initializeSceneStack()),
    scene_change_executer_{ scene_change_listener_ptr_, scene_stack_ptr_ } {}

bool GameMainLoop::loop() {
    // 入力を取得
    input_ptr_->update();

    // シーンのスタックの一番上を実行する．
    if (!scene_stack_ptr_->updateTopScene()) {
        return false;
    }

    // 処理が重い場合はここでコマ落ちさせる．
    if (!fps_controller_->skipDrawScene()) {
        // スクリーンを消す．
        if (ClearDrawScreen() != 0) {
            return false;
        }

        // 描画する．
        scene_stack_ptr_->drawTopScene();

        // スクリーンに表示する．
        if (ScreenFlip() != 0) {
            return false;
        }
    }

    // FPSを調整するための処理．
    fps_controller_->wait();

    // シーンの変更を実行する．
    scene_change_executer_.execute();

    return true;
}

std::shared_ptr<SceneStack> GameMainLoop::initializeSceneStack() const {
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
    ASSERT_NOT_NULL_PTR(input_ptr_);

    LanguageRecordInitializer language_record_initializer;
    const auto language_record_ptr =
        std::make_shared<const LanguageRecord>(language_record_initializer.initialize(LanguageRecord::Country::kJapan));

    auto scene_creator_ptr = std::make_unique<SceneCreator>(
        scene_change_listener_ptr_,
        fps_controller_,
        language_record_ptr,
        input_ptr_,
        std::make_shared<BgmPlayer>(),
        std::make_shared<FontLoader>(),
        std::make_shared<ImageLoader>(),
        std::make_shared<SoundEffectLoader>());

    auto scene_stack_ptr = std::make_shared<SceneStack>(std::move(scene_creator_ptr));

    return scene_stack_ptr;
}

}  // namespace match_stick
