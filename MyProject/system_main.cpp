
#include "system_main.h"

#include <DxLib.h>

#include "define.h"
#include "game_main_loop.h"
#include "setting.h"
#include "sound.h"

namespace match_stick {

bool SystemMain::initialize() const {
    // icon.rcで設定したアイコンファイルをセットする
    SetWindowIconID(333);

    SetWindowText(Define::WIN_TITLE.c_str());  // ウィンドウタイトルを付ける
    SetAlwaysRunFlag(TRUE);  // ウィンドウがノンアクティブでも実行
    SetOutApplicationLogValidFlag(FALSE);  // ログ出力しない
    const int COLOR_BIT = 32;  // 色の bit 数。通常32で良いが軽くするなら16にする
    // ゲーム画面の解像度を設定する
    SetGraphMode(Define::WIN_SIZEX, Define::WIN_SIZEY, COLOR_BIT);

    Setting::getIns()->loadSettingFile();  // セーブファイルを読み込む

    // 音量を設定ファイル空設定する
    Sound::getIns()->changeVolume(Setting::getIns()->getSettingVol());

    // フルスクリーン設定
    if (!Setting::getIns()->getSettingFulWin()) {
        // ウィンドウモードで起動する場合
        ChangeWindowMode(TRUE);

        // ウィンドウサイズを自由に変更できるようにする
        SetWindowSizeChangeEnableFlag(FALSE, FALSE);

        // 画面サイズ設定（スクリーンの大きさを取得して、それに合わせてウィンドウのサイズを変更する）
        RECT rc;
        GetWindowRect(GetDesktopWindow(), &rc);
        int width = rc.right - rc.left;  // 横幅取得
        double ex_rate = static_cast<double>(width) *
            Define::WIN_EXRATE / static_cast<double>(Define::WIN_SIZEX);
        // ウィンドウサイズを変更したい時はここに倍率を指定する
        SetWindowSizeExtendRate(ex_rate);
    }

    // DXライブラリ初期化処理
    if (DxLib_Init() < -1) {
        // 異常終了したら即座にやめる
        return false;
    }

    SetSysCommandOffFlag(TRUE);  // ALTを無効にする
    SetDrawScreen(DX_SCREEN_BACK);  // 裏画面処理を設定する

    return true;
}

void SystemMain::finalize() const {
    // DxLibの終了処理を呼ぶ
    DxLib_End();
}

void SystemMain::main() const {

    GameMainLoop game_main_loop;

    // メインループ
    while (!ProcessMessage()) {
        if (!game_main_loop.loop()) {
            break;
        }
    }
}

}  // namespace match_stick
