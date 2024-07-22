
#include "keyboard.h"
#include "looper.h"

Looper::Looper() {
}

bool Looper::loop() {
    // 入力を取得
    Keyboard::getIns()->update();

    // シーンのスタックの一番上を実行
    if (!m_sceneMgr.updateTopScene()) { return false; }
    m_sceneMgr.drawTopScene();

    // fpsを制御するための関数
    m_fps.wait();
    // m_fps.draw();

    // 全処理の遂行後,シーンチェンジを行う
    m_sceneMgr.sceneChangeExecute();

    return true;
}
