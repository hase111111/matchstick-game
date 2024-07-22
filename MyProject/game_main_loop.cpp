
#include "game_main_loop.h"

#include <DxLib.h>

#include "keyboard.h"


namespace match_stick {

GameMainLoop::GameMainLoop() : fps_controller_{ 60 } {
}

bool GameMainLoop::loop() {

    // 入力を取得
    Keyboard::getIns()->update();

    // シーンのスタックの一番上を実行
    if (!scene_manager_.updateTopScene()) {
        return false;
    }

    if (!fps_controller_.skipDrawScene()) {

        // 裏画面を初期化
        if (ClearDrawScreen() < 0) {
            return false;
        }

        scene_manager_.drawTopScene();

        // 裏画面を表画面に反映
        if (ScreenFlip() < 0) {
            return false;
        }
    }

    // FPSを一定にするために待つ
    fps_controller_.wait();

    // 全処理の遂行後,シーンチェンジを行う
    scene_manager_.sceneChangeExecute();

    return true;
}

}  // namespace match_stick
