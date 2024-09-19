
//! @file game_main_loop.cpp
//! @brief
//! Copyright(c) 2024 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php


#include "game_main_loop.h"

#include <utility>

#include <DxLib.h>

#include "dxlib_resource_loader.h"
#include "language_record_initializer.h"

namespace match_stick {

GameMainLoop::GameMainLoop(const std::shared_ptr<const GameSettingRecord>& game_setting_record_ptr) :
    dxlib_input_ptr_(std::make_shared<DxLibInput>()),
    fps_controller_ptr_(std::make_shared<FpsController>(60)),
    game_setting_record_ptr_(game_setting_record_ptr),
    scene_change_listener_ptr_(std::make_shared<SceneChangeListener>()),
    scene_stack_ptr_(initializeSceneStack()),
    scene_change_executer_{ scene_change_listener_ptr_, scene_stack_ptr_ } {
    // NULLチェック．
    ASSERT_NOT_NULL_PTR(game_setting_record_ptr);

    ASSERT_NOT_NULL_PTR(dxlib_input_ptr_);
    ASSERT_NOT_NULL_PTR(fps_controller_ptr_);
    ASSERT_NOT_NULL_PTR(game_setting_record_ptr_);
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
    ASSERT_NOT_NULL_PTR(scene_stack_ptr_);
}

bool GameMainLoop::loop() {
    // 入力を取得
    dxlib_input_ptr_->update();

    // シーンのスタックの一番上を実行する．
    if (!scene_stack_ptr_->updateTopScene()) {
        return false;
    }

    // 処理が重い場合はここでコマ落ちさせる．
    if (!fps_controller_ptr_->skipDrawScene()) {
        // スクリーンを消す．
        if (DxLib::ClearDrawScreen() != 0) {
            return false;
        }

        // 描画する．
        scene_stack_ptr_->drawTopScene();

        // スクリーンに表示する．
        if (DxLib::ScreenFlip() != 0) {
            return false;
        }
    }

    // FPSを調整するための処理．
    fps_controller_ptr_->wait();

    // シーンの変更を実行する．
    scene_change_executer_.execute();

    return true;
}

std::shared_ptr<SceneStack> GameMainLoop::initializeSceneStack() const {
    // NULLチェック．
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr_);
    ASSERT_NOT_NULL_PTR(fps_controller_ptr_);
    ASSERT_NOT_NULL_PTR(game_setting_record_ptr_);
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);

    LanguageRecordInitializer language_record_initializer;
    const auto language_record_ptr =
        std::make_shared<LanguageRecord>(
            language_record_initializer.initialize(game_setting_record_ptr_->language_country));

    const auto dxlib_resource_loader_ptr = std::make_shared<DxLibResourceLoader>();
    dxlib_resource_loader_ptr->changeAllSEVolume(game_setting_record_ptr_->sound_volume);

    auto scene_creator_ptr = std::make_unique<SceneCreator>(
        scene_change_listener_ptr_,
        fps_controller_ptr_,
        language_record_ptr,
        dxlib_input_ptr_,
        dxlib_resource_loader_ptr);

    auto scene_stack_ptr = std::make_shared<SceneStack>(std::move(scene_creator_ptr));

    return scene_stack_ptr;
}

}  // namespace match_stick
