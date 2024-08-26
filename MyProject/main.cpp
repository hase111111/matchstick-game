
// 表示→その他のウィンドウ→プロパティ→マネージャー
// myBuildSettings → マクロ に DXLIB_DIR が定義されている．

// C28251 を無視する
#pragma warning(disable: 28251)

#include <DxLib.h>

#include "dxlib_debug_print.h"
#include "error_message_box.h"
#include "system_main.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    using match_stick::ErrorMessageBox;
    using match_stick::SystemMain;

    PREPAER_DEBUG_PRINT();  // デバッグ用のコンソールを作成

    SystemMain system_main;

    if (system_main.initialize()) {
        system_main.main();
    } else {
        ErrorMessageBox::show("初期化に失敗しました。");
    }

    system_main.finalize();

    return 0;
}
