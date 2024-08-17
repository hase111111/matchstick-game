
#include "system_main.h"

#include <DxLib.h>

#include "game_const.h"
#include "game_main_loop.h"
#include "game_setting_importer.h"

namespace match_stick {

bool SystemMain::initialize() {
    // 設定ファイルを読み込む
    const GameSettingImporter game_setting_importer{};
    game_setting_record_ptr_ = std::make_shared<GameSettingRecord>(game_setting_importer.importSetting());

    // icon.rcで設定したアイコンファイルをセットする
    SetWindowIconID(333);

    SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);   // 文字コードをUTF-8に設定する
    SetWindowText(GameConst::kWindowTitle);            // ウィンドウタイトルを付ける
    SetAlwaysRunFlag(TRUE);                         // ウィンドウがノンアクティブでも実行
    SetOutApplicationLogValidFlag(FALSE);           // ログ出力しない
    SetDoubleStartValidFlag(FALSE);                 // 二重起動を許可しない
    SetMainWindowClassName(kWindowClassName.c_str());  // ウィンドウのクラス名を設定する

    // ゲーム画面の解像度を設定する
    const int color_bit = 32;  // 色の bit 数。通常32で良いが軽くするなら16にする
    SetGraphMode(GameConst::kResolutionX, GameConst::kResolutionY, color_bit);

    // フルスクリーン設定
    if (true) {
        // ウィンドウモードで起動する場合
        ChangeWindowMode(TRUE);

        // ウィンドウサイズを自由に変更できるようにする
        SetWindowSizeChangeEnableFlag(FALSE, FALSE);

        // 画面サイズ設定（スクリーンの大きさを取得して、それに合わせてウィンドウのサイズを変更する）
        RECT rc;
        GetWindowRect(GetDesktopWindow(), &rc);
        const int width = rc.right - rc.left;  // 横幅取得
        const double ex_rate = static_cast<double>(width) *
            GameConst::kWindowExRate / static_cast<double>(GameConst::kResolutionX);
        // ウィンドウサイズを変更したい時はここに倍率を指定する
        SetWindowSizeExtendRate(ex_rate);
    }

    // DXライブラリ初期化処理
    if (DxLib_Init() < -1) {
        // 異常終了したら即座にやめる
        return false;
    }

    SetSysCommandOffFlag(TRUE);     // ALTを無効にする
    SetDrawScreen(DX_SCREEN_BACK);  // 裏画面処理を設定する

    return true;
}

void SystemMain::finalize() const {
    // DxLibの終了処理を呼ぶ
    DxLib_End();
}

void SystemMain::main() const {
    GameMainLoop game_main_loop(game_setting_record_ptr_);

    // メインループ
    while (!ProcessMessage()) {
        if (!game_main_loop.loop()) {
            break;
        }
    }
}

}  // namespace match_stick
